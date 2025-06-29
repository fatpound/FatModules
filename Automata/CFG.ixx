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

            ReadLine1_(inputFile, alphabet);
            ReadLine2_(inputFile, alphabet, m_grammar_);
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
        static auto GenerateLanguageSymbols_(const Symbol_t& symbol, const Alphabet_t& alphabet) -> std::vector<Symbol_t>
        {
            std::vector<Symbol_t> symbols;

            std::istringstream iss(symbol);

            std::string tempstr;

            while (std::getline<>(iss, tempstr, scx_SymbolDelimiter_))
            {
                if (std::ranges::find(symbols, tempstr) not_eq symbols.cend())
                {
                    continue;
                }

                for (const auto& ch : tempstr)
                {
                    if ((std::islower(ch) not_eq 0)
                        and
                        std::ranges::find(alphabet, ch) == alphabet.cend())
                    {
                        throw std::runtime_error("The letter " + std::string{ ch } + " is not in the alphabet!");
                    }
                }

                symbols.push_back(tempstr);
            }

            return symbols;
        }

        static auto GetLanguageName_  (const std::string& linestr) -> std::string
        {
            return { linestr.cbegin(), linestr.cbegin() + static_cast<std::ptrdiff_t>(GetLanguageCIIdx_(linestr)) };
        }
        static auto GetLanguageCIIdx_ (const std::string& linestr) -> std::size_t
        {
            const auto idx = linestr.find(scx_LanguageContentIndicator_);

            if (idx not_eq std::string::npos)
            {
                return idx;
            }

            throw std::runtime_error("Cannot find language content indicator in line!");
        }

        static void ReadLine1_(std::ifstream& inputFile,       Alphabet_t& alphabet)
        {
            {
                std::stringstream ss;

                {
                    std::string str;
                    std::getline<>(inputFile, str);

                    ss << str;
                }

                for (char ch{}; ss >> ch; void())
                {
                    alphabet.push_back(ch);
                }
            }

            std::ranges::sort(alphabet);

            const auto&   [beg, end] = std::ranges::unique(alphabet);
            alphabet.erase(beg, end);
        }
        static void ReadLine2_(std::ifstream& inputFile, const Alphabet_t& alphabet, Grammar_t& grammar)
        {
            for (std::string str; std::getline<>(inputFile, str, scx_LanguageDelimiter_); void())
            {
                {
                    const auto& [beg, end] = std::ranges::remove_if(str, [](const auto& ch) noexcept -> bool { return std::isspace(ch) not_eq 0; });
                    str.erase(beg, end);
                }

                grammar.emplace_back(
                    GetLanguageName_(str),
                    GenerateLanguageSymbols_(str.substr(GetLanguageCIIdx_(str) + std::string_view{ scx_LanguageContentIndicator_ }.size()), alphabet)
                );
            }
        }
        

    private:
        Grammar_t  m_grammar_;
    };
}

module : private;
