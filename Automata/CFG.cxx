module;

#include <algorithm>

module FatPound.Automata.CFG;

namespace fatpound::automata
{
    CFG::CFG(const std::string& inputFilename)
    {
        std::ifstream inputFile(inputFilename);

        if (not inputFile.is_open())
        {
            throw std::runtime_error("Input file cannot be opened for [InputtingCFG]!");
        }

        Alphabet_t alphabet;

        ReadFirstLine_(inputFile, alphabet);
        ReadSecondLine_(inputFile, alphabet);
    }

    auto CFG::GetGrammar() const noexcept -> Grammar_t
    {
        return m_grammar_;
    }
    
    void CFG::ReadFirstLine_(std::ifstream& inputFile, Alphabet_t& alphabet)
    {
        // duzelt?
        {
            std::string str;

            std::getline(inputFile, str);

            {
                std::stringstream ss;

                ss << str;

                char ch;

                while (ss >> ch)
                {
                    alphabet.push_back(ch);
                }
            }
        }

        std::sort(alphabet.begin(), alphabet.end());

        const auto it = std::unique(alphabet.begin(), alphabet.end());

        alphabet.erase(it, alphabet.end());
    }
    void CFG::ReadSecondLine_(std::ifstream& inputFile, const Alphabet_t& alphabet)
    {
        std::string str;

        while (std::getline(inputFile, str, scx_LanguageDelimiter_))
        {
            {
                const auto& it = std::remove_if(str.begin(), str.end(), [](const auto& ch) noexcept -> bool { return std::isspace(ch) not_eq 0; });

                str.erase(it, str.end());
            }

            const auto& index = str.find(scx_LanguageContentIndicator_);

            if (index not_eq std::string::npos)
            {
                std::string word(str.cbegin(), str.cbegin() + static_cast<std::ptrdiff_t>(index));

                {
                    constexpr auto lciLen = std::string_view{scx_LanguageContentIndicator_}.size();

                    str.erase(0, index + lciLen);
                }

                std::vector<std::string> leaves;

                std::istringstream iss(str);

                std::string tempstr;

                while (std::getline(iss, tempstr, scx_SymbolDelimiter_))
                {
                    if (std::find(leaves.begin(), leaves.end(), tempstr) == leaves.cend())
                    {
                        for (const auto& ch : tempstr)
                        {
                            if (std::islower(ch) and std::find(alphabet.cbegin(), alphabet.cend(), ch) == alphabet.cend())
                            {
                                throw std::runtime_error("The letter " + std::string{ ch } + " is not in the alphabet!");
                            }
                        }

                        leaves.push_back(tempstr);
                    }
                }

                m_grammar_.emplace_back(std::move(word), std::move(leaves));
            }
        }
    }
}
