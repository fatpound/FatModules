module;

export module FatPound.File;

import std;

namespace fatpound::file
{
    namespace details
    {
        void EncryptDecrypt_     (const std::filesystem::path& in_path, const std::size_t& key, std::filesystem::path& out_path)
        {
            std::ifstream inputFile(in_path, std::ios::binary);

            if (not inputFile.is_open())
            {
                throw std::runtime_error("Input file cannot be opened!");
            }

            if (out_path.empty() or in_path == out_path)
            {
                out_path = std::filesystem::temp_directory_path().string() + in_path.stem().string() + "_temp.fat000";
            }

            std::ofstream outputFile(out_path, std::ios::binary);

            if (not outputFile.is_open())
            {
                throw std::runtime_error("Cannot create the new version of file!");
            }

            std::minstd_rand rng(static_cast<unsigned int>(key));

            std::transform<>(
                std::istreambuf_iterator<char>(inputFile),
                std::istreambuf_iterator<char>(),
                std::ostreambuf_iterator<char>(outputFile),
                [&rng](const char& ch) noexcept -> char
                {
                    return static_cast<char>(static_cast<decltype(rng)::result_type>(ch) xor rng());
                }
            );
        }
    }

    export
    {
        auto GetNameAndExtension (const std::filesystem::path& path) -> std::pair<std::string, std::string>
        {
            if (not std::filesystem::exists(path))
            {
                throw std::runtime_error("The file does not exist!");
            }

            return {
                path.stem().string(),
                path.extension().string()
            };
        }

        void EncryptDecrypt      (const std::filesystem::path& in_path, const std::size_t& key, std::filesystem::path out_path = {})
        {
            details::EncryptDecrypt_(in_path, key, out_path);

            std::filesystem::remove(in_path);
            std::filesystem::rename(out_path, in_path);
        }
        void EncryptDecrypt_Dir  (const std::filesystem::path& in_path, const std::size_t& key, bool recurse = false)
        {
            namespace fs = std::filesystem;

            if (not fs::is_directory(in_path))
            {
                throw std::runtime_error("Input path is NOT a directory!");
            }

            using DirIt = std::variant<fs::recursive_directory_iterator, fs::directory_iterator>;

            std::visit<>(
                [&key](auto&& it) -> void
                {
                    for (const auto& path : it)
                    {
                        if (fs::is_regular_file(path))
                        {
                            EncryptDecrypt(path, key);
                        }
                    }
                },
                recurse
                    ? DirIt{ fs::recursive_directory_iterator{ in_path, fs::directory_options::skip_permission_denied } }
                    : DirIt{ fs::directory_iterator          { in_path, fs::directory_options::skip_permission_denied } }
            );
        }
    }
}

module : private;
