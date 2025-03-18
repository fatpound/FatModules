module;

export module FatPound.Automata.TLT;

import FatPound.Automata.CFG;

import std;

export namespace fatpound::automata
{
    inline namespace details_v1
    {
        class TLT final
        {
            static constexpr auto scx_recurse_limit_ = 1U;

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
            auto GetWords() const -> std::vector<std::string>;

            void PrintWords() const;


        protected:


        private:
            // NOLINTBEGIN(altera-struct-pack-align)
            struct alignas(64) Node_ final
            {
                explicit Node_(std::string item);

                std::vector<Node_*> m_leaves;

                std::string m_item;
            };
            // NOLINTEND(altera-struct-pack-align)


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

            Node_* m_pTree_{};
        };
    }

    namespace details_v2
    {
        class TLT final
        {
            static constexpr auto scx_RecursionLimit_ = 1U;

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
            auto GetWords() const -> Result_t;

            void PrintWords() const;


        protected:


        private:
            // NOLINTBEGIN(altera-struct-pack-align)
            struct alignas(64) Node_ final
            {
                explicit Node_(const std::pair<std::string, std::vector<std::string>>& tree);
                explicit Node_(std::string item);

                std::vector<Node_*> m_leaves;

                std::string m_item;
            };
            // NOLINTEND(altera-struct-pack-align)


        private:
            [[nodiscard]]
            auto GenerateResults_(const std::string& init_str = "", const std::size_t& index = {}, const std::size_t& recursed = {}) const -> Result_t;

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
