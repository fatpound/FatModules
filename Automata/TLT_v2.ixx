module;

export module FatPound.Automata.TLT_v2;

import FatPound.Automata.CFG;

import std;

using std::literals::string_literals::operator ""s;

export namespace fatpound::automata
{
    class TLT_v2 final
    {
        static constexpr auto scx_RecursionLimit_ = 1u;

    public:
        using Result_t = std::vector<std::pair<std::string, bool>>;


    public:
        explicit TLT_v2(const CFG& cfgs);
        explicit TLT_v2(const std::string& inputFilename);

        explicit TLT_v2()              = delete;
        explicit TLT_v2(const TLT_v2&) = delete;
        explicit TLT_v2(TLT_v2&&)      = delete;

        auto operator = (const TLT_v2&) -> TLT_v2& = delete;
        auto operator = (TLT_v2&&)      -> TLT_v2& = delete;
        ~TLT_v2() noexcept(false);


    public:
        [[nodiscard]]
        auto GetWords() const noexcept -> Result_t;

        void PrintWords() const;


    protected:


    private:
        struct alignas(64) Node_ final
        {
            explicit Node_(const std::pair<std::string, std::vector<std::string>>& tree);
            explicit Node_(const std::string& str);

            std::vector<Node_*> m_leaves;

            std::string m_item;
        };


    private:
        [[nodiscard]]
        auto GenerateResults_(std::string init_str = ""s, std::size_t index = 0u, std::size_t recursed = 0u) const -> Result_t;

        [[nodiscard]]
        auto IsTerminal_(const std::string& str) const -> bool;

        void Clear_();


    private:
        Result_t m_results_;

        std::vector<Node_*> m_trees_;
    };
}

module : private;
