module;

export module FatPound.Algorithm.Graph.DFS;

import FatPound.DSA.DirectedGraph;
import FatPound.Utility.Color;

import std;

namespace fatpound::algorithm
{
    /// @brief Performs a depth-first search (DFS) visit on a directed graph starting from a given node index, marking node colors and returning a string representation of the traversal order
    /// 
    /// @param  graph: The directed graph to traverse
    /// @param colors: A vector representing the color (state) of each node during traversal
    /// @param  index: The index of the node to start the DFS visit from
    /// 
    /// @return A string containing the traversal order of visited node indices, each followed by a newline
    /// 
    auto DFS_Visit_(const dsa::DirectedGraph& graph, std::vector<utility::Color>& colors, const std::size_t& index) -> std::string
    {
        colors[index] = colors::Gray;

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4686)
#endif
        std::string output = std::format<>("{}\n", index);
#ifdef _MSC_VER
#pragma warning (pop)
#endif

        for (std::size_t i{}; i < graph.GetNextCount(index); ++i)
        {
            if (const auto& nextIndex = graph.GetNextAt(index, i); colors[nextIndex] == colors::White)
            {
                output += DFS_Visit_(graph, colors, nextIndex);
            }
        }

        colors[index] = colors::Black;

        return output;
    }
}

export namespace fatpound::algorithm
{
    /// @brief Performs a depth-first search (DFS) traversal on a directed graph and returns the traversal order as a string
    /// 
    /// @param graph: The directed graph to traverse
    /// 
    /// @return A string representing the order in which the nodes are visited during the DFS traversal
    /// 
    auto DFS(const dsa::DirectedGraph& graph) -> std::string
    {
        std::string output;

        std::vector<utility::Color> colors(graph.GetNodeCount());

        for (std::size_t i{}; i < graph.GetNodeCount(); ++i)
        {
            if (colors[i] == colors::White)
            {
                output += DFS_Visit_(graph, colors, i);
            }
        }

        return output;
    }
}

module : private;
