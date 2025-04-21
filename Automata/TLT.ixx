module;

#ifdef __INTELLISENSE__
#include <algorithm>
#endif

export module FatPound.Automata.TLT;

import FatPound.Automata.CFG;

import std;

export namespace fatpound::automata
{
    class TLT final
    {
        static constexpr auto scx_recurse_limit_ = 1U;

    public:
        explicit TLT(const CFG& cfg)
                :
                mc_cfgrammar_(cfg.GetGrammar()),
                m_recursers_(mc_cfgrammar_.size(), 0)
            {
                if (mc_cfgrammar_.empty())
                {
                    throw std::runtime_error("There is no input!");
                }

                m_pTree_ = new Node_(mc_cfgrammar_[0].first);

                for (const auto& leaf_str : mc_cfgrammar_[0].second)
                {
                    m_pTree_->m_leaves.push_back(new Node_(leaf_str));
                }

                CreateTree_(m_pTree_);
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
        auto GetWords() const -> std::vector<std::string>
            {
                return m_results_;
            }

        void PrintWords() const
            {
                std::vector<std::string> finals;
                std::vector<std::string> repeaters;

                for (const auto& str : m_results_)
                {
                    if (std::ranges::find(finals, str) == finals.cend())
                    {
                        finals.push_back(str);
                    }
                    else if (std::ranges::find(repeaters, str) == repeaters.cend())
                    {
                        repeaters.push_back(str);
                    }
                }

                if (not finals.empty())
                {
                    for (const auto& str : finals)
                    {
                        std::cout << str << '\n';
                    }
                }

                if (not repeaters.empty())
                {
                    std::cout << "\nRepeaters :\n\n";

                    for (const auto& str : repeaters)
                    {
                        std::cout << str << '\n';
                    }
                }

                std::cout << '\n';
            }


    protected:


    private:
        // NOLINTBEGIN(altera-struct-pack-align)
        struct alignas(64) Node_ final
        {
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
        static auto IsTerminal_(const std::string& word) noexcept -> bool
            {
                return std::ranges::all_of(word, [](const auto& ch) noexcept -> bool { return std::islower(ch) not_eq 0; });
            }


    private:
        void CreateTree_     (Node_* node)
            {
                m_results_.reserve(node->m_leaves.size());

                for (auto& leaf : node->m_leaves)
                {
                    if (IsTerminal_(leaf->m_item))
                    {
                        m_results_.push_back(leaf->m_item);

                        continue;
                    }

                    CreateInnerTree_(leaf);
                }
            }
        void CreateInnerTree_(Node_* node)
            {
                for (std::size_t i{}; i < node->m_item.size(); ++i)
                {
                    const auto& ch = node->m_item[i];

                    if (not static_cast<bool>(std::isupper(ch)))
                    {
                        continue;
                    }

                    const auto& cfg_it = std::ranges::find_if(mc_cfgrammar_, [&](const auto& pair) { return pair.first[0] == ch; });

                    const std::string leftstr(node->m_item.cbegin(), node->m_item.cbegin() + static_cast<std::ptrdiff_t>(i));
                    const std::string rightstr(node->m_item.cbegin() + static_cast<std::ptrdiff_t>(i + 1U), node->m_item.cend());

                    const std::size_t index = static_cast<std::size_t>(cfg_it - mc_cfgrammar_.cbegin());

                    node->m_leaves.reserve(node->m_leaves.size() + cfg_it->second.size());

                    for (const auto& cfgstr : cfg_it->second)
                    {
                        // string str = cfgstr;

                        bool recursed = false;

                        if (cfgstr.contains(ch))
                        {
                            if (m_recursers_[index] >= scx_recurse_limit_)
                            {
                                // const auto& [first, last] = std::ranges::remove_if(str, [](const auto& ch) { return std::isupper(ch); });
                                // 
                                // str.erase(first, last);

                                continue;
                            }

                            recursed = true;

                            ++m_recursers_[index];
                        }

                        {
                            std::string newstr = leftstr;

                            newstr += cfgstr;
                            newstr += rightstr;

                            auto* newnode = new Node_(newstr);

                            node->m_leaves.push_back(newnode);

                            if (recursed or (not IsTerminal_(newstr)))
                            {
                                CreateInnerTree_(newnode);
                            }
                            else
                            {
                                m_results_.push_back(newstr);
                            }
                        }

                        if (recursed)
                        {
                            --m_recursers_[index];
                        }
                    }
                }
            }

        void Clear_()
            {
                if (m_pTree_ == nullptr)
                {
                    return;
                }

                std::deque<Node_*> nodes;

                nodes.push_back(m_pTree_);

                while (not nodes.empty())
                {
                    Node_* const node = nodes.back();

                    nodes.pop_back();

                    for (auto& leaf : node->m_leaves)
                    {
                        nodes.push_back(leaf);
                    }

                    delete node;
                }
            }


    private:
        const CFG::Grammar_t mc_cfgrammar_;

        std::vector<std::string> m_results_;

        std::vector<std::size_t> m_recursers_;

        Node_* m_pTree_{};
    };
}

module : private;
