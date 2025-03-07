module;

export module FatPound.File;

import std;

namespace fatpound::file
{
    export
    {
        auto GetNameAndExtension  (const std::filesystem::path& filename) -> std::pair<std::string, std::string>;

        void EncryptDecrypt       (const std::filesystem::path& in_filepath, const std::size_t& key, std::filesystem::path out_filepath = {});
        void EncryptDecrypt_Dir   (const std::filesystem::path& in_filepath, const std::size_t& key, const bool recurse = false);
    }
    
    namespace details
    {
        void EncryptDecrypt_      (const std::filesystem::path& in_filepath, const std::size_t& key, std::filesystem::path& out_filepath);
    }
}

module : private;