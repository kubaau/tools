#include "AStar.hpp"
#include "GtestWrapper.hpp"

class Node : public AStarNode
{
public:
    Node(int x = 0, int y = 0) : x(x), y(y) {}
    Node(AStarNodePtr node) { *this = *reinterpret_cast<const Node*>(node); }

    Distance distance(AStarNodePtr other) const override
    {
        const Node o = other;
        return abs(x - o.x) + abs(y - o.y);
    }

    friend ostream& operator<<(ostream& os, const Node& node) { return os << "{" << node.x << ", " << node.y << "}"; }

private:
    bool isNeighbor(AStarNodePtr other) const override { return distance(other) == 1; }

    int x;
    int y;
};

TEST(AStar, a_star)
{
    vector<Node> nodes = {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}};
    AStarNodePtr start = &nodes[0];
    AStarNodePtr goal = &nodes[3];
    print("Nodes:", nodes);

    auto path = aStar(transform<AStarNodePtrs>(nodes, [](const auto& node) { return &node; }), start, goal);

    nodes.clear();
    transform(path, nodes, [](auto node) { return node; });
    print("Path:", nodes);
    EXPECT_EQ(path.size(), 4u);

    nodes = {{0, 0},
             {0, 1},
             {0, 2},
             {0, 3},
             {1, 1},
             {1, 2},
             {1, 3},
             {2, 1},
             {2, 3},
             {3, 0},
             {3, 1},
             {3, 2},
             {3, 3},
             {4, 2},
             {4, 3}};
    start = &nodes[0];
    goal = &nodes[11];
    print("Nodes:", nodes);

    path = aStar(transform<AStarNodePtrs>(nodes, [](const auto& node) { return &node; }), start, goal);
    nodes.clear();
    transform(path, nodes, [](auto node) { return node; });
    print("Path:", nodes);
    EXPECT_EQ(path.size(), 6u);
}
