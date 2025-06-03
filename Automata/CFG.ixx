module;

#ifdef __INTELLISENSE__
    #include <algorithm>
#endif

export module FatPound.Automata.CFG;

import std;

export namespace fatpound::automata
{
    class CFG final
    {
        static constexpr auto scx_SymbolDelimiter_          = '|';
        static constexpr auto scx_LanguageDelimiter_        = ',';
        static constexpr auto scx_LanguageContentIndicator_ = "-->";

    public:
        using LanguageName_t = std::string;
        using       Symbol_t = std::string;
        using     Alphabet_t = std::vector<char>;
        using     Language_t = std::pair<LanguageName_t, std::vector<Symbol_t>>;
        using      Grammar_t = std::vector<Language_t>;


    public:
        // The input file should be in the following format:
        //
        // 1st line: The alphabet, the languages' acceptable letters separated by spaces (they must be common)
        // 2nd line: The languages are separated by commas and are defined by their names followed by an arrow which is like this "-->"
        // and followed by the symbols of the language(terminals and non - terminals) separated by a pipe character '|'
        // The separators can be changed. See static constexpr variables below
        //
        // Example:
        // a b  c   d e
        // S --> aa | bX | aXX, X --> ab | b
        //
        explicit CFG(const std::string& inputFilename)
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

        explicit CFG()               = delete;
        explicit CFG(const CFG&)     = delete;
        explicit CFG(CFG&&) noexcept = delete;

        auto operator = (const CFG&)     -> CFG& = delete;
        auto operator = (CFG&&) noexcept -> CFG& = delete;
        ~CFG() noexcept                          = default;


    public:
        [[nodiscard]]
        auto GetGrammar() const -> Grammar_t
        {
            return m_grammar_;
        }


    protected:


    private:
        static void ReadFirstLine_(std::ifstream& inputFile, Alphabet_t& alphabet)
        {
            {
                std::string str;
                std::getline<>(inputFile, str);

                std::stringstream ss{ str };

                char ch{};

                while (ss >> ch)
                {
                    alphabet.push_back(ch);
                }
            }

            std::ranges::sort(alphabet);

            const auto&   [beg, end] = std::ranges::unique(alphabet);
            alphabet.erase(beg, end);
        }


    private:
        void ReadSecondLine_(std::ifstream& inputFile, const Alphabet_t& alphabet)
        {
            std::string str;

            while (std::getline<>(inputFile, str, scx_LanguageDelimiter_))
            {
                {
                    const auto& [beg, end] = std::ranges::remove_if(str, [](const auto& ch) noexcept -> bool { return std::isspace(ch) not_eq 0; });
                    str.erase(beg, end);
                }

                std::string word;

                {
                    const auto& index = str.find(scx_LanguageContentIndicator_);

                    if (index == std::string::npos)
                    {
                        continue;
                    }

                    word = std::string(str.cbegin(), str.cbegin() + static_cast<std::ptrdiff_t>(index));

                    str.erase(0, index + std::string_view{ scx_LanguageContentIndicator_ }.size());
                }

                std::vector<std::string> leaves;

                {
                    std::istringstream iss(str);

                    std::string tempstr;

                    while (std::getline<>(iss, tempstr, scx_SymbolDelimiter_))
                    {
                        if (std::ranges::find(leaves, tempstr) not_eq leaves.cend())
                        {
                            continue;
                        }

                        for (const auto& ch : tempstr)
                        {
                            if (static_cast<bool>(std::islower(ch))
                                and
                                std::ranges::find(alphabet, ch) == alphabet.cend())
                            {
                                throw std::runtime_error("The letter " + std::string{ ch } + " is not in the alphabet!");
                            }
                        }

                        leaves.push_back(tempstr);
                    }
                }

                m_grammar_.emplace_back(std::move<>(word), std::move<>(leaves));
            }
        }


    private:
        Grammar_t m_grammar_;
    };
}

module : private;
