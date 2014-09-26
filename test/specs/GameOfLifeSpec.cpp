#include <bandit/bandit.h>

#include "GameOfLife.hpp"

using namespace bandit;

go_bandit([]()
{

    describe("life", []()
    {
        shared_ptr<GameOfLifeInterface> life;

        before_each([&]() {
            life = shared_ptr<GameOfLifeInterface>(new GameOfLife());
        });

        it("contains no live cells initially", [&]()
        {
            AssertThat(life->getCells(), IsEmpty());
        });

        it("can have cells added to it", [&]()
        {
            life->addLife(0, 0);
            life->addLife(0, 1);
            AssertThat(life->getCells(), HasLength(2));
        });

        it("can be inspected for life at a particular location", [&]()
        {
            AssertThat(life->isCellAlive(0, 0), IsFalse());
            AssertThat(life->isCellAlive(1, 1), IsFalse());
            life->addLife(1, 1);
            AssertThat(life->isCellAlive(0, 0), IsFalse());
            AssertThat(life->isCellAlive(1, 1), IsTrue());
        });

        describe("underpopulation", [&]()
        {
            it("results in the cell's death", [&]()
            {
                life->addLife(0, 0);
                AssertThat(life->getCells(), HasLength(1));

                life->tick();
                AssertThat(life->getCells(), HasLength(0));
            });
        });

        describe("overpopulation", [&]()
        {

        });
    });
});
