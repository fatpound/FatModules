module;

#ifdef __INTELLISENSE__
#include <algorithm>
#endif

export module FatPound.Automata.TLT_v2;

import FatPound.Automata.CFG;

import std;

namespace fatpound::automata
{
    class TLT final
    {
        static constexpr auto scx_RecursionLimit_ = 1U;

    public:
        using Result_t = std::vector<std::pair<std::string, bool>>;


    public:
        explicit TLT(const CFG& cfg)
        {
            {
                const auto& cfgrammar = cfg.GetGrammar();

                m_trees_.reserve(cfgrammar.size());

                for (const auto& tree : cfgrammar)
                {
                    m_trees_.push_back(new Node_(tree));
                }
            }

            m_results_ = GenerateResults_("", 0U, 0U);
        }
        explicit TLT(const std::string& inputFilename)
            :
            TLT(CFG{ inputFilename })
        {

        }

        explicit TLT()               = delete;
        explicit TLT(const TLT&)     = delete;
        explicit TLT(TLT&&) noexcept = delete;

        auto operator = (const TLT&)     -> TLT& = delete;
        auto operator = (TLT&&) noexcept -> TLT& = delete;
        ~TLT() noexcept(false)
        {
            Clear_();
        }


    public:
        [[nodiscard]]
        auto GetWords() const -> Result_t
        {
            return m_results_;
        }

        void PrintWords() const
        {
            for (const auto& item : m_results_)
            {
                if (item.second)
                {
                    std::cout << item.first << '\n';
                }
            }
        }


    protected:


    private:
        // NOLINTBEGIN(altera-struct-pack-align)
        struct alignas(64) Node_ final
        {
            explicit Node_(const std::pair<std::string, std::vector<std::string>>& tree)
                :
                m_item(tree.first)
            {
                m_leaves.reserve(tree.second.size());

                for (const auto& str : tree.second)
                {
                    m_leaves.push_back(new Node_(str));
                }
            }
            explicit Node_(std::string item) noexcept
                :
                m_item(std::move<>(item))
            {

            }

            std::vector<Node_*> m_leaves;

            std::string m_item;
        };
        // NOLINTEND(altera-struct-pack-align)


    private:
        // NOLINTBEGIN(readability-function-cognitive-complexity)
        [[nodiscard]]
        auto GenerateResults_(const std::string& init_str = "", const std::size_t& index = {}, const std::size_t& recursed = {}) const -> Result_t
        {
            Result_t strings;

            for (const auto& node : m_trees_[index]->m_leaves)
            {
                Result_t tempstrings;

                tempstrings.emplace_back(init_str, false);

                for (const auto& ch : node->m_item)
                {
                    Result_t newTempStrings;

                    for (const auto& strPair : tempstrings)
                    {
                        std::string& str = newTempStrings.emplace_back(strPair).first;

                        const auto insertedindex = newTempStrings.size() - 1;

                        const auto it = std::find_if<>(m_trees_.cbegin() + static_cast<std::ptrdiff_t>(index), m_trees_.cend(), [&](const auto& tree) -> bool { return ch == tree->m_item[0]; });

                        if (it == m_trees_.cend())
                        {
                            str += ch;
                        }
                        else
                        {
                            const auto tree_index = static_cast<std::size_t>(it - m_trees_.cbegin());
                            const auto will_recurse = static_cast<::std::size_t>((tree_index == index) ? 1 : 0);

                            if (recursed < scx_RecursionLimit_)
                            {
                                // const auto size = tempstrings.size();

                                // bool deleted = false;

                                const std::string tempstr = strPair.first;

                                if (tempstr.empty())
                                {
                                    continue;
                                }

                                const auto vec = GenerateResults_(tempstr, tree_index, recursed + will_recurse);

                                for (const auto& pair : vec)
                                {
                                    newTempStrings.emplace_back(pair);
                                }

                                newTempStrings.erase(newTempStrings.begin() + static_cast<std::ptrdiff_t>(insertedindex));
                            }
                            else
                            {
                                str += ch;
                            }
                        }
                    }

                    tempstrings = std::move<>(newTempStrings);
                }

                for (const auto& strPair : tempstrings)
                {
                    strings.emplace_back(strPair.first, IsTerminal_(strPair.first));
                }
            }

            return strings;
        }
        // NOLINTEND(readability-function-cognitive-complexity)

        [[nodiscard]]
        auto IsTerminal_(const std::string& str) const -> bool
        {
            for (const auto& tree : m_trees_)
            {
                if (std::ranges::any_of(str, [&](const auto& ch) -> bool { return ch == (tree->m_item[0]); }))
                {
                    return false;
                }
            }

            return true;
        }

        void Clear_()
        {
            std::deque<Node_*> nodes;

            for (auto& tree : m_trees_)
            {
                if (tree not_eq nullptr)
                {
                    nodes.push_back(tree);
                }
                else
                {
                    continue;
                }

                while (not nodes.empty())
                {
                    Node_* node = nodes.back();

                    nodes.pop_back();

                    for (auto& leaf : node->m_leaves)
                    {
                        nodes.push_back(leaf);
                    }

                    delete node;
                }
            }
        }


    private:
        Result_t m_results_;

        std::vector<Node_*> m_trees_;
    };
}

module : private;
