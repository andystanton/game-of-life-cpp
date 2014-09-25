#pragma once

#include <vector>
#include <utility>

using std::vector;
using std::pair;

class GameOfLifeInterface
{
public:
    virtual const vector<pair<int, int>> & getCells() = 0;
    virtual void addLife(int x, int y) = 0;
    virtual void tick() = 0;
    virtual ~GameOfLifeInterface() {};
};