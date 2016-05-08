#include <memory>
#include <string>
#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/ConfigurationLoader.hpp"
#include "Larp/Model.hpp"
#include "Larp/SceneGraph.hpp"
#include "Larp/Shader.hpp"
#include "Larp/SkyBox.hpp"

#include "Camera.hpp"

#include "Physics/PhysicsMeshColliderBuilder.hpp"
#include "Physics/PhysicsObjectBuilder.hpp"
#include "Physics/PhysicsPlayerController.hpp"
#include "Physics/PhysicsWorld.hpp"

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
void make_floor(std::unique_ptr<PhysicsWorld>& physics_world);

// Camera
Larp::SceneGraphPtr graph = Larp::SceneGraph::singleton();
std::unique_ptr<PhysicsWorld> world;
std::unique_ptr<PhysicsPlayerController> player;
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
    {
        THROW_RUNTIME_ERROR("glfwInit() failed!");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, config.is_resizable());
    //glfwWindowHint(GLFW_SAMPLES, 4);

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, config.get_title().c_str(), nullptr, nullptr); // Windowed
    if (window == nullptr)
    {
        THROW_RUNTIME_ERROR("GLFWwindow* = nullptr");
    }
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
    glDepthFunc(GL_LESS);
    //glEnable(GL_MULTISAMPLE);

    // Setting up PhysicsWorld
    world.reset(new PhysicsWorld());
    world->init_objects();

    Larp::ModelPtr level = Larp::Model::create("assets/LEVEL/LEVEL.obj");
    Larp::EntityPtr entity = Larp::Entity::create(level);
    entity->set_directional_shadows(true);
    Larp::DirectionalLightPtr dir_light = Larp::LightFactory::create_directional_light(0.5, -1.0, 1.0);
    dir_light->set_ambient_intensity(0.2, 0.2, 0.2);
    //Larp::PointLightPtr point_light = Larp::LightFactory::create_point_light();

    //point_light->set_ambient_color(4.0f, 2.0f, 6.0f);
    //point_light->set_position(0.0f, 2.0f, -5.0f);

    //graph->remove_light(dir_light);
    Larp::NodePtr node11 = graph->create_child_node();
    Larp::NodePtr node12 = graph->create_child_node();

    Larp::NodePtr node21 = node11->create_child();
    //node21->set_scale(0.1f, 0.1f, 0.1f);
    node21->attach_entity(entity);

    PhysicsMeshColliderBuilder physics_level_builder = PhysicsMeshColliderBuilder("assets/LEVEL/LEVEL.obj");
    physics_level_builder.set_mass(0.0);
    physics_level_builder.set_restitution(1.0);
    physics_level_builder.set_user_pointer(node21);

    PhysicsMeshColliderPtr physics_level = physics_level_builder.build();

    world->get_dynamics_world()->addRigidBody(physics_level->get_rigid_body());

    Larp::ModelPtr crate_model = Larp::Model::create("assets/crate/crate.obj");
    Larp::EntityPtr entity22 = Larp::Entity::create(crate_model);
    entity22->set_directional_shadows(true);
    Larp::NodePtr node22 = graph->create_child_node();
    node22->attach_entity(entity22);
    node22->set_scale(0.4, 0.4, 0.4);
    node22->set_position(0.0, 4.0, 0.0);

    PhysicsObjectBuilder<btBoxShape> crate_builder;
    crate_builder.set_position(glm::vec3(0.0, 4.0, 0.0));
    crate_builder.set_mass(10.0);
    crate_builder.set_restitution(0.0);
    crate_builder.set_user_pointer(node22);

    PhysicsBoxPtr crate_collider = crate_builder.build();

    world->get_dynamics_world()->addRigidBody(crate_collider->get_rigid_body());

    Larp::ModelPtr p90_model = Larp::Model::create("assets/testgun/testgun.obj");
    Larp::EntityPtr p90_entity = Larp::Entity::create(p90_model);
    p90_entity->set_directional_shadows(true);
    Larp::NodePtr p90_node = graph->create_child_node();
    p90_node->attach_entity(p90_entity);
    p90_node->set_scale(0.1, 0.1, 0.1);
    p90_node->set_position(3.0, 9.0, 0.0);

    PhysicsObjectBuilder<btBoxShape> p90_builder;
    glm::quat p90_rot(0, 0, 0, 1);
    p90_rot = glm::rotate(p90_rot, 90.0, glm::vec3(0, 0, 1));
    p90_node->set_orientation(p90_rot);
    p90_builder.set_orientation(p90_rot);
    p90_builder.set_position(glm::vec3(3.0, 9.0, 0.0));
    p90_builder.set_mass(1.0);
    p90_builder.set_restitution(0.0);
    p90_builder.set_user_pointer(p90_node);

    PhysicsBoxPtr p90_collider = p90_builder.build();

    world->get_dynamics_world()->addRigidBody(p90_collider->get_rigid_body());
    /// Can't add mesh collider for crate. It's too big.
    // PhysicsMeshColliderBuilder crate_builder = PhysicsMeshColliderBuilder("assets/crate.obj");
    // crate_builder.set_mass(1.0);
    // crate_builder.set_position(btVector3(0.0, 5.0, 2.0));
    // crate_builder.set_local_inertia(btVector3(0.0, 0.0, 0.0));
    // crate_builder.set_restitution(1);
    // crate_builder.set_user_pointer(node22);

    // PhysicsMeshColliderPtr crate = crate_builder.build();

    //world->get_dynamics_world()->addRigidBody(crate->get_rigid_body());


    /*******************************
     * TESTING - DELETE THIS       *
     *******************************/
    Larp::ModelPtr nanosuit = Larp::Model::create("assets/nanosuit/nanosuit.obj");
    Larp::EntityPtr entity2 = Larp::Entity::create(nanosuit);

    node12->attach_entity(entity2);
    node12->set_scale(0.05f, 0.05f, 0.05f);

    player.reset(new PhysicsPlayerController(world.get(), node12, glm::vec3(0, 5.0, 2.0)));
    player->set_user_pointer(node12);

    make_floor(world);

    // Skybox stuff
    std::vector<const GLchar*> skybox_files;
    skybox_files.push_back("assets/skybox/right.jpg");//assets/mp_drakeq/drakeq_rt.tga");
    skybox_files.push_back("assets/skybox/left.jpg");
    skybox_files.push_back("assets/skybox/top.jpg");
    skybox_files.push_back("assets/skybox/bottom.jpg");
    skybox_files.push_back("assets/skybox/back.jpg");
    skybox_files.push_back("assets/skybox/front.jpg");
    Larp::SkyBox skybox(skybox_files);
    graph->set_skybox(&skybox);


    GLfloat frame_rate_limiter = 0.0f;
    uint64_t iteration_number = 0;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        frame_rate_limiter += delta_time;
        if (frame_rate_limiter > 1.0 / 60.0)
        {
            frame_rate_limiter -= 1.0 / 60.0;
            ++iteration_number;
        }
        else
            continue;

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        player->update_movement(world.get());

        world->get_dynamics_world()->stepSimulation(1.0f / 60.0f, 10);

        player->step(world.get(), 1.0f / 60.0f);
        Larp::NodePtr player_node = player->get_user_pointer();
        glm::vec3 pos = player->get_position();
        glm::quat quat = player->get_orientation();
        player_node->set_position(pos);
        player_node->set_orientation(quat);
        camera._position = glm::vec3(pos.x, pos.y + player_node->get_scaled_height(), pos.z);

        camera._yaw = player->get_yaw();

        for (size_t i = 0; i < world->get_collision_object_count(); ++i)
        {
            btCollisionObject* obj = world->get_dynamics_world()->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);

            if (body && body->getMotionState() &&
                obj->getCollisionFlags() != btCollisionObject::CF_CHARACTER_OBJECT)
            {
                btTransform trans;
                body->getMotionState()->getWorldTransform(trans);
                void* user_pointer = body->getUserPointer();

                if (user_pointer != nullptr)
                {
                    btQuaternion orientation = trans.getRotation();
                    Larp::NodePtr user_node = static_cast<Larp::NodePtr>(user_pointer);

                    user_node->set_position(trans.getOrigin().getX(),
                                            trans.getOrigin().getY(),
                                            trans.getOrigin().getZ());
                    user_node->set_orientation(orientation.getX(),
                                               orientation.getY(),
                                               orientation.getZ(),
                                               orientation.getW());
                }
            }
        }

        // Check and call events
        glfwPollEvents();
        Do_Movement();

        // Clear the colorbuffer
        glClearColor(0.1f, 0.8f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // node11->yaw(delta_time * 32.0);
        // node11->pitch(delta_time * 23.0);
        // node11->roll(delta_time * 17.0);

        glm::mat4 projection = glm::perspective(camera._zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.get_view_matrix();
        glm::vec3 view_pos = camera._position;
        graph->draw(view, projection, view_pos);

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
    if (keys[GLFW_KEY_UP])
        camera.process_keyboard(Camera::FORWARD, delta_time);
    if (keys[GLFW_KEY_DOWN])
        camera.process_keyboard(Camera::BACKWARD, delta_time);
    if (keys[GLFW_KEY_LEFT])
        camera.process_keyboard(Camera::LEFT, delta_time);
    if (keys[GLFW_KEY_RIGHT])
        camera.process_keyboard(Camera::RIGHT, delta_time);

    if (keys[GLFW_KEY_S])
        player->add_movement_direction(PhysicsPlayerController::PlayerDirection::BACKWARD);
    if (keys[GLFW_KEY_A])
        player->add_movement_direction(PhysicsPlayerController::PlayerDirection::LEFT);
    if (keys[GLFW_KEY_D])
        player->add_movement_direction(PhysicsPlayerController::PlayerDirection::RIGHT);
    if (keys[GLFW_KEY_W])
        player->add_movement_direction(PhysicsPlayerController::PlayerDirection::FORWARD);

    if (keys[GLFW_KEY_SPACE])
        player->jump();
    if (keys[GLFW_KEY_LEFT_SHIFT])
        camera.process_keyboard(Camera::DOWN, delta_time);

    if (keys[GLFW_KEY_R])
        player->set_position(glm::vec3(0.0, 7.0, 0.0));
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // We don't want people to actually clear the graph
    // if (key == GLFW_KEY_C)
    //     graph->clear();

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

    glm::quat rotation(0, 0, 0, 1);
    player->rotate(glm::rotate(rotation, xoffset * 0.05, glm::vec3(0, 1, 0)));
    camera.process_mouse_movement(0, yoffset);
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
    camera.process_mouse_scroll(y_offset);
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void make_floor(std::unique_ptr<PhysicsWorld>& world)
{
    btTransform trans;
    trans.setIdentity();
    trans.setOrigin(btVector3(0.0, -5.0, 0.0));
    btScalar mass(0.0);
    btVector3 local_inertia(0, 0, 0);

    btStaticPlaneShape* shape = new btStaticPlaneShape(btVector3(0.0f, 1.0f, 0.0f), 0.0f);
    world->get_collision_shapes().push_back(shape);
    btDefaultMotionState* motion_state = new btDefaultMotionState(trans);

    shape->calculateLocalInertia(mass, local_inertia);

    btRigidBody::btRigidBodyConstructionInfo body_info(mass, motion_state, shape, local_inertia);
    btRigidBody* body = new btRigidBody(body_info);
    body->setRestitution(0);

    world->get_dynamics_world()->addRigidBody(body);
}

