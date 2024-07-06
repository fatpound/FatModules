module;

#include <string>

export module FatPound.File;

import std;

export namespace fatpound::file
{
    auto GetNameAndExtension(const std::string& filename) -> std::pair<std::string, std::string>
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
            throw std::runtime_error("The given path is not pointing to a file!");
        }
    }
}