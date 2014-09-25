#include <memory>

#include "UI.hpp"
#include "GameOfLife.hpp"
#include "util/cli/CLIParser.hpp"


unique_ptr<GameOfLife> life;

long currentTimeMillis()
{
    auto millisDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    return static_cast<long>(millisDuration.count());
}

void mouseButtonCallback(int xpos, int ypos)
{
    std::cout << "mouse clicked at " << xpos << ", " << ypos << std::endl;
    life->addLife(xpos, ypos);
}


int main(int argc, char ** argv)
{
    Configuration c = CLIParser(argc, argv).getConfiguration();

    LoggerFactory::configure(c.getBoolValue("no-colour"));

    unsigned int width = 640;
    unsigned int height = 480;
    unsigned int squareSize = 20;
    //unsigned int cols = width / squareSize;
    //unsigned int rows = height / squareSize;

    life = unique_ptr<GameOfLife>(new GameOfLife());

    UI ui("Game of Life", width, height, squareSize, life->getCells());


    ui.setup();
    ui.registerMouseButtonCallback(&mouseButtonCallback);

    while (ui.isActive())
    {
        //long seconds = currentTimeMillis() / 1000;

        //life->tickSpecial(cols, rows, seconds % 2 == 0);

        ui.draw();
    }

    ui.teardown();



    return 0;
}
