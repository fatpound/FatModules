module;

export module FatPound.DSA.DirectedGraph;

import std;

export namespace fatpound::dsa
{
    class DirectedGraph final
    {
    public:
        explicit DirectedGraph(const std::string& filePath)
        {
            std::ifstream my_file(filePath, std::ios_base::binary);

            if (not my_file.is_open())
            {
                throw std::runtime_error("Input file cannot be opened!");
            }

            while (not my_file.eof())
            {
                std::string line;
                std::getline<>(my_file, line);

                std::stringstream ss;
                ss << line;

                std::vector<std::ptrdiff_t> vec;

                while (not ss.eof())
                {
                    std::ptrdiff_t x;
                    ss >> x >> std::ws;

                    vec.push_back(x);
                }

                m_adj_.push_back(std::move<>(vec));
                m_nexts_.emplace_back();
            }

            my_file.close();

            m_node_count_ = m_adj_.size();

            for (std::size_t i{}; i < m_node_count_; ++i)
            {
                for (std::size_t j{}; j < m_node_count_; ++j)
                {
                    if (m_adj_[i][j] not_eq 0U)
                    {
                        m_nexts_[i].push_back(j);

                        ++m_edge_count_;
                    }
                }
            }
        }
        
        explicit DirectedGraph()                         = delete;
        explicit DirectedGraph(const DirectedGraph&)     = delete;
        explicit DirectedGraph(DirectedGraph&&) noexcept = delete;

        auto operator = (const DirectedGraph&)     -> DirectedGraph& = delete;
        auto operator = (DirectedGraph&&) noexcept -> DirectedGraph& = delete;
        ~DirectedGraph() noexcept                                    = default;


    public:
        auto GetAdjAt (const std::size_t& u, const std::size_t& v) const noexcept -> std::ptrdiff_t
        {
            return m_adj_[u][v];
        }
        auto GetNextAt(const std::size_t& u, const std::size_t& v) const noexcept -> std::size_t
        {
            return m_nexts_[u][v];
        }

        auto GetNextCount(const std::size_t& idx) const noexcept -> std::size_t
        {
            return m_nexts_[idx].size();
        }

        auto GetNodeCount() const noexcept -> std::size_t
        {
            return m_node_count_;
        }
        auto GetEdgeCount() const noexcept -> std::size_t
        {
            return m_edge_count_;
        }


    protected:


    private:
        std::vector<std::vector<std::ptrdiff_t>> m_adj_;
        std::vector<std::vector<std::size_t>>    m_nexts_;

        std::size_t m_node_count_{};
        std::size_t m_edge_count_{};
    };
}

module : private;
