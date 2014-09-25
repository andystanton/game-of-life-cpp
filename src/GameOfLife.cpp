#include "GameOfLife.hpp"

GameOfLife::GameOfLife()
    : cells()
{
}

GameOfLife::~GameOfLife()
{
}

const vector<pair<int, int>> & GameOfLife::getCells()
{
    return cells;
}

void GameOfLife::tick()
{

}

void GameOfLife::addLife(int x, int y)
{
    if (std::find(cells.begin(), cells.end(), pair<int, int>(x, y)) == cells.end())
    {
        cells.push_back({x, y});
    }

}
