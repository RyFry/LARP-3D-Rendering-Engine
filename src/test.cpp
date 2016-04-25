#include <string>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "LarpPrerequisites.hpp"

#include "Camera.hpp"
#include "ConfigurationLoader.hpp"
#include "Model.hpp"
#include "PhysicsWorld.hpp"
#include "PhysicsMeshColliderBuilder.hpp"
#include "SceneGraph.hpp"
#include "Shader.hpp"

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
Larp::SceneGraphPtr graph = Larp::SceneGraph::singleton();
PhysicsWorld* world = new PhysicsWorld();
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat delta_time = 0.0f;
GLfloat last_frame = 0.0f;

int main(void)
{
    Larp::ConfigurationLoader config("larp.cfg");
    screenWidth = config.get_width();
    screenHeight = config.get_height();
    // Init GLFW
    if (!glfwInit())
        throw std::runtime_error(std::string(__FILE__) + std::string(" : line ") + std::to_string(__LINE__) + std::string(" :: glfwInit() failed!"));
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, config.is_resizable());
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, config.get_title().c_str(), nullptr, nullptr); // Windowed
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

    // Setting up PhysicsWorld
    world->init_objects();

    Larp::Shader shader("shaders/default.vert", "shaders/default.frag");
    Larp::ModelPtr level = Larp::Model::create("assets/LEVEL.obj");
    Larp::EntityPtr entity = Larp::Entity::create(shader, level);

    Larp::NodePtr node11 = graph->create_child_node();
    Larp::NodePtr node12 = graph->create_child_node();

    Larp::NodePtr node21 = node11->create_child();
    node21->set_scale(0.1f, 0.1f, 0.1f);
    node21->attach_entity(entity);


    PhysicsMeshColliderBuilder physics_level_builder = PhysicsMeshColliderBuilder("assets/LEVEL.obj");
    physics_level_builder.set_mass(0.0);
    physics_level_builder.set_local_inertia(btVector3(0.0, 0.0, 0.0));
    physics_level_builder.set_user_pointer(node21);

    PhysicsMeshColliderPtr physics_level = physics_level_builder.build();

    world->get_dynamics_world()->addRigidBody(physics_level->get_rigid_body());

    GLfloat frame_rate_limiter = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        frame_rate_limiter += delta_time;
        if (frame_rate_limiter > 1.0 / 60.0)
            frame_rate_limiter -= 1.0 / 60.0;
        else
            continue;

        world->get_dynamics_world()->stepSimulation(1.0f / 60.0f);

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // node11->yaw(delta_time * 32.0);
        // node11->pitch(delta_time * 23.0);
        // node11->roll(delta_time * 17.0);

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
    if (keys[GLFW_KEY_W])
        camera.process_keyboard(Camera::FORWARD, delta_time);
    if (keys[GLFW_KEY_S])
        camera.process_keyboard(Camera::BACKWARD, delta_time);
    if (keys[GLFW_KEY_A])
        camera.process_keyboard(Camera::LEFT, delta_time);
    if (keys[GLFW_KEY_D])
        camera.process_keyboard(Camera::RIGHT, delta_time);
    if (keys[GLFW_KEY_SPACE])
        camera.process_keyboard(Camera::UP, delta_time);
    if (keys[GLFW_KEY_LEFT_SHIFT])
        camera.process_keyboard(Camera::DOWN, delta_time);
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
