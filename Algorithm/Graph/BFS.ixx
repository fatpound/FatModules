module;

export module FatPound.Algorithm.Graph.BFS;

import FatPound.DSA.DirectedGraph;
import FatPound.Utility.Color;

import std;

export namespace fatpound::algorithm
{
    auto BFS(const dsa::DirectedGraph& graph) -> std::string
    {
        std::vector<utility::Color> colors(graph.GetNodeCount());

        std::queue<std::size_t> queue;
        queue.push(0);

        std::string output;

        while (not queue.empty())
        {
            const auto& u = queue.front();
            queue.pop();

            for (std::size_t i{}; i < graph.GetNextCount(u); ++i)
            {
                if (const auto& v = graph.GetNextAt(u, i); colors[v] == colors::White)
                {
                    colors[v] = colors::Gray;
                    queue.push(v);
                }
            }

            colors[u] = colors::Black;

            output += static_cast<char>('a' + u);
        }

        return output;
    } 
}

module : private;
