module;

export module FatPound.Graph.DFS;

import FatPound.Graph.DirectedGraph;
import FatPound.Colors.ARGB;

import std;

namespace fatpound::graph
{
    /// @brief Performs a depth-first search (DFS) visit on a directed graph starting from a given node index, marking node colors and returning a string representation of the traversal order
    /// 
    /// @param  graph: The directed graph to traverse
    /// @param colors: A vector representing the color (state) of each node during traversal
    /// @param  index: The index of the node to start the DFS visit from
    /// 
    /// @return A string containing the traversal order of visited node indices, each followed by a newline
    /// 
    auto DFS_Visit_(const DirectedGraph& graph, std::vector<colors::argb::Color>& colors, const std::size_t& index) -> std::string
    {
        colors[index] = colors::argb::Gray;

        std::string output = std::format<>("{}\n", index);

        for (std::size_t i{}; i < graph.GetNextCount(index); ++i)
        {
            if (const auto& nextIndex = graph.GetNextAt(index, i); colors[nextIndex] == colors::argb::White)
            {
                output += DFS_Visit_(graph, colors, nextIndex);
            }
        }

        colors[index] = colors::argb::Black;

        return output;
    }
}

export namespace fatpound::graph
{
    /// @brief Performs a depth-first search (DFS) traversal on a directed graph and returns the traversal order as a string
    /// 
    /// @param graph: The directed graph to traverse
    /// 
    /// @return A string representing the order in which the nodes are visited during the DFS traversal
    /// 
    auto DFS(const DirectedGraph& graph) -> std::string
    {
        std::string output;

        std::vector<colors::argb::Color> colors(graph.GetNodeCount());

        for (std::size_t i{}; i < graph.GetNodeCount(); ++i)
        {
            if (colors[i] == colors::argb::White)
            {
                output += DFS_Visit_(graph, colors, i);
            }
        }

        return output;
    }
}

// module : private;
