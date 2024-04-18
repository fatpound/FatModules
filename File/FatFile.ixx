// module;

export module FatFile;

import <cstring>;

#if (_MSVC_LANG > 202002L)
import std;
#else
#if (_MSVC_LANG == 202002L)
#ifdef NDEBUG
import std.core;
import std.filesystem;
#else
import <string>;
import <stdexcept>;
import <filesystem>;
import <ranges>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // (_MSVC_LANG == 202002L)
#endif // (_MSVC_LANG > 202002L)

export namespace fatpound::file
{
    std::pair<std::string, std::string> GetNameAndExtension(const std::string& filename)
    {
        if (std::filesystem::is_regular_file(filename))
        {
            const auto& it = std::find(filename.rbegin(), filename.rend(), '.');
            std::size_t dot_index = 0u;

            if (it != filename.rend())
            {
                dot_index = it - filename.rbegin() + 1u;
            }
            
            return {
                std::string(filename.cbegin(), filename.cend() - dot_index),
                std::string(::_strrev(const_cast<char*>(std::string(filename.rbegin(), it).c_str())))
            };
        }
        else
        {
            throw std::invalid_argument("The given path is not pointing to a file!");
        }
    }
}