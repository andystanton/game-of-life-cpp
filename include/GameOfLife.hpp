#pragma once

#include <vector>
#include <utility>

using std::vector;
using std::pair;

class GameOfLife
{
public:
    GameOfLife();
    ~GameOfLife();
    const vector<pair<int, int>> & getCells();
    void tick();
    void tickSpecial(unsigned int, unsigned int, bool);
    void addLife(unsigned int x, unsigned int y);
private:
    vector<pair<int, int>> cells;
};
