#pragma once

#include <algorithm>

#include "GameOfLifeInterface.hpp"

class GameOfLife
    : public GameOfLifeInterface
{
public:
    GameOfLife();
    ~GameOfLife();
    const vector<pair<int, int>> & getCells();
    void tick();
    void addLife(int x, int y);
private:
    vector<pair<int, int>> cells;
};
