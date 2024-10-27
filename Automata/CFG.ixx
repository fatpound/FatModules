module;

export module FatPound.Automata.CFG;

import std;

using std::vector, std::string, std::pair;

export namespace fatpound::automata
{
    class CFG final
    {
        using GrammarType = std::vector<std::pair<std::string, std::vector<std::string>>>;

    public:
        // The input file should be in the following format:
        //
        // 1st line: The languages' acceptable letters seperated by spaces (they must be common)
        // 2nd line: The languages are sepeareted by commas and are defined by their names followed by an arrow which is like this "-->"
        // and followed by the symbols of the language(terminals and non - terminals) seperated by a pipe character '|'
        // The seperators can be changed. See static constexprs below
        //
        // Example:
        // a b  c   d e
        // S --> aa | bX | aXX, X --> ab | b
        //
        explicit CFG(const std::string& inputFilename);

        explicit CFG() = delete;
        explicit CFG(const CFG& src) = delete;
        explicit CFG(CFG&& src) = delete;

        auto operator = (const CFG& src) -> CFG& = delete;
        auto operator = (CFG&& src)      -> CFG& = delete;
        ~CFG() noexcept = default;


    public:
        [[nodiscard]]
        auto GetGrammar() const noexcept -> GrammarType;


    protected:


    private:
        void ReadFirstLine_(std::ifstream& inputFile, std::vector<char>& alphabet);
        void ReadSecondLine_(std::ifstream& inputFile, std::vector<char>& alphabet);


    private:
        static constexpr auto scx_language_seperator_         = ',';
        static constexpr auto scx_language_word_seperator_    = '|';
        static constexpr auto scx_language_content_seperator_ = "-->";


    private:
        GrammarType m_grammar_;
    };
}