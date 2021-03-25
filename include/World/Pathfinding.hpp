
#pragma once

#include <vector>

struct Node {
    Node *parent;
    float cost;
};

class Pathfinding {
    public:
            Node *astar(int startx, int starty, int endx, int endy, std::vector<std::vector<int>> map);
};