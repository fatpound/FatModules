module;

export module FatPound.File;

import FatPound.DSA.Cryptography.XorCipher;

import std;

namespace fatpound::file
{
    void EncryptDecrypt_Impl (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path& outPath)
    {
        std::ifstream inputFile(inPath, std::ios::binary);

        if (not inputFile.is_open())
        {
            throw std::runtime_error("Input file cannot be opened!");
        }

        if (outPath.empty() or inPath == outPath)
        {
            outPath = std::filesystem::temp_directory_path().string() + inPath.stem().string() + "_temp.fat000";
        }

        std::ofstream outputFile(outPath, std::ios::binary);

        if (not outputFile.is_open())
        {
            throw std::runtime_error("Cannot create the new version of file!");
        }

        dsa::cryptography::ApplyXorCipherWithKey<>(
            std::istreambuf_iterator<char>(inputFile),
            std::istreambuf_iterator<char>(),
            std::ostreambuf_iterator<char>(outputFile),
            key
        );
    }
}

export namespace fatpound::file
{
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

    void EncryptDecrypt      (const std::filesystem::path& inPath, const std::size_t& key, std::filesystem::path outPath = {})
    {
        EncryptDecrypt_Impl(inPath, key, outPath);

        std::filesystem::remove(inPath);
        std::filesystem::rename(outPath, inPath);
    }
    void EncryptDecrypt_Dir  (const std::filesystem::path& inPath, const std::size_t& key, const bool& recurse = false)
    {
        namespace fs = std::filesystem;

        if (not fs::is_directory(inPath))
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
                ? DirIt{ fs::recursive_directory_iterator{ inPath, fs::directory_options::skip_permission_denied } }
                : DirIt{ fs::directory_iterator          { inPath, fs::directory_options::skip_permission_denied } }
        );
    }
}

module : private;
