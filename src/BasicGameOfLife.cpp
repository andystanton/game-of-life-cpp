#include <memory>
#include "BasicGameOfLife.hpp"

BasicGameOfLife::BasicGameOfLife()
    : cells()
{
    logger = LoggerFactory::getLogger("BasicGameOfLife");
}

BasicGameOfLife::~BasicGameOfLife()
{
}

bool BasicGameOfLife::isLiveCell(int x, int y)
{
    return std::find(cells.begin(), cells.end(), Cell(x, y)) != cells.end();
}

const vector<pair<int, int>> & BasicGameOfLife::getLiveCells()
{
    return cells;
}

void BasicGameOfLife::tick()
{
    vector<Cell> newCells;
    map<Cell, int> deadCandidates;

    for (auto a : cells)
    {
        int neighbourCount = 0;
        for (auto b : cells)
        {
            if (a != b) {
                auto aX = a.first; auto aY = a.second;
                auto bX = b.first; auto bY = b.second;
                auto diffX = bX - aX; auto diffY = bY - aY;

                if (abs(diffX) < 2 && abs(diffY) < 2) {
                    neighbourCount += 1;
                }

                for (auto adjacentCell : findAdjacentNeighbours(a, b))
                {
                    if (!isLiveCell(adjacentCell.first, adjacentCell.second)) deadCandidates[adjacentCell] += 1;
                }
            }
        }

        if (neighbourCount == 2 || neighbourCount == 3) {
            newCells.push_back(a);
        }
    }

    for (auto entry : deadCandidates)
    {
        if (entry.second == 4 || entry.second  == 6) newCells.push_back(entry.first);
    }

    cells.swap(newCells);
}

void BasicGameOfLife::addLiveCell(int x, int y)
{
    if (!isLiveCell(x, y)) cells.push_back({x, y});
}

vector<GameOfLife::Cell> BasicGameOfLife::findAdjacentNeighbours(GameOfLife::Cell a, GameOfLife::Cell b)
{
    vector<Cell> adjacent;

    auto aX = a.first; auto aY = a.second;
    auto bX = b.first; auto bY = b.second;
    auto diffX = bX - aX; auto diffY = bY - aY;

    if (abs(diffX) == 2 && abs(diffY) == 2)
    {
        adjacent.push_back({bX - diffX / abs(diffX), bY - diffY / abs(diffY)});
    }
    else if(abs(diffX) == 1 && abs(diffY) == 1)
    {
        adjacent.push_back({bX - diffX / abs(diffX), bY});
        adjacent.push_back({bX, bY - diffY / abs(diffY)});
    }
    else if(abs(diffX) == 1 && diffY == 0)
    {
        adjacent.push_back({aX, aY - 1});
        adjacent.push_back({aX, aY + 1});
        adjacent.push_back({bX, aY - 1});
        adjacent.push_back({bX, aY + 1});
    }
    else if(abs(diffY) == 1 && diffX == 0)
    {
        adjacent.push_back({aX - 1, aY});
        adjacent.push_back({aX + 1, aY});
        adjacent.push_back({aX - 1, bY});
        adjacent.push_back({aX + 1, bY});
    }
    else if(abs(diffX) == 2 && diffY == 0)
    {
        adjacent.push_back({aX + diffX/abs(diffX), aY});
        adjacent.push_back({aX + diffX/abs(diffX), aY - 1});
        adjacent.push_back({aX + diffX/abs(diffX), aY + 1});
    }
    else if(diffX == 0 && abs(diffY) == 2)
    {
        adjacent.push_back({aX, aY + diffY/abs(diffY)});
        adjacent.push_back({aX - 1, aY + diffY/abs(diffY)});
        adjacent.push_back({aX + 1, aY + diffY/abs(diffY)});
    }

    return adjacent;
}

void BasicGameOfLife::reset()
{
    cells.clear();
}
