#include <bandit/bandit.h>

#include "BasicGameOfLife.hpp"

using std::unique_ptr;

using namespace bandit;

go_bandit([]()
{
    describe("life", []()
    {
        unique_ptr<GameOfLife> life;

        before_each([&]() {
            life = unique_ptr<GameOfLife>(new BasicGameOfLife());
        });

        it("contains no live cells initially", [&]()
        {
            AssertThat(life->getLiveCells(), IsEmpty());
        });

        it("can have cells added to it", [&]()
        {
            life->addLiveCell(0, 0);
            life->addLiveCell(0, 1);

            AssertThat(life->getLiveCells(), HasLength(2));
        });

        it("can be inspected for live cells at a particular location", [&]()
        {
            AssertThat(life->isLiveCell(0, 0), IsFalse());
            AssertThat(life->isLiveCell(1, 1), IsFalse());

            life->addLiveCell(1, 1);

            AssertThat(life->isLiveCell(0, 0), IsFalse());
            AssertThat(life->isLiveCell(1, 1), IsTrue());
        });

        it("can list the cells who share two live cells as a neighbour", [&]()
        {
            // diagonal 2 away
            vector<GameOfLife::Cell> case1a = life->findAdjacentNeighbours({5, 6}, {7, 8});
            vector<GameOfLife::Cell> expected1a = { GameOfLife::Cell(6, 7) };

            AssertThat(case1a, EqualsContainer(expected1a));

            vector<GameOfLife::Cell> case1b = life->findAdjacentNeighbours({5, 6}, {3, 8});
            vector<GameOfLife::Cell> expected1b = { GameOfLife::Cell(4, 7) };

            AssertThat(case1b, EqualsContainer(expected1b));

            vector<GameOfLife::Cell> case1c = life->findAdjacentNeighbours({5, 6}, {3, 4});
            vector<GameOfLife::Cell> expected1c = { GameOfLife::Cell(4, 5) };

            AssertThat(case1c, EqualsContainer(expected1c));

            vector<GameOfLife::Cell> case1d = life->findAdjacentNeighbours({5, 6}, {7, 4});
            vector<GameOfLife::Cell> expected1d = { GameOfLife::Cell(6, 5) };

            AssertThat(case1d, EqualsContainer(expected1d));

            // diagonal 1 away
            vector<GameOfLife::Cell> case2a = life->findAdjacentNeighbours({8, 20}, {9, 21});

            AssertThat(case2a, HasLength(2));
            AssertThat(case2a, Contains(GameOfLife::Cell(8, 21)));
            AssertThat(case2a, Contains(GameOfLife::Cell(9, 20)));

            vector<GameOfLife::Cell> case2b = life->findAdjacentNeighbours({8, 20}, {7, 21});

            AssertThat(case2b, HasLength(2));
            AssertThat(case2b, Contains(GameOfLife::Cell(8, 21)));
            AssertThat(case2b, Contains(GameOfLife::Cell(7, 20)));

            vector<GameOfLife::Cell> case2c = life->findAdjacentNeighbours({8, 20}, {7, 19});

            AssertThat(case2c, HasLength(2));
            AssertThat(case2c, Contains(GameOfLife::Cell(8, 19)));
            AssertThat(case2c, Contains(GameOfLife::Cell(7, 20)));

            vector<GameOfLife::Cell> case2d = life->findAdjacentNeighbours({8, 20}, {9, 19});

            AssertThat(case2d, HasLength(2));
            AssertThat(case2d, Contains(GameOfLife::Cell(8, 19)));
            AssertThat(case2d, Contains(GameOfLife::Cell(9, 20)));

            // horizontal 1 away
            vector<GameOfLife::Cell> case3a = life->findAdjacentNeighbours({12, 13}, {13, 13});

            AssertThat(case3a, HasLength(4));
            AssertThat(case3a, Contains(GameOfLife::Cell(12, 14)));
            AssertThat(case3a, Contains(GameOfLife::Cell(12, 12)));
            AssertThat(case3a, Contains(GameOfLife::Cell(13, 14)));
            AssertThat(case3a, Contains(GameOfLife::Cell(13, 12)));

            vector<GameOfLife::Cell> case3b = life->findAdjacentNeighbours({13, 13}, {12, 13});

            AssertThat(case3b, HasLength(4));
            AssertThat(case3b, Contains(GameOfLife::Cell(12, 14)));
            AssertThat(case3b, Contains(GameOfLife::Cell(12, 12)));
            AssertThat(case3b, Contains(GameOfLife::Cell(13, 14)));
            AssertThat(case3b, Contains(GameOfLife::Cell(13, 12)));

            // vertical 1 away
            vector<GameOfLife::Cell> case4a = life->findAdjacentNeighbours({10, 10}, {10, 9});

            AssertThat(case4a, HasLength(4));
            AssertThat(case4a, Contains(GameOfLife::Cell(11, 10)));
            AssertThat(case4a, Contains(GameOfLife::Cell( 9, 10)));
            AssertThat(case4a, Contains(GameOfLife::Cell(11,  9)));
            AssertThat(case4a, Contains(GameOfLife::Cell( 9,  9)));

            vector<GameOfLife::Cell> case4b = life->findAdjacentNeighbours({10, 9}, {10, 10});

            AssertThat(case4b, HasLength(4));
            AssertThat(case4b, Contains(GameOfLife::Cell(11, 10)));
            AssertThat(case4b, Contains(GameOfLife::Cell( 9, 10)));
            AssertThat(case4b, Contains(GameOfLife::Cell(11,  9)));
            AssertThat(case4b, Contains(GameOfLife::Cell( 9,  9)));

            // horizontal 2 away
            vector<GameOfLife::Cell> case5a = life->findAdjacentNeighbours({6, 6}, {4, 6});

            AssertThat(case5a, HasLength(3));
            AssertThat(case5a, Contains(GameOfLife::Cell(5, 5)));
            AssertThat(case5a, Contains(GameOfLife::Cell(5, 6)));
            AssertThat(case5a, Contains(GameOfLife::Cell(5, 7)));

            vector<GameOfLife::Cell> case5b = life->findAdjacentNeighbours({6, 6}, {8, 6});

            AssertThat(case5b, HasLength(3));
            AssertThat(case5b, Contains(GameOfLife::Cell(7, 5)));
            AssertThat(case5b, Contains(GameOfLife::Cell(7, 6)));
            AssertThat(case5b, Contains(GameOfLife::Cell(7, 7)));

            // vertical 2 away
            vector<GameOfLife::Cell> case6a = life->findAdjacentNeighbours({10, 8}, {10, 10});

            AssertThat(case6a, HasLength(3));
            AssertThat(case6a, Contains(GameOfLife::Cell(9, 9)));
            AssertThat(case6a, Contains(GameOfLife::Cell(10, 9)));
            AssertThat(case6a, Contains(GameOfLife::Cell(11, 9)));

            vector<GameOfLife::Cell> case6b = life->findAdjacentNeighbours({10, 8}, {10, 6});

            AssertThat(case6b, HasLength(3));
            AssertThat(case6b, Contains(GameOfLife::Cell(9, 7)));
            AssertThat(case6b, Contains(GameOfLife::Cell(10, 7)));
            AssertThat(case6b, Contains(GameOfLife::Cell(11, 7)));
        });

        describe("underpopulation", [&]()
        {
            it("results in the cell's death", [&]()
            {
                AssertThat(life->getLiveCells(), HasLength(0));

                life->addLiveCell(0, 0);

                AssertThat(life->getLiveCells(), HasLength(1));

                life->tick();

                AssertThat(life->getLiveCells(), HasLength(0));

                life->reset();

                AssertThat(life->getLiveCells(), HasLength(0));

                life->addLiveCell(0, 0);
                life->addLiveCell(1, 0);

                AssertThat(life->getLiveCells(), HasLength(2));

                life->tick();

                AssertThat(life->getLiveCells(), HasLength(0));
            });
        });

        describe("survival", [&]()
        {
            it("results in the cell existing to the next generation when there are two neighbouring cells", [&]()
            {
                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->addLiveCell(0, 0);
                life->addLiveCell(0, 1);
                life->addLiveCell(1, 0);

                AssertThat(life->isLiveCell(0, 0), IsTrue());

                life->tick();

                AssertThat(life->isLiveCell(0, 0), IsTrue());

                life->reset();

                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->addLiveCell(0, 0);
                life->addLiveCell(0, 1);
                life->addLiveCell(1, 0);
                life->addLiveCell(1, 1);

                AssertThat(life->isLiveCell(0, 0), IsTrue());

                life->tick();

                AssertThat(life->isLiveCell(0, 0), IsTrue());
            });

            it("results in the cell existing to the next generation when there are three neighbouring cells", [&]()
            {
                AssertThat(life->isLiveCell(0, 1), IsFalse());

                life->addLiveCell(0, 0);
                life->addLiveCell(0, 1);
                life->addLiveCell(0, 2);
                life->addLiveCell(1, 1);

                AssertThat(life->isLiveCell(0, 1), IsTrue());

                life->tick();

                AssertThat(life->isLiveCell(0, 1), IsTrue());
            });
        });

        describe("overpopulation", [&]()
        {
            it("results in a cell's death if it has more than three live neighbours", [&]()
            {
                // 4 neighbours
                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->addLiveCell(1, 1);
                life->addLiveCell(0, 0);
                life->addLiveCell(0, 1);
                life->addLiveCell(0, 2);
                life->addLiveCell(1, 2);

                AssertThat(life->isLiveCell(1, 1), IsTrue());

                life->tick();

                AssertThat(life->isLiveCell(1, 1), IsFalse());

                // 5 neighbours
                life->reset();

                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->addLiveCell(1, 1);
                life->addLiveCell(0, 0);
                life->addLiveCell(0, 1);
                life->addLiveCell(0, 2);
                life->addLiveCell(1, 2);
                life->addLiveCell(2, 2);

                AssertThat(life->isLiveCell(1, 1), IsTrue());

                life->tick();

                AssertThat(life->isLiveCell(1, 1), IsFalse());

                // 6 neighbours
                life->reset();

                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->addLiveCell(1, 1);
                life->addLiveCell(0, 0);
                life->addLiveCell(0, 1);
                life->addLiveCell(0, 2);
                life->addLiveCell(1, 2);
                life->addLiveCell(2, 2);
                life->addLiveCell(2, 1);

                AssertThat(life->isLiveCell(1, 1), IsTrue());

                life->tick();

                AssertThat(life->isLiveCell(1, 1), IsFalse());

                // 7 neighbours
                life->reset();

                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->addLiveCell(1, 1);
                life->addLiveCell(0, 0);
                life->addLiveCell(0, 1);
                life->addLiveCell(0, 2);
                life->addLiveCell(1, 2);
                life->addLiveCell(2, 2);
                life->addLiveCell(2, 1);
                life->addLiveCell(2, 0);

                AssertThat(life->isLiveCell(1, 1), IsTrue());

                life->tick();

                AssertThat(life->isLiveCell(1, 1), IsFalse());

                // 8 neighbours
                life->reset();

                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->addLiveCell(1, 1);
                life->addLiveCell(0, 0);
                life->addLiveCell(0, 1);
                life->addLiveCell(0, 2);
                life->addLiveCell(1, 2);
                life->addLiveCell(2, 2);
                life->addLiveCell(2, 1);
                life->addLiveCell(2, 0);
                life->addLiveCell(1, 0);

                AssertThat(life->isLiveCell(1, 1), IsTrue());

                life->tick();

                AssertThat(life->isLiveCell(1, 1), IsFalse());
            });
        });

        describe("reproduction", [&]()
        {
            it("results in a dead cell becoming alive if it has exactly three neighbours", [&]()
            {
                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->addLiveCell(0, 1);
                life->addLiveCell(1, 0);
                life->addLiveCell(1, 1);

                AssertThat(life->isLiveCell(0, 0), IsFalse());

                life->tick();

                AssertThat(life->isLiveCell(0, 0), IsTrue());

                life->reset();

                AssertThat(life->getLiveCells(), IsEmpty());
                AssertThat(life->isLiveCell(0, 0), IsFalse());
                AssertThat(life->isLiveCell(0, 2), IsFalse());

                life->addLiveCell(0, 1);
                life->addLiveCell(1, 1);
                life->addLiveCell(2, 1);

                AssertThat(life->isLiveCell(1, 0), IsFalse());
                AssertThat(life->isLiveCell(1, 2), IsFalse());

                life->tick();

                AssertThat(life->isLiveCell(1, 0), IsTrue());
                AssertThat(life->isLiveCell(1, 2), IsTrue());

                // toad test
                life->reset();

                AssertThat(life->isLiveCell(1, 1), IsFalse());

                life->addLiveCell(1, 0);
                life->addLiveCell(0, 2);
                life->addLiveCell(0, 1);

                AssertThat(life->isLiveCell(1, 1), IsFalse());

                life->tick();

                AssertThat(life->isLiveCell(1, 1), IsTrue());
            });
        });
    });
});
