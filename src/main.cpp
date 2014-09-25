#include <memory>

#include "UI.hpp"
#include "GameOfLife.hpp"

#include "util/cli/CLIParser.hpp"
#include "util/timehelper.hpp"

unique_ptr<GameOfLifeInterface> life;

void mouseButtonCallback(unsigned int x, unsigned int y)
{
    life->addLife(x, y);
}

int main(int argc, char ** argv)
{
    Configuration c = CLIParser(argc, argv).getConfiguration();
    LoggerFactory::configure(c.getBoolValue("no-colour"));

    life = unique_ptr<GameOfLifeInterface>(new GameOfLife());

    UI ui("Game of Life", 640, 480, 5, life->getCells());

    ui.setup();
    ui.registerMouseButtonCallback(& mouseButtonCallback);

    long lastUpdate = timehelper::currentTimeMillis();

    while (ui.isActive())
    {
        if (timehelper::currentTimeMillis() - lastUpdate > 1000)
        {
            lastUpdate = timehelper::currentTimeMillis();
            life->tick();
        }
        ui.draw();
    }

    ui.teardown();


    return 0;
}
