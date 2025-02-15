module;

#include <algorithm>

module FatPound.Automata.TLT;

namespace fatpound::automata
{
    // TLT

    TLT::TLT(const CFG& cfg)
        :
        mc_cfgrammar_(cfg.GetGrammar()),
        m_recursers_(mc_cfgrammar_.size(), 0)
    {
        if (mc_cfgrammar_.size() < 1)
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

    auto TLT::GetWords() const noexcept -> std::vector<std::string>
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

        if (finals.size() > 0u)
        {
            for (const auto& str : finals)
            {
                std::cout << str << '\n';
            }
        }

        if (repeaters.size() > 0u)
        {
            std::cout << "\nRepeaters :\n\n";

            for (const auto& str : repeaters)
            {
                std::cout << str << '\n';
            }
        }

        std::cout << '\n';
    }

    bool TLT::IsTerminal_(const std::string& word) noexcept
    {
        return std::ranges::all_of(word, [](const auto& ch) noexcept -> bool { return std::islower(ch) not_eq 0; });
    }

    void TLT::CreateTree_(Node_* node)
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
    void TLT::CreateInnerTree_(Node_* node)
    {
        for (std::size_t i = 0u; i < node->m_item.size(); ++i)
        {
            const auto& ch = node->m_item[i];

            if (not std::isupper(ch))
            {
                continue;
            }

            const auto& cfg_it = std::ranges::find_if(mc_cfgrammar_, [&](const auto& pair) { return pair.first[0] == ch; });

            std::string leftstr(node->m_item.cbegin(), node->m_item.cbegin() + static_cast<std::ptrdiff_t>(i));
            std::string rightstr(node->m_item.cbegin() + static_cast<std::ptrdiff_t>(i + 1u), node->m_item.cend());

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
                        // const auto [first, last] = rn::remove_if(str, [](const auto& ch) { return std::isupper(ch); });
                        // 
                        // str.erase(first, last);

                        continue;
                    }

                    recursed = true;

                    ++m_recursers_[index];
                }

                const std::string& newstr = leftstr + cfgstr + rightstr;

                Node_* newnode = new Node_(newstr);

                node->m_leaves.push_back(newnode);

                if (recursed or (not IsTerminal_(newstr)))
                {
                    CreateInnerTree_(newnode);
                }
                else
                {
                    m_results_.push_back(newstr);
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

        while (nodes.size() > 0u)
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

    TLT::Node_::Node_(const std::string& item)
        :
        m_item(item)
    {

    }
}
