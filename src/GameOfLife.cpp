#include <iostream>
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

void GameOfLife::tickSpecial(unsigned int cols, unsigned int rows, bool flip)
{
    cells.clear();
    if (flip)
    {
        for (unsigned int i = 0; i < cols; ++i)
        {
            for (unsigned int j = 0; j < rows; ++j)
            {
                if (((i < cols / 2 && j >= rows / 2) || (i >= cols / 2 && j < rows / 2)) && ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)))
                {
                    cells.push_back({i, j});
                }
            }
        }
    } else
    {
        for (unsigned int i = 0; i < cols; ++i)
        {
            for (unsigned int j = 0; j < rows; ++j)
            {
                if (((i >= cols / 2 && j >= rows / 2) || (i < cols / 2 && j < rows / 2)) && ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)))
                {
                    cells.push_back({i, j});
                }
            }
        }
    }
}

void GameOfLife::addLife(unsigned int x, unsigned int y)
{
    cells.push_back({x, y});
    for (auto cell : cells)
    {
        std::cout << "cell at " << std::get<0>(cell) << ", " << std::get<1>(cell) << std::endl;
    }
}
