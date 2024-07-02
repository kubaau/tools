#pragma once

#include "ExtendedRangeStlAlgorithms.hpp"
#include "Typedefs.hpp"

using AStarNodePtr = const class AStarNode*;
using AStarNodePtrs = std::set<AStarNodePtr>;
class AStarNode
{
protected:
    using Distance = u64;

public:
    using Cost = Distance;

    virtual ~AStarNode() = default;

    virtual Distance distance(AStarNodePtr) const = 0;
    virtual Cost heuristicCostEstimate(AStarNodePtr other) const { return distance(other); }
    AStarNodePtrs neighbors(const AStarNodePtrs& others) const
    {
        return copy_if(others, [&](auto node) { return isNeighbor(node); });
    }

protected:
    virtual bool isNeighbor(AStarNodePtr) const = 0;
};

using CameFrom = std::map<AStarNodePtr, AStarNodePtr>;
using Path = std::vector<AStarNodePtr>;

inline auto reconstructPath(const CameFrom& came_from, AStarNodePtr current)
{
    using namespace std;

    Path total_path = {current};
    for (auto it = came_from.find(current); it != cend(came_from); it = came_from.find(current))
        total_path.emplace_back(current = it->second);
    reverse(begin(total_path), end(total_path));
    return total_path;
}

inline auto aStar(const AStarNodePtrs& nodes, AStarNodePtr start, AStarNodePtr goal)
{
    using namespace std;

    // The set of nodes already evaluated
    AStarNodePtrs closed_set;

    // The set of currently discovered nodes that are not evaluated yet.
    // Initially, only the start node is known.
    AStarNodePtrs open_set = {start};

    // For each node, which node it can most efficiently be reached from.
    // If a node can be reached from many nodes, cameFrom will eventually contain the
    // most efficient previous step.
    CameFrom came_from;

    // For each node, the cost of getting from the start node to that node.
    using Score = map<AStarNodePtr, AStarNode::Cost>;
    constexpr auto infinity = numeric_limits<Score::mapped_type>::max();
    Score g_score;
    for (auto node : nodes)
        g_score[node] = infinity;

    // The cost of going from start to start is zero.
    g_score[start] = 0;

    // For each node, the total cost of getting from the start node to the goal
    // by passing by that node. That value is partly known, partly heuristic.
    Score f_score;
    for (auto node : nodes)
        f_score[node] = infinity;

    // For the first node, that value is completely heuristic.
    f_score[start] = start->heuristicCostEstimate(goal);

    while (not open_set.empty())
    {
        const auto current =
            *min_element(open_set, [&](const auto& lhs, const auto& rhs) { return f_score[lhs] < f_score[rhs]; });

        if (current == goal)
            return reconstructPath(came_from, current);

        open_set.erase(current);
        closed_set.insert(current);

        for (const auto& neighbor : current->neighbors(nodes))
        {
            if (closed_set.count(neighbor))
                continue; // Ignore the neighbor which is already evaluated.

            // The distance from start to a neighbor
            const auto tentative_g_score = g_score[current] + current->distance(neighbor);

            if (not open_set.insert(neighbor).second and tentative_g_score >= g_score[neighbor]) // Discover a new node
                continue;

            // This path is the best until now. Record it!
            came_from[neighbor] = current;
            g_score[neighbor] = tentative_g_score;
            f_score[neighbor] = g_score[neighbor] + neighbor->heuristicCostEstimate(goal);
        }
    }

    return Path{};
}
