#include "UI.hpp"

void (* UI::mousePositionCallback)(int, int);
void (* UI::mouseButtonCallback)(int, int);
int UI::mousePositionX = 0;
int UI::mousePositionY = 0;
unsigned int UI::squareSize = 10;

UI::UI(const string & appName,
       unsigned int width,
       unsigned int height,
       unsigned int squareSize,
       const vector<pair<int, int>> & cells)
    : appName(appName)
    , width(width)
    , height(height)
    , cells(cells)
{
    this->logger = LoggerFactory::getLogger("UI");
    UI::squareSize = squareSize;
}

UI::~UI()
{

}

void UI::initGL()
{
    *logger << "Initialising OpenGL" << Logger::endl;

    // Initialise GLFW
    *logger << "Initialising GLFW";
    if (!glfwInit())
    {
        *logger << Logger::fail << Logger::endl;
        throw "Failed to initialise GLFW";
    }
    *logger << Logger::ok << Logger::endl;

    // Create window with GLFW
    *logger << " - Creating window with GLFW";
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(
        width,
        height,
        appName.c_str(),
        nullptr,
        nullptr
    );

    if (window == nullptr)
    {
        glfwTerminate();
        *logger << Logger::fail << Logger::endl;
        throw "Failed to create window with GLFW.";
    }
    *logger << Logger::ok << Logger::endl;

    // Make window the current OpenGL context
    *logger << " - Making window the current OpenGL context";
    glfwMakeContextCurrent(window);
    *logger << Logger::ok << Logger::endl;

    // Initialise GLEW
    *logger << " - Initialising GLEW";
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        *logger << Logger::fail << Logger::endl;
        throw "Failed to initialise GLEW";
    }
    *logger << Logger::ok << Logger::endl;

    // Set GLFW Options
    *logger << " - Setting GLFW Options";
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    *logger << Logger::ok << Logger::endl;

    // Set OpenGL Options
    *logger << " - Setting OpenGL Options";
    glClearColor(0.3f, 0.2f, 0.2f, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    *logger << Logger::ok << Logger::endl;

    glfwSetCursorPosCallback(window, &mousePositionCallbackWrapper);
    glfwSetMouseButtonCallback(window, &mouseButtonCallbackWrapper);
}

void UI::drawSquares()
{
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, & mvp[0][0]);

    glm::vec4 colour = colourhelper::rgbHexToVec4("664444");
    glm::vec2 pos = {0, 0};

    glUniform2fv(posId, 1, &pos[0]);
    glUniform4fv(colourId, 1, &colour[0]);
    glUniform1f(scaleId, UI::squareSize);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, squaresVertexbuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));

    unsigned long arraySize = ONE_SQUARE_VERTEX_COMPONENT_COUNT * cells.size();
    GLfloat squaresV[arraySize];
    for (unsigned int i = 0; i < cells.size(); ++i)
    {
        int base = i * ONE_SQUARE_VERTEX_COMPONENT_COUNT;
        for (int j = 0; j < ONE_SQUARE_VERTEX_COMPONENT_COUNT; j+=2)
        {
            squaresV[base + j + 0] = std::get<0>(cells[i]) + SQUARE_VERTICES[j + 0];
            squaresV[base + j + 1] = std::get<1>(cells[i]) + SQUARE_VERTICES[j + 1];
        }
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(squaresV), squaresV, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(squaresV) / sizeof(GLfloat));

    glDisableVertexAttribArray(0);
}

void UI::setup()
{
    *logger << Logger::endl << "Running \033[1m" << appName << "\033[0m" << Logger::endl;

    try
    {
        initGL();
    }
    catch (const char * error)
    {
        *logger << error << Logger::endl;
        exit(-1);
    }

    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    try {
        programId = shaderhelper::createProgram("standard.vertexshader", "standard.fragmentshader");
    }
    catch (const string & error)
    {
        *logger << error << Logger::endl;
        teardown();
        exit(-1);
    }

    posId         = glGetUniformLocation(programId, "offset");
    colourId      = glGetUniformLocation(programId, "colour");
    scaleId       = glGetUniformLocation(programId, "scale");
    matrixId      = glGetUniformLocation(programId, "mvp");

    glm::mat4 projection = glm::ortho(
        0.f,  static_cast<float>(width),
        0.f,  static_cast<float>(height),
        0.0f, 1.0f
    );
    glm::mat4 view = glm::lookAt(
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    glm::mat4 model = glm::mat4(1.0f);

    mvp = projection * view * model;


    glGenBuffers(1, &squaresVertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, squaresVertexbuffer);

}

void UI::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programId);

    //int time = glfwGetTime();
    //*logger << std::to_string(time) << Logger::endl;


    drawSquares();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void UI::teardown()
{
    *logger << "Cleaning up OpenGL" << Logger::endl;

    *logger << " - Deleting OpenGL resources";
    glDeleteBuffers(1, &squaresVertexbuffer);
    glDeleteProgram(programId);
    glDeleteVertexArrays(1, &vertexArrayId);
    *logger << Logger::ok << Logger::endl;

    *logger << " - Terminating GLFW";
    glfwTerminate();
    *logger << Logger::ok << Logger::endl;
}

bool UI::isActive()
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0;
}

const GLfloat UI::SQUARE_VERTICES[] =
{
        0 , 0,
        1 , 0,
        0 , 1,
        1 , 0,
        1 , 1,
        0 , 1
};

void UI::mousePositionCallbackWrapper(GLFWwindow * window, double xpos, double ypos)
{
    auto adjusted = adjustPosition(window, xpos, ypos);
    mousePositionX = std::get<0>(adjusted);
    mousePositionY = std::get<1>(adjusted);
    if (mousePositionCallback != nullptr)
    {
        mousePositionCallback(mousePositionX, mousePositionY);
    }
}

void UI::mouseButtonCallbackWrapper(GLFWwindow * window, int button, int action, int mods)
{
    if (mouseButtonCallback != nullptr && action == GLFW_RELEASE)
    {
        mouseButtonCallback(mousePositionX, mousePositionY);
    }
}

void UI::registerMousePositionCallback(void (* mousePositionCallback)(int, int))
{
    UI::mousePositionCallback = mousePositionCallback;
}

void UI::registerMouseButtonCallback(void (* mouseButtonCallback)(int, int))
{
    UI::mouseButtonCallback = mouseButtonCallback;
}

pair<int, int> UI::adjustPosition(GLFWwindow * window, double x, double y)
{
    int width, height;
    glfwGetWindowSize(window, & width, & height);

    int adjustedX = static_cast<int>(x), adjustedY = static_cast<int>(y);
    if (x < 0) adjustedX = 0;
    if (x > width) adjustedX = width;
    if (y < 0) adjustedY = 0;
    if (y > height) adjustedY = height;

    adjustedX /= UI::squareSize;
    adjustedY = (height - adjustedY) / UI::squareSize;

    return { adjustedX, adjustedY };
}
