#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util/shaderhelper.hpp"
#include "util/colourhelper.hpp"
#include "util/log/LoggerFactory.hpp"

#include <iostream>
#include <memory>
#include <utility>

using std::string;
using std::pair;
using std::get;

class UI
{
private:
    static constexpr int ONE_SQUARE_VERTEX_COMPONENT_COUNT = 2 * 3 * 2; // 2 triangles consiting of 3 sets of x and y coords
    static const GLfloat SQUARE_VERTICES[ONE_SQUARE_VERTEX_COMPONENT_COUNT];

    string appName;
    unsigned int width;
    unsigned int height;
    const vector<pair<int, int>> & squares;
    shared_ptr<Logger> logger;

    GLFWwindow * window;

    GLint posId;
    GLint colourId;
    GLint scaleId;
    GLint matrixId;
    GLuint squaresVertexbuffer;
    GLuint vertexArrayId;
    GLuint programId;

    glm::mat4 mvp;

    static pair<unsigned int, unsigned int> adjustPosition(GLFWwindow *, double x, double y);

    static void (* mousePositionCallback)(unsigned int, unsigned int);
    static void (* mouseButtonCallback)(unsigned int, unsigned int);
    static void (* keyboardCallback)(int ascii);

    static unsigned int mousePositionX, mousePositionY;
    static unsigned int squareSize;

    void drawSquares();

    void initGL();
    void setup();
    void teardown();

public:

    UI(const string & appName,
       unsigned int width,
       unsigned int height,
       unsigned int squareSize, const vector<pair<int, int>> & cells);
    ~UI();

    void draw();
    bool isActive();

    void registerMousePositionCallback(void (*)(unsigned int x, unsigned int y));
    void registerMouseButtonCallback(void (*)(unsigned int x, unsigned int y));
    void registerKeyboardCallback(void (*)(int ascii));

    static void mousePositionCallbackWrapper(GLFWwindow * window, double x, double y);
    static void mouseButtonCallbackWrapper(GLFWwindow * window, int button, int action, int mods);
    static void keyboardCallbackWrapper(GLFWwindow * window, int key, int scancode, int action, int mods);
};

