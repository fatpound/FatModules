module;

export module FatPound.Automata.TLT;

import FatPound.Automata.CFG;

import std;

using std::literals::string_literals::operator ""s;

export namespace fatpound::automata
{
    namespace tlt_v1
    {
        class TLT final
        {
            static constexpr auto scx_recurse_limit_ = 1u;

        public:
            explicit TLT(const CFG& cfgs);
            explicit TLT(const std::string& inputFilename);

            explicit TLT()               = delete;
            explicit TLT(const TLT&)     = delete;
            explicit TLT(TLT&&) noexcept = delete;

            auto operator = (const TLT&)     -> TLT& = delete;
            auto operator = (TLT&&) noexcept -> TLT& = delete;
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

    namespace tlt_v2
    {
        class TLT final
        {
            static constexpr auto scx_RecursionLimit_ = 1u;

        public:
            using Result_t = std::vector<std::pair<std::string, bool>>;


        public:
            explicit TLT(const CFG& cfgs);
            explicit TLT(const std::string& inputFilename);

            explicit TLT()               = delete;
            explicit TLT(const TLT&)     = delete;
            explicit TLT(TLT&&) noexcept = delete;

            auto operator = (const TLT&)     -> TLT& = delete;
            auto operator = (TLT&&) noexcept -> TLT& = delete;
            ~TLT() noexcept(false);


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
}

module : private;
