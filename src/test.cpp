#include <string>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "LarpPrerequisites.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "SceneGraph.hpp"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

// Properties
GLuint screenWidth = 800, screenHeight = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();
void error_callback(int error, const char* description);

// Camera
Larp::pSceneGraph graph;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main(void)
{
    // Init GLFW
    if (!glfwInit())
        throw std::runtime_error(std::string(__FILE__) + std::string(" : line ") + std::to_string(__LINE__) + std::string(" :: glfwInit() failed!"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr); // Windowed
    if (window == nullptr)
        throw std::runtime_error(std::string(__FILE__) + std::string(" : line ") + std::to_string(__LINE__) + std::string(" :: GLFWwindow* = nullptr"));
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    Larp::Shader shader("shaders/default.vert", "shaders/default.frag");
    Larp::Model nanosuit("assets/nanosuit.obj");
    Larp::pEntity entity = Larp::Entity::create(shader, nanosuit);

    graph = Larp::SceneGraph::singleton();
    Larp::pNode node1 = graph->create_child_node();
    Larp::pNode node = node1->create_child();
    node->set_scale(0.1f, 0.1f, 0.1f);
    node->attach_entity(entity);

    // Create floor
    Larp::pNode node2 = graph->create_child_node();
    Larp::Model floor("assets/floor.obj");
    Larp::pEntity floorE = Larp::Entity::create(shader, floor);
    node2->attach_entity(floorE);

    // Testing the SceneGraph clear
    // node1.reset(new Larp::Node());
    // node.reset(new Larp::Node());

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        node->yaw(deltaTime * 32.0);
        node->pitch(deltaTime * 23.0);
        node->roll(deltaTime * 17.0);

        glm::mat4 projection = glm::perspective(camera._zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.get_view_matrix();
        graph->draw(view, projection);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void Do_Movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.process_keyboard(Camera::FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.process_keyboard(Camera::BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.process_keyboard(Camera::LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.process_keyboard(Camera::RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_C)
        graph->clear();

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.process_mouse_movement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
    camera.process_mouse_scroll(y_offset);
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
