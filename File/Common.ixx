module;

#ifdef __INTELLISENSE__
    #include <algorithm>
    #include <variant>
    #include <filesystem>
    #include <format>
#endif

export module FatPound.File.Common;

import FatPound.Cryptography.XorCipher;
import std;

namespace fatpound::file
{
    /// @brief Encrypts or decrypts a file using an XOR cipher with the specified key
    /// 
    /// @param  inPath: The path to the input file to be encrypted or decrypted
    /// @param     key: The key to use for the XOR cipher
    /// @param outPath: The path where the output file will be written. If empty or the same as inPath, a temporary file path is used
    /// 
    void EncryptDecrypt_Impl (const std::filesystem::path& inPath, const std::size_t& key, const std::filesystem::path& outPath)
    {
        std::ifstream inputFile(inPath, std::ios::binary);

        if (not inputFile.is_open())
        {
            throw std::runtime_error("Input file cannot be opened!");
        }

        std::ofstream outputFile(outPath, std::ios::binary);

        if (not outputFile.is_open())
        {
            throw std::runtime_error("Cannot create the new version of file!");
        }

        cryptography::ApplyXorCipherWithKey<>(
            std::istreambuf_iterator<char>(inputFile),
            {},
            std::ostreambuf_iterator<char>(outputFile),
            key
        );
    }
}

export namespace fatpound::file
{
    /// @brief Reads the entire contents of a file into a string
    ///
    /// @param path: The path to the file to be read
    ///
    /// @return A string containing the contents of the file
    /// 
    [[nodiscard]]
    auto ReadToString        (const std::filesystem::path& path) -> std::string
    {
        std::ifstream file(path, std::ios::binary);

        if (not file.is_open())
        {
            throw std::runtime_error("Cannot open file!");
        }

        file.seekg(0, std::ios::end);
        const auto size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (size < 0U)
        {
            throw std::runtime_error("Cannot GET file size!");
        }
        else if (size == 0U)
        {
            throw std::runtime_error("File size is 0!");
        }

        std::string buffer(static_cast<std::size_t>(size), '\0');

        if (not file.read(buffer.data(), size))
        {
            throw std::runtime_error("Cannot read file!");
        }

        return buffer;
    }



    /// @brief Counts how many times a specific character appears in a given file. Checks neither whether the path exists nor whether it refers to a regular file
    ///
    /// @tparam ForNewline: Set to true only if this function is specifically used to count newline characters
    ///
    /// @param path: The path to the file in which the character occurrences will be counted
    /// @param   ch: The character to count
    ///
    /// @return The number of times the character appears in the file
    /// 
    template <bool ForNewline = false>
    auto CharCount_Unchecked (const std::filesystem::path& path, const char& character) -> std::size_t
    {
        std::ifstream file(path, std::ios::binary);

        if (not file.is_open())
        {
            throw std::runtime_error("Cannot open file!");
        }

        const auto& count = static_cast<std::size_t>(std::count_if<>(std::istreambuf_iterator<char>{ file }, {}, [character](const auto& ch) noexcept -> bool { return ch == character; }));

        if constexpr (ForNewline)
        {
            return count + static_cast<std::size_t>(std::filesystem::file_size(path) not_eq 0);
        }
        else
        {
            return count;
        }
    }



    /// @brief Counts how many times a specific character appears in a given file.
    ///
    /// @tparam ForNewline: Set to true only if this function is specifically used to count newline characters
    ///
    /// @param path: The path to the file in which the character occurrences will be counted
    /// @param   ch: The character to count
    ///
    /// @return The number of times the character appears in the file
    /// 
    template <bool ForNewline = false>
    auto CharCount           (const std::filesystem::path& path, const char& character) -> std::size_t
    {
        if (not std::filesystem::exists(path))
        {
            throw std::runtime_error("The given path does NOT exist!");
        }

        if (not std::filesystem::is_regular_file(path))
        {
            throw std::runtime_error("The given path is NOT a regular file!");
        }

        return CharCount_Unchecked<ForNewline>(path, character);
    }



    /// @brief Counts how many times a specific character appears in all regular files within a given directory
    /// 
    /// @tparam     ForNewline: Set to true only if this function is specifically used to count newline characters
    /// 
    /// @param            path: The path to the DIR in which the character occurrences will be counted
    /// @param       character: The character to count
    /// @param         recurse: If true, traverses subdirectories recursively; otherwise, only the top-level directory is scanned
    /// @param extensionFilter: A list of file extensions to filter which files will be read
    /// 
    /// @return The total number of times the character appears in all regular files found in the directory
    /// 
    template <bool ForNewline = false>
    auto CharCount_Dir       (const std::filesystem::path& path, const char& character, const bool& recurse = false, const std::vector<std::string>& extensionFilter = {}) -> std::size_t
    {
        namespace fs = std::filesystem;

        if (not fs::exists(path))
        {
            throw std::runtime_error("The given path does NOT exist!");
        }

        if (not fs::is_directory(path))
        {
            throw std::runtime_error("The given path is NOT a directory!");
        }

        // NOLINTBEGIN(cppcoreguidelines-macro-usage)

        using DirIt = std::variant<fs::recursive_directory_iterator, fs::directory_iterator>;
        
        return std::visit<>(
            [&filters = extensionFilter, ch = character](auto&& it) -> std::size_t
            {
#define FATLIB_FILE_LINECOUNT_DIR_LOOP_GENERATOR(...)                               \
                                                                                    \
                for (const auto& dir_entry : it)                                    \
                {                                                                   \
                    if (fs::is_regular_file(dir_entry) __VA_ARGS__ )                \
                    {                                                               \
                        total += CharCount_Unchecked<ForNewline>(dir_entry, ch);    \
                    }                                                               \
                }

                std::size_t total{};

                if (filters.empty())
                {
                    FATLIB_FILE_LINECOUNT_DIR_LOOP_GENERATOR()
                }
                else
                {
                    FATLIB_FILE_LINECOUNT_DIR_LOOP_GENERATOR(and (std::ranges::find(filters, dir_entry.path().extension().string()) not_eq filters.cend()))
                }

                return total;

#undef FATLIB_FILE_LINECOUNT_DIR_LOOP_GENERATOR
            },
            recurse
                ? DirIt{ fs::recursive_directory_iterator{ path, fs::directory_options::skip_permission_denied } }
                : DirIt{ fs::directory_iterator          { path, fs::directory_options::skip_permission_denied } }
        );

        // NOLINTEND(cppcoreguidelines-macro-usage)
    }



    /// @brief Counts lines in a given file. Checks neither whether the path exists nor whether it refers to a regular file
    ///
    /// @param path: The path to the file in which the lines will be counted
    ///
    /// @return The number of lines in the file
    /// 
    auto LineCount_Unchecked (const std::filesystem::path& path) -> std::size_t
    {
        return CharCount_Unchecked<true>(path, '\n');
    }



    /// @brief Counts lines in a given file
    ///
    /// @param path: The path to the file in which the lines will be counted
    ///
    /// @return The number of lines in the file
    /// 
    auto LineCount           (const std::filesystem::path& path) -> std::size_t
    {
        if (not std::filesystem::exists(path))
        {
            throw std::runtime_error("The given path does NOT exist!");
        }

        if (not std::filesystem::is_regular_file(path))
        {
            throw std::runtime_error("The given path is NOT a regular file!");
        }

        return LineCount_Unchecked(path);
    }



    /// @brief Counts lines in all regular files within a given directory
    /// 
    /// @param            path: The path to the DIR in which the lines will be counted
    /// @param         recurse: If true, traverses subdirectories recursively; otherwise, only the top-level directory is scanned
    /// @param extensionFilter: A list of file extensions to filter which files will be read
    /// 
    /// @return The total number of lines in all regular files found in the directory
    /// 
    auto LineCount_Dir       (const std::filesystem::path& path, const bool& recurse = false, const std::vector<std::string>& extensionFilter = {}) -> std::size_t
    {
        return CharCount_Dir<true>(path, '\n', recurse, extensionFilter);
    }



    /// @brief Returns the name and extension of a regular file from a given filesystem path
    /// 
    /// @param path: The filesystem path to the file
    /// 
    /// @return A pair containing the file name (without extension) and the file extension as strings
    /// 
    auto NameAndExtension    (const std::filesystem::path& path) -> std::pair<std::string, std::string>
    {
        if (not std::filesystem::exists(path))
        {
            throw std::runtime_error("The given path to the file does NOT exist!");
        }

        if (not std::filesystem::is_regular_file(path))
        {
            throw std::runtime_error("The given path is NOT a regular file!");
        }

        return
        {
            path.stem().string(),
            path.extension().string()
        };
    }



    /// @brief Converts a filesystem path to a URI-compatible string
    /// 
    /// @param path: The filesystem path to be converted
    ///
    /// @return A string representing the URI-compatible version of the path
    /// 
    auto ToUriPath           (const std::filesystem::path& path) -> std::string
    {
        const auto& path_str = path.u8string();

        std::string uri;
        uri.reserve(path_str.length());

        for (const auto& ch : path_str)
        {
            if (static_cast<bool>(std::isalnum(ch)) or (ch == '-') or (ch == '_') or (ch == '.') or (ch == '~') or (ch == '/') or (ch == ':'))
            {
                uri.push_back(static_cast<char>(ch));
            }
            else if (ch == '\\')
            {
                uri.push_back('/');
            }
            else
            {
                std::format_to<>(std::back_inserter<>(uri), "%{:02X}", static_cast<std::uint8_t>(ch));
            }
        }

        return uri;
    }



