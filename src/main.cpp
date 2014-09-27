#include <memory>

#include "UI.hpp"
#include "BasicGameOfLife.hpp"

#include "util/cli/CLIParser.hpp"
#include "util/timehelper.hpp"

static const int WINDOW_WIDTH = 640;
static const int WINDOW_HEIGHT = 480;
static const int SQUARE_SIZE = 10;
static const int DEFAULT_TICK_FREQUENCY = 512;
static const int DEFAULT_RANDOM_LIFE_COUNT = (WINDOW_WIDTH / SQUARE_SIZE) * (WINDOW_HEIGHT / SQUARE_SIZE) / 4;

unique_ptr<GameOfLife> life;
int tickFrequency = DEFAULT_TICK_FREQUENCY;
bool paused = false;

void addRandomLife(int count)
{
    for (int i = 0; i < count; ++i)
    {
        bool done = false;
        while (!done)
        {
            auto candidateX = rand() % (WINDOW_WIDTH / SQUARE_SIZE);
            auto candidateY = rand() % (WINDOW_HEIGHT / SQUARE_SIZE);

            if (!life->isLiveCell(candidateX, candidateY))
            {
                life->addLiveCell(candidateX, candidateY);
                done = true;
            }
        }
    }
}

void mouseButtonCallback(unsigned int x, unsigned int y)
{
    life->addLiveCell(x, y);
}

void keyCallback(int key)
{
    switch(key)
    {
        case 45: if (tickFrequency < 4096) tickFrequency *= 2; break;
        case 61: if (tickFrequency > 64) tickFrequency /= 2; break;
        case 48: tickFrequency = DEFAULT_TICK_FREQUENCY; break;
        case 32: paused = !paused; break;
        case 81: addRandomLife(DEFAULT_RANDOM_LIFE_COUNT); break;
        case 87:
            paused = true;
            tickFrequency = DEFAULT_TICK_FREQUENCY;
            life->reset();
            break;
        default: break;
    }
}

int main(int argc, char ** argv)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Configuration c = CLIParser(argc, argv).getConfiguration();
    LoggerFactory::configure(c.getBoolValue("no-colour"));

    life = unique_ptr<GameOfLife>(new BasicGameOfLife());
    addRandomLife(DEFAULT_RANDOM_LIFE_COUNT);

    UI ui("Game of Life", WINDOW_WIDTH, WINDOW_HEIGHT, SQUARE_SIZE, life->getLiveCells());

    ui.registerMouseButtonCallback(& mouseButtonCallback);
    ui.registerKeyboardCallback(& keyCallback);

    long lastUpdate = timehelper::currentTimeMillis();

    while (ui.isActive())
    {
        if (timehelper::currentTimeMillis() - lastUpdate > tickFrequency)
        {
            lastUpdate = timehelper::currentTimeMillis();
            if (!paused) life->tick();
        }
        ui.draw();
    }

    return 0;
}
