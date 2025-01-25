module;

export module FatPound.Automata.TLT;

import FatPound.Automata.CFG;

import std;

export namespace fatpound::automata
{
    class TLT final
    {
        static constexpr auto scx_recurse_limit_ = 1u;

    public:
        explicit TLT(const CFG& cfgs);
        explicit TLT(const std::string& inputFilename);

        explicit TLT() = delete;
        explicit TLT(const TLT& src) = delete;
        explicit TLT(TLT&& src) = delete;

        auto operator = (const TLT& src) -> TLT& = delete;
        auto operator = (TLT&& src)      -> TLT& = delete;
        ~TLT() noexcept(false);


    public:
        [[nodiscard]]
        auto GetWords() const noexcept -> std::vector<std::string>;

        void PrintWords() const;


    protected:


    private:
        struct alignas(64) Node_ final
        {
            explicit Node_(const std::string& item);

            std::vector<Node_*> m_leaves;

            std::string m_item;
        };


    private:
        static auto IsTerminal_(const std::string& word) noexcept -> bool;


    private:
        void CreateTree_     (Node_* node);
        void CreateInnerTree_(Node_* node);

        void Clear_();


    private:
        const CFG::Grammar_t mc_cfgrammar_;

        std::vector<std::string> m_results_;

        std::vector<std::size_t> m_recursers_;

        Node_* m_pTree_ = nullptr;
    };
}

module : private;
