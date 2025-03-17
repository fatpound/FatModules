module;

module FatPound.Automata.TLT;

namespace fatpound::automata
{
    inline namespace details_v1
    {
        // TLT

        TLT::TLT(const CFG& cfg)
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
        TLT::TLT(const std::string& inputFilename)
            :
            TLT(CFG{ inputFilename })
        {

        }
        TLT::~TLT() noexcept(false)
        {
            Clear_();
        }

        auto TLT::GetWords() const -> std::vector<std::string>
        {
            return m_results_;
        }

        void TLT::PrintWords() const
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

        auto TLT::IsTerminal_(const std::string& word) noexcept -> bool
        {
            return std::ranges::all_of(word, [](const auto& ch) noexcept -> bool { return std::islower(ch) not_eq 0; });
        }

        void TLT::CreateTree_(Node_* const node)
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
        void TLT::CreateInnerTree_(Node_* const node)
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

        void TLT::Clear_()
        {
            if (m_pTree_ == nullptr) [[unlikely]]
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


        // TLT::Node_

        TLT::Node_::Node_(std::string item)
            :
            m_item(std::move<>(item))
        {

        }
    }

    namespace details_v2
    {
        TLT::TLT(const CFG& cfg)
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
        TLT::TLT(const std::string& inputFilename)
            :
            TLT(CFG{ inputFilename })
        {

        }
        TLT::~TLT() noexcept(false)
        {
            Clear_();
        }

        auto TLT::GetWords() const -> Result_t
        {
            return m_results_;
        }

        void TLT::PrintWords() const
        {
            for (const auto& item : m_results_)
            {
                if (item.second)
                {
                    std::cout << item.first << '\n';
                }
            }
        }

        // NOLINTBEGIN(readability-function-cognitive-complexity)
        auto TLT::GenerateResults_(const std::string& init_str, const std::size_t& index, const std::size_t& recursed) const -> Result_t
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

                    tempstrings = std::move(newTempStrings);
                }

                for (const auto& strPair : tempstrings)
                {
                    strings.emplace_back(strPair.first, IsTerminal_(strPair.first));
                }
            }

            return strings;
        }
        // NOLINTEND(readability-function-cognitive-complexity)

        auto TLT::IsTerminal_(const std::string& str) const -> bool
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

        void TLT::Clear_()
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


        // TLT::Node_

        TLT::Node_::Node_(const std::pair<std::string, std::vector<std::string>>& tree)
            :
            m_item(tree.first)
        {
            m_leaves.reserve(tree.second.size());

            for (const auto& str : tree.second)
            {
                m_leaves.push_back(new Node_(str));
            }
        }
        TLT::Node_::Node_(std::string str)
            :
            m_item(std::move<>(str))
        {

        }
    }
}
