#include "GameOfLife.hpp"

GameOfLife::GameOfLife()
    : cells()
{
    logger = LoggerFactory::getLogger("GameOfLife");
}

GameOfLife::~GameOfLife()
{
}

bool GameOfLife::isCellAlive(int x, int y)
{
    return std::find(cells.begin(), cells.end(), pair<int, int>(x, y)) != cells.end();
}

const vector<pair<int, int>> & GameOfLife::getCells()
{
    return cells;
}

void GameOfLife::tick()
{
    //*logger << "tick" << Logger::endl;
    //cells.clear();
}

void GameOfLife::addLife(int x, int y)
{
    if (!isCellAlive(x, y))
    {
        cells.push_back({x, y});
        //*logger << "Added life at ";
    } else
    {
        //*logger << "Unable to add life at ";
    }
    //*logger << std::to_string(x) << ", " << std::to_string(y) << Logger::endl;

}
