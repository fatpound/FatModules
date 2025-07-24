module;

export module FatPound.Graph.BFS;

import FatPound.Graph.DirectedGraph;
import FatPound.Colors.ARGB;

import std;

export namespace fatpound::graph
{
    /// @brief Performs a breadth-first search (BFS) traversal on a directed graph starting from node 0 and returns the traversal order as a string
    /// 
    /// @param graph: The directed graph to traverse
    /// 
    /// @return A string representing the order in which nodes are visited during BFS, with each node encoded as a lowercase letter starting from 'a'
    /// 
    auto BFS(const DirectedGraph& graph) -> std::string
    {
        std::vector<colors::argb::Color> colors(graph.GetNodeCount());

        std::queue<std::size_t> queue;
        queue.push(0);

        std::string output;

        while (not queue.empty())
        {
            const auto& u = queue.front();
            queue.pop();

            for (std::size_t i{}; i < graph.GetNextCount(u); ++i)
            {
                if (const auto& v = graph.GetNextAt(u, i); colors[v] == colors::argb::White)
                {
                    colors[v] = colors::argb::Gray;
                    queue.push(v);
                }
            }

            colors[u] = colors::argb::Black;

            output += static_cast<char>('a' + u);
        }

        return output;
    } 
}

// module : private;
