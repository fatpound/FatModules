module FatPound.File;

namespace fatpound::file
{
    auto GetNameAndExtension(const std::string& filename) -> std::pair<std::string, std::string>
    {
        if (not std::filesystem::is_regular_file(filename))
        {
            throw std::runtime_error("The file does not exist!");
        }

        const std::filesystem::path filePath(filename);

        return {
            filePath.stem().string(),
            filePath.extension().string()
        };
    }
}