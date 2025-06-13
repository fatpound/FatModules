module;

#ifdef __INTELLISENSE__
    #include <variant>
    #include <filesystem>
#endif

export module FatPound.File;

import FatPound.Cryptography.XorCipher;

import std;

namespace fatpound::file
{
    /// @brief Encrypts or decrypts a file using an XOR cipher with the specified key
    /// 
    /// @param  inPath: The path to the input file to be encrypted or decrypted
    /// @param     key: The key to use for the XOR cipher
    /// @param outPath: The path where the output file will be written. If empty or the same as inPath, a temporary file path is generated and assigned
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
            std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(outputFile),
            key
        );
    }
}

export namespace fatpound::file
{
    /// @brief Returns the name and extension of a file from a given filesystem path
    /// 
    /// @param path: The filesystem path to the file
    /// 
    /// @return A pair containing the file name (without extension) and the file extension as strings
    /// 
    auto NameAndExtensionOf  (const std::filesystem::path& path) -> std::pair<std::string, std::string>
    {
        if (not std::filesystem::exists(path))
        {
            throw std::runtime_error("The file does not exist!");
        }

        return
        {
            path.stem().string(),
            path.extension().string()
        };
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
    /// @param  inPath: The path to the input directory containing files to encrypt or decrypt
    /// @param     key: The encryption or decryption key to use
    /// @param outPath: The output directory path where processed files will be saved. If not specified, the default behavior is used
    /// @param recurse: If true, processes files in all subdirectories recursively; otherwise, only processes files in the top-level directory. Defaults to false
    /// 
    void EncryptDecrypt_Dir  (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path outPath = {}, const bool& recurse = false)
    {
        namespace fs = std::filesystem;

        if (not fs::is_directory(inPath))
        {
            throw std::runtime_error("Input path is NOT a directory!");
        }

        using DirIt = std::variant<fs::recursive_directory_iterator, fs::directory_iterator>;

        std::visit<>(
            [&inPath, &key, &outPath](auto&& it) -> void
            {
                for (const auto& path : it)
                {
                    if (fs::is_regular_file(path))
                    {
                        const auto& out_path = outPath.empty()
                            ?  outPath
                            : (outPath / fs::relative(path, inPath))
                            ;

                        EncryptDecrypt(path, key, out_path));
                    }
                }
            },
            recurse
                ? DirIt{ fs::recursive_directory_iterator{ inPath, fs::directory_options::skip_permission_denied } }
                : DirIt{ fs::directory_iterator          { inPath, fs::directory_options::skip_permission_denied } }
        );
    }



#ifndef __GNUC__
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
            throw std::runtime_error("Input file cannot be opened!");
        }

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4686)
#endif
        if (auto ch = file.get(); not file.eof())
        {
            std::print<>(os, "{:02X}", ch);
        }

        for (auto ch = file.get(); not file.eof(); ch = file.get())
        {
            std::print<>(os, " {:02X}", ch);
        }
#ifdef _MSC_VER
#pragma warning (pop)
#endif
    }
#endif
}

module : private;
