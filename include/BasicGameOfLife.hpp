#pragma once

#include <algorithm>
#include <functional>
#include <map>

#include "GameOfLife.hpp"
#include "util/log/LoggerFactory.hpp"

using std::map;

class BasicGameOfLife
    : public GameOfLife
{
public:
    BasicGameOfLife();
    ~BasicGameOfLife();
    const vector<Cell> & getLiveCells();
    vector<Cell> findAdjacentNeighbours(Cell, Cell);
    void tick();
    void reset();
    void addLiveCell(int x, int y);
    bool isLiveCell(int x, int y);
private:
    vector<Cell> cells;
    shared_ptr<Logger> logger;
};
