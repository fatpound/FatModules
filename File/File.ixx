module;

export module FatPound.File;

import std;

export namespace fatpound::file
{
    auto GetNameAndExtension(const std::string& filename) -> std::pair<std::string, std::string>;
}

module : private;