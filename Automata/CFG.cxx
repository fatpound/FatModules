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

        ReadFirstLine_ (inputFile, alphabet);
        ReadSecondLine_(inputFile, alphabet);
    }

    auto CFG::GetGrammar() const noexcept -> Grammar_t
    {
        return m_grammar_;
    }
    
    void CFG::ReadFirstLine_ (std::ifstream& inputFile, Alphabet_t& alphabet)
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

        std::ranges::sort(alphabet);

        const auto it = std::ranges::unique(alphabet);

        alphabet.erase(it.begin(), it.end());
    }
    void CFG::ReadSecondLine_(std::ifstream& inputFile, Alphabet_t& alphabet)
    {
        std::string str;

        while (std::getline(inputFile, str, scx_LanguageDelimiter_))
        {
            {
                const auto& it = std::ranges::remove_if(str, [](const auto& ch) noexcept -> bool { return std::isspace(ch) not_eq 0; });

                str.erase(it.begin(), it.end());
            }

            const auto& index = str.find(scx_LanguageContentIndicator_);

            if (index not_eq std::string::npos)
            {
                std::string word(str.cbegin(), str.cbegin() + static_cast<std::ptrdiff_t>(index));

                str.erase(0, index + std::strlen(scx_LanguageContentIndicator_));

                std::vector<std::string> leaves;

                std::istringstream iss(str);

                std::string tempstr;

                while (std::getline(iss, tempstr, scx_SymbolDelimiter_))
                {
                    if (std::ranges::find(leaves, tempstr) == leaves.cend())
                    {
                        for (const auto& ch : tempstr)
                        {
                            if (std::islower(ch) && std::ranges::find(alphabet, ch) == alphabet.cend())
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