    /// @brief Encrypts or decrypts a file and replaces the original file with the processed output
    /// 
    /// @param  inPath: The path to the input file to be encrypted or decrypted
    /// @param     key: The key used for encryption or decryption
    /// @param outPath: The path to the output file AND its name. If not specified, the file will be encrypted in-place
    /// 
    void EncryptDecrypt      (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path outPath = {})
    {
        namespace fs = std::filesystem;

        const auto& outWasEmpty = outPath.parent_path().empty() or (inPath == outPath);

        if (outWasEmpty)
        {
            outPath = fs::temp_directory_path() / (inPath.stem().string() + "_temp.fat000");
        }
        else if (const auto& dirPath = outPath.parent_path(); not dirPath.empty())
        {
            std::filesystem::create_directories(dirPath);
        }

        EncryptDecrypt_Impl(inPath, key, outPath);

        if (outWasEmpty)
        {
            fs::remove(inPath);
            fs::rename(outPath, inPath);
        }
    }



    /// @brief Encrypts or decrypts all regular files in a directory using a specified key
    /// 
    /// @param          inPath: The path to the input directory containing files to encrypt or decrypt
    /// @param             key: The encryption or decryption key to use
    /// @param         outPath: The output directory path where processed files will be saved. If not specified, the default behavior is used
    /// @param         recurse: If true, processes files in all subdirectories recursively; otherwise, only processes files in the top-level directory. Defaults to false
    /// @param extensionFilter: extensions as a vector of strings to filter the files that will be processed
    /// 
    void EncryptDecrypt_Dir  (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path outPath = {}, const bool& recurse = false, const std::vector<std::string>& extensionFilter = {})
    {
        namespace fs = std::filesystem;

        if (not fs::is_directory(inPath))
        {
            throw std::runtime_error("Input path is NOT a directory!");
        }

        // NOLINTBEGIN(cppcoreguidelines-macro-usage)

        using DirIt = std::variant<fs::recursive_directory_iterator, fs::directory_iterator>;

        std::visit<>(
            [&inPath, &key, &outPath, &filters = extensionFilter](auto&& it) -> void
            {
#define FATLIB_FILE_ENCRYPTDECRYPT_DIR_LOOP_GENERATOR(...)                   \
                                                                             \
                for (const auto& dir_entry : it)                             \
                {                                                            \
                    if (fs::is_regular_file(dir_entry) __VA_ARGS__ )         \
                    {                                                        \
                        const auto& out_path = outPath.empty()               \
                            ?  outPath                                       \
                            : (outPath / fs::relative(dir_entry, inPath))    \
                            ;                                                \
                                                                             \
                        EncryptDecrypt(dir_entry, key, out_path);            \
                    }                                                        \
                }


                if (filters.empty())
                {
                    FATLIB_FILE_ENCRYPTDECRYPT_DIR_LOOP_GENERATOR()
                }
                else
                {
                    FATLIB_FILE_ENCRYPTDECRYPT_DIR_LOOP_GENERATOR(and (std::ranges::find(filters, dir_entry.path().extension().string()) not_eq filters.cend()))
                }

#undef FATLIB_FILE_ENCRYPTDECRYPT_DIR_LOOP_GENERATOR
            },
            recurse
                ? DirIt{ fs::recursive_directory_iterator{ inPath, fs::directory_options::skip_permission_denied } }
                : DirIt{ fs::directory_iterator          { inPath, fs::directory_options::skip_permission_denied } }
        );

        // NOLINTEND(cppcoreguidelines-macro-usage)
    }



    /// @brief Prints the contents of a file as hexadecimal values to the specified output stream (with spaces between those values)
    /// 
    /// @param path: The path to the file whose contents will be printed in hexadecimal format
    /// @param   os: The output stream to which the hexadecimal values will be written. Defaults to std::cout
    /// 
    void PrintHex            (const std::filesystem::path& path, std::ostream& os = std::cout)
    {
        std::ifstream file(path, std::ios::binary);

        if (not file.is_open())
        {
            throw std::runtime_error("Input file CANNOT be opened!");
        }

        {
            char first_byte{};

            if (file.get(first_byte))
            {
                os << std::format<>("{:02X}", static_cast<std::uint8_t>(first_byte));
            }
            else
            {
                return;
            }
        }

        std::vector<std::uint8_t> inbuf(8192U);
        std::string outbuf;
        outbuf.reserve(inbuf.size() * 3U);

        while (file.read(reinterpret_cast<char*>(inbuf.data()), static_cast<std::streamsize>(inbuf.size())))
        {
            for (std::size_t i{}; i < inbuf.size(); ++i)
            {
                std::format_to<>(std::back_inserter<>(outbuf), " {:02X}", inbuf[i]);
            }

            os << outbuf;
            outbuf.clear();
        }

        if (const auto& bytes_left = static_cast<std::size_t>(file.gcount()); bytes_left > 0U)
        {
            for (std::size_t i{}; i < bytes_left; ++i)
            {
                std::format_to<>(std::back_inserter<>(outbuf), " {:02X}", inbuf[i]);
            }

            os << outbuf;
        }
    }
}

// module : private;
