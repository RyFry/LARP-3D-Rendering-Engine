#include <memory>
#include <string>
#include <stdexcept>
#include <unordered_set>

#include "Larp/LarpPrerequisites.hpp"
#include "Larp/ConfigurationLoader.hpp"
#include "Larp/Model.hpp"
#include "Larp/SceneGraph.hpp"
#include "Larp/Shader.hpp"
#include "Larp/SkyBox.hpp"

#include "Larp/AnimationHandler.hpp"
#include "Camera.hpp"
#include "Weapon.hpp"
//#include "GUIManager.hpp"
#include "Sound/SoundManager.hpp"

#include "Physics/MeshColliderBuilder.hpp"
#include "Physics/ObjectBuilder.hpp"
#include "Physics/PlayerController.hpp"
#include "Physics/World.hpp"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Bullet
#include <btBulletDynamicsCommon.h>

// Other Libs
#include <SOIL.h>

#define FRAME_RATE 60.0f

// Properties
GLuint screenWidth = 800, screenHeight = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void char_callback(GLFWwindow* window, unsigned int codepoint);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void do_movement();
void error_callback(int error, const char* description);
void make_floor(Physics::World* physics_world);
// unsigned int GlfwToCeguiKey(int glfwKey);
void attempt_to_pick_up_weapon();
void attempt_to_drop_weapon();
void attempt_to_spawn_bullet();
void make_floor(std::unique_ptr<Physics::World>& physics_world);

// Camera
Larp::SceneGraph* graph = Larp::SceneGraph::singleton();
std::unique_ptr<Physics::World> world;
std::unique_ptr<Physics::PlayerController> player;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
bool buttons[3];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
bool GUIrendering;

std::unordered_set<Weapon*> pickupable_items;
std::unordered_set<Larp::Node*> destructable_items;
Weapon* player_held_item = nullptr;
Larp::Node* camera_node = nullptr;
Larp::AnimationHandler* test_gun_animator;
bool was_in_air = false;
bool firing = false;
GLfloat air_start_time = 0;
//GUIManager* GUIMan;

int main(void)
{
    Larp::ConfigurationLoader* config = Larp::ConfigurationLoader::load_configurations("larp.cfg");
    screenWidth = config->get_width();
    screenHeight = config->get_height();
    // Init GLFW
    if (!glfwInit())
    {
        THROW_RUNTIME_ERROR("glfwInit() failed!");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, config->is_resizable());
    //glfwWindowHint(GLFW_SAMPLES, 4);

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, config->get_title().c_str(), glfwGetPrimaryMonitor(), nullptr); // Windowed
    if (window == nullptr)
    {
        THROW_RUNTIME_ERROR("GLFWwindow* = nullptr");
    }
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
	glfwSetCharCallback(window, char_callback);

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

    // Setting up Physics::World
    world.reset(new Physics::World());
    world->init_objects();

    Larp::Model* level = Larp::Model::create("assets/LEVEL/LEVEL.obj");
    Larp::Entity* entity = Larp::Entity::create(level);
    entity->set_directional_shadows(true);
    Larp::DirectionalLight* dir_light = Larp::LightFactory::create_directional_light(0.5, -1.0, 1.0);
    dir_light->set_ambient_intensity(0.2, 0.2, 0.2);

    Larp::Node* node11 = graph->create_child_node();
    Larp::Node* player_node = graph->create_child_node();

    Larp::Node* node21 = node11->create_child();
    node21->attach_entity(entity);

    Physics::MeshColliderBuilder physics_level_builder = Physics::MeshColliderBuilder("assets/LEVEL/LEVEL.obj");
    physics_level_builder.set_mass(0.0);
    physics_level_builder.set_restitution(1.0);
    physics_level_builder.set_user_pointer(node21);

    Physics::MeshCollider* physics_level = physics_level_builder.build();

    world->get_dynamics_world()->addRigidBody(physics_level->get_rigid_body());

    Larp::Model* crate_model = Larp::Model::create("assets/crate/crate.obj");
    Larp::Entity* entity22 = Larp::Entity::create(crate_model);
    entity22->set_directional_shadows(true);
    Larp::Node* crate_node = graph->create_child_node();
    crate_node->attach_entity(entity22);
    crate_node->set_scale(0.4, 0.4, 0.4);
    std::cout << "Scaled dimensions of crate: ("
              << crate_node->get_scaled_width()
              << ", "
              << crate_node->get_scaled_height()
              << ", "
              << crate_node->get_scaled_depth()
              << ')'
              << std::endl;
    crate_node->set_position(0.0, 6.0, 3.0);

    destructable_items.insert(crate_node);

    Physics::ObjectBuilder<btBoxShape> crate_builder;
    crate_builder.set_position(glm::vec3(0.0, 6.0, 3.0));
    crate_builder.set_mass(0.6);
    crate_builder.set_restitution(0.0);
    crate_builder.set_user_pointer(crate_node);

    Physics::Box* crate_collider = crate_builder.build();

    world->get_dynamics_world()->addRigidBody(crate_collider->get_rigid_body());

    Weapon* shotgun = new Weapon("assets/Shotgun/shotgun_000000.obj",
                                 "assets/Shotgun/shotgun.lub",
                                 "assets/crate/crate.obj",
                                 "shotgun",
                                 graph->get_root_node(),
                                 -90, 0, 1.2,
                                 false);
    shotgun->m_node->set_scale(0.1, 0.1, 0.1);
    shotgun->m_node->set_position(3.0, 1.5, 0.0);
    shotgun->initiate_physics(world.get());
    pickupable_items.insert(shotgun);

    Weapon* launcher = new Weapon("assets/Rocket Launcher/launcher_000000.obj",
                                  "assets/Rocket Launcher/launcher.lub",
                                  "assets/rocket/rocket.obj",
                                  "rocket_fire",
                                  graph->get_root_node(),
                                  0, -90, 0.5,
                                  false);
    launcher->m_node->set_scale(0.1, 0.1, 0.1);
    launcher->m_node->set_position(-8.5, 8.5, 8.5);
    launcher->initiate_physics(world.get());
    pickupable_items.insert(launcher);

    Weapon* chaingun = new Weapon("assets/Chaingun/chaingun_000000.obj",
                                  "assets/Chaingun/chaingun.lub",
                                  "assets/crate/crate.obj",
                                  "chaingun",
                                  graph->get_root_node(),
                                  0, 0, 0.75,
                                  true);
    chaingun->m_node->set_scale(0.2, 0.2, 0.2);
    chaingun->m_node->set_position(10.0, 9.0, -10.0);
    chaingun->initiate_physics(world.get());
    pickupable_items.insert(chaingun);

    /*******************************
     * TESTING - DELETE THIS       *
     *******************************/
    player.reset(new Physics::PlayerController(world.get(), player_node, .35, .75, .15, glm::vec3(0, 5.0, 2.0)));
    player->set_user_pointer(player_node);

    camera_node = player_node->create_child();
    camera_node->translate(0.0, 0.75, 0.0);

    make_floor(world);

    // Skybox stuff
    std::vector<const GLchar*> skybox_files;
    skybox_files.push_back("assets/skybox/right.jpg");
    skybox_files.push_back("assets/skybox/left.jpg");
    skybox_files.push_back("assets/skybox/top.jpg");
    skybox_files.push_back("assets/skybox/bottom.jpg");
    skybox_files.push_back("assets/skybox/back.jpg");
    skybox_files.push_back("assets/skybox/front.jpg");
    Larp::SkyBox skybox(skybox_files);
    graph->set_skybox(&skybox);

    GLfloat frame_rate_limiter = 0.0f;
    uint64_t iteration_number = 0;

    // soundMan = new SoundManager();
    // GUIMan = new GUIManager(graph, window);
    GUIrendering = false;

    SoundManager::sound_init();
    SoundManager::play_music();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // GUIrendering = GUIMan->get_rendering_state();
        // Set frame time
        Larp::Time::update_time();
        // Update animation system
        Larp::AnimationHandler::update_animations();

        frame_rate_limiter += Larp::Time::delta_time();
        if (frame_rate_limiter > 1.0 / FRAME_RATE)
        {
            frame_rate_limiter -= 1.0 / FRAME_RATE;
            ++iteration_number;
        }
        else
            continue;

        // Check and call events
        glfwPollEvents();
        do_movement();

        player->update_movement(world.get());

        world->get_dynamics_world()->stepSimulation(1.0f / FRAME_RATE, 10);

        player->step(world.get(), 1.0f / FRAME_RATE);
        Larp::Node* player_node = player->get_user_pointer();
        glm::vec3 pos = player->get_position();
        glm::quat quat = player->get_orientation();
        player_node->set_position(pos);
        player_node->set_orientation(quat);
        camera.m_position = glm::vec3(pos.x, pos.y + player->get_height(), pos.z);
        camera.m_yaw = player->get_yaw();

        glm::quat item_quat;
        //item_quat = glm::rotate(item_quat, 90.0f, glm::vec3(0, 1, 0));
        item_quat = glm::rotate(item_quat, -camera.m_pitch, glm::vec3(1, 0, 0));
        camera_node->set_orientation(item_quat);

        for (size_t i = 0; i < world->get_collision_object_count(); ++i)
        {
            btCollisionObject* obj = world->get_dynamics_world()->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);

            if (body && body->getMotionState() &&
                obj->getCollisionFlags() != btCollisionObject::CF_CHARACTER_OBJECT)
            {
                btTransform trans;
                trans.setIdentity();
                body->getMotionState()->getWorldTransform(trans);
                void* user_pointer = body->getUserPointer();

                if (user_pointer != nullptr)
                {
                    btQuaternion orientation = trans.getRotation();
                    Larp::Node* user_node = static_cast<Larp::Node*>(user_pointer);

                    user_node->set_position(trans.getOrigin().getX(),
                                            trans.getOrigin().getY(),
                                            trans.getOrigin().getZ());
                    user_node->set_orientation(glm::quat(orientation.getW(),
                                                         orientation.getX(),
                                                         orientation.getY(),
                                                         orientation.getZ()));
                }
            }
        }

        // Check and call events
        glfwPollEvents();
        if(!GUIrendering)
        {
            do_movement();

            if(firing && player_held_item != nullptr && player_held_item->m_auto)
            {
                attempt_to_spawn_bullet();
            }
        }

        // Clear the colorbuffer
        glClearColor(0.1f, 0.8f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // node11->yaw(Larp::Time::delta_time() * 32.0);
        // node11->pitch(Larp::Time::delta_time() * 23.0);
        // node11->roll(Larp::Time::delta_time() * 17.0);

        glm::mat4 projection = glm::perspective(camera.m_zoom, (float)screenWidth/(float)screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.get_view_matrix();
        glm::vec3 view_pos = camera.m_position;
        graph->draw(view, projection, view_pos);

        if(GUIrendering)
        {
            glDisable(GL_DEPTH_TEST);
            // CEGUI::System::getSingleton().renderAllGUIContexts();
            glEnable(GL_DEPTH_TEST);
        }

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    SoundManager::sound_quit();

    return 0;
}

// Moves/alters the camera positions based on user input
void do_movement()
{
    // Camera controls
    if (keys[GLFW_KEY_UP])
        camera.process_keyboard(Camera::FORWARD, Larp::Time::delta_time());
    if (keys[GLFW_KEY_DOWN])
        camera.process_keyboard(Camera::BACKWARD, Larp::Time::delta_time());
    if (keys[GLFW_KEY_LEFT])
        camera.process_keyboard(Camera::LEFT, Larp::Time::delta_time());
    if (keys[GLFW_KEY_RIGHT])
        camera.process_keyboard(Camera::RIGHT, Larp::Time::delta_time());

    if (keys[GLFW_KEY_S])
        player->add_movement_direction(Physics::PlayerController::PlayerDirection::BACKWARD);
    if (keys[GLFW_KEY_A])
        player->add_movement_direction(Physics::PlayerController::PlayerDirection::LEFT);
    if (keys[GLFW_KEY_D])
        player->add_movement_direction(Physics::PlayerController::PlayerDirection::RIGHT);
    if (keys[GLFW_KEY_W])
        player->add_movement_direction(Physics::PlayerController::PlayerDirection::FORWARD);

    if (keys[GLFW_KEY_SPACE])
        player->jump();

    if (keys[GLFW_KEY_LEFT_SHIFT])
        camera.process_keyboard(Camera::DOWN, Larp::Time::delta_time());

    if (keys[GLFW_KEY_R])
        player->set_position(glm::vec3(0.0, 7.0, 0.0));

    if(!was_in_air && !(player->is_on_floor()))
    {
        was_in_air = true;
        air_start_time = Larp::Time::current_time();
    }
    if(was_in_air && player->is_on_floor())
    {
        was_in_air = false;
        SoundManager::play_sound("jump");
        if(player_held_item != nullptr && !(player_held_item->m_animation->get_current_animation() == "fire") && Larp::Time::current_time() - air_start_time >= 0.3)
        {
            player_held_item->m_animation->play("land", true, 0);
        }
    }
    if(player_held_item != nullptr && player->is_moving() && player->is_on_floor() && player_held_item->m_animation->get_current_animation() == "NO ANIMATION PLAYING")
    {
        player_held_item->m_animation->play("walk", true, 0);
    }
    if(player_held_item != nullptr && (!(player->is_moving()) || !(player->is_on_floor())) && player_held_item->m_animation->get_current_animation() == "walk")
    {
        player_held_item->m_animation->stop(true);
    }
    if(player->is_moving() && player->is_on_floor())
    {
        SoundManager::play_sound("walk");
    }
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
//    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

    /*Inject keys for CEGUI. Mainly pressing down on one */
    if(action == GLFW_PRESS)
    {

        // if(GlfwToCeguiKey(key) != 0)
        // {
        //     context.injectKeyDown((CEGUI::Key::Scan)GlfwToCeguiKey(key));
        //     /*If I don't add this the arrow keys start putting in weird character codes */
        //     if(key == GLFW_KEY_BACKSPACE)
        //         context.injectChar((CEGUI::Key::Scan)GlfwToCeguiKey(key));
        // }
        // else
        //     context.injectKeyDown((CEGUI::Key::Scan)key);
    }
    /* Inject keys for CEGUI. For releasing a key */
    // else if(action == GLFW_RELEASE)
    //     context.injectKeyUp((CEGUI::Key::Scan)key);

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && !GUIrendering)
        glfwSetWindowShouldClose(window, GL_TRUE);
    // else if(key == GLFW_KEY_F1 && action == GLFW_PRESS)
    //     GUIMan->show_main();

    // We don't want people to actually clear the graph
    // if (key == GLFW_KEY_C)
    //     graph->clear();

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;

    // Have the player attempt to pick up a weapon
    if (keys[GLFW_KEY_E])
        attempt_to_pick_up_weapon();
    if (keys[GLFW_KEY_Q])
        attempt_to_drop_weapon();
}

/* GLFW has two keyboard related call backs.
 * One for the physical keyboard and one for the Unicode for the keys
 * This one is for the Unicode
 */
void char_callback(GLFWwindow* window, unsigned int codepoint)
{
    // CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    // context.injectChar(codepoint);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    // context.injectMouseMove(xpos - lastX,  ypos - lastY);

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    /* May need to change the movement feels weird */

    /* If the GUI is rendering stop mouse movement for the player camera */
    if(!GUIrendering)
    {
        glm::quat rotation(0.0, 0.0, 0.0, 1.0);
        player->rotate(glm::rotate(rotation, xoffset * 0.05, glm::vec3(0, 1, 0)));
        camera.process_mouse_movement(0, yoffset);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !GUIrendering)
    {
        attempt_to_spawn_bullet();
        firing = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE && !GUIrendering)
    {
        firing = false;
    }
    // if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    //     CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton);
    // else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    //     CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::RightButton);
    // else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    //      CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
    // else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    //      CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton);
}

void scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
    camera.process_mouse_scroll(y_offset);
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

/**
 * We attempt to have the player pick up a gun by raycasting to whatever the player is
 * looking at, and then if we hit something in the raycast, we check the distance,
 * and then we have to determine whether or not it's a gun.
 */
void attempt_to_pick_up_weapon()
{
    if (player_held_item != nullptr)
        return;

    GLfloat yaw = camera.m_yaw;
    GLfloat pitch = camera.m_pitch;
    glm::vec3 pos = camera.m_position;

    btScalar xz_len = cos(glm::radians(pitch));
    btVector3 bt_to(xz_len * cos(glm::radians(yaw)),
                    sin(glm::radians(pitch)),
                    xz_len * sin(glm::radians(yaw)));
    btVector3 bt_from(pos.x, pos.y, pos.z);
    bt_from += bt_to;
    bt_to *= 20;
    btCollisionWorld::ClosestRayResultCallback result(bt_from, bt_to);
    world->get_dynamics_world()->rayTest(bt_from, bt_to, result);

    if (result.hasHit() && (bt_from - result.m_hitPointWorld).length() < 0.7)
    {
        btRigidBody* collided = const_cast<btRigidBody*>(static_cast<const btRigidBody*>(result.m_collisionObject));
        Larp::Node* user_pointer = static_cast<Larp::Node*>(collided->getUserPointer());
        Weapon* weaponptr = nullptr;
        if(user_pointer != nullptr)
        {
           for (auto& it:pickupable_items) {
                if(it->m_node == user_pointer)
                {
                    weaponptr = it;
                }
            }
        }
        if (weaponptr != nullptr)
        {
            world->get_dynamics_world()->removeRigidBody(const_cast<btRigidBody*>(collided));
            user_pointer->detach_this_from_parent();
            Larp::Node* gun_parent = camera_node->create_child();
            gun_parent->attach_child(user_pointer);
            user_pointer->set_position(0.0, 0.0, 0.0);
            gun_parent->set_position(-0.2, -0.25, weaponptr->m_offset_z);
            glm::vec3 player_scale = static_cast<Larp::Node*>(player->get_user_pointer())->get_scale();
            glm::vec3 user_pointer_scale = user_pointer->get_scale();
            user_pointer->set_scale(user_pointer_scale.x / player_scale.x,
                                    user_pointer_scale.y / player_scale.y,
                                    user_pointer_scale.z / player_scale.z);
            user_pointer->set_orientation(glm::quat(1, 0, 0, 0));
            user_pointer->pitch(weaponptr->m_offset_pitch);
            user_pointer->yaw(weaponptr->m_offset_yaw);

            // Finally, update our player_held_item to denote that we are actually holding something
            player_held_item = weaponptr;
        }
    }
}

void attempt_to_drop_weapon()
{
    if (player_held_item == nullptr)
        return;

    GLfloat yaw = camera.m_yaw;
    GLfloat pitch = camera.m_pitch;
    glm::vec3 pos = camera.m_position;

    btScalar xz_len = cos(glm::radians(pitch));
    btVector3 direction(xz_len * cos(glm::radians(yaw)), sin(glm::radians(pitch)), xz_len * sin(glm::radians(yaw)));

    Physics::ObjectBuilder<btBoxShape> test_gun_builder;
    glm::quat test_gun_rot(0, 0, 0, 1);
    test_gun_rot = glm::rotate(test_gun_rot, 50.0, glm::vec3(0, 0, 1));
    player_held_item->m_node->set_orientation(test_gun_rot);
    test_gun_builder.set_orientation(test_gun_rot);
    test_gun_builder.set_position(pos);
    test_gun_builder.set_mass(5.0);
    test_gun_builder.set_restitution(0.0);
    test_gun_builder.set_user_pointer(player_held_item->m_node);

    Physics::Box* test_gun_collider = test_gun_builder.build();

    test_gun_collider->get_rigid_body()->setLinearVelocity(direction * 5);

    world->get_dynamics_world()->addRigidBody(test_gun_collider->get_rigid_body());

    player_held_item->m_node->detach_this_from_parent();
    graph->get_root_node()->attach_child(player_held_item->m_node);
    player_held_item = nullptr;
}

void attempt_to_spawn_bullet()
{
    // Only attempt to shoot  a bullet if the user is holding a gun
    if (player_held_item == nullptr || player_held_item->m_animation->get_current_animation() == "fire")
        return;

    SoundManager::play_sound(player_held_item->m_sound);
    player_held_item->m_animation->play("fire", true, 0);
    GLfloat yaw = camera.m_yaw;
    GLfloat pitch = camera.m_pitch;
    glm::vec3 pos = camera.m_position;
    glm::quat rotation;
    rotation = glm::rotate(rotation, -yaw + 90.0, glm::vec3(0, 1, 0));
    rotation = glm::rotate(rotation, -pitch, glm::vec3(1, 0, 0));

    btScalar xz_len = cos(glm::radians(pitch));
    btVector3 direction(xz_len * cos(glm::radians(yaw)), sin(glm::radians(pitch)), xz_len * sin(glm::radians(yaw)));

    Larp::Model* crate_model = Larp::Model::create(player_held_item->m_ammo);
    Larp::Entity* crate_entity = Larp::Entity::create(crate_model);
    Larp::Node* crate_node = graph->create_child_node();
    crate_node->attach_entity(crate_entity);
    crate_node->set_scale(0.04, 0.04, 0.04);
    crate_node->set_position(pos);
    crate_node->set_orientation(rotation);

    Physics::ObjectBuilder<btBoxShape> crate_builder;
    crate_builder.set_position(pos);
    crate_builder.set_orientation(rotation);
    crate_builder.set_mass(0.2);
    crate_builder.set_restitution(0.0);
    crate_builder.set_user_pointer(crate_node);

    Physics::Box* crate_collider = crate_builder.build();

    crate_collider->get_rigid_body()->setLinearVelocity(direction * 100);
    world->get_dynamics_world()->addRigidBody(crate_collider->get_rigid_body());
}

void make_floor(std::unique_ptr<Physics::World>& world)
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


// unsigned int GlfwToCeguiKey(int glfwKey)
// {
//     switch(glfwKey)
//     {
//         case GLFW_KEY_UNKNOWN   : return 0;
//         case GLFW_KEY_UP        : return CEGUI::Key::ArrowUp;
//         case GLFW_KEY_DOWN      : return CEGUI::Key::ArrowDown;
//         case GLFW_KEY_LEFT      : return CEGUI::Key::ArrowLeft;
//         case GLFW_KEY_RIGHT     : return CEGUI::Key::ArrowRight;
//         case GLFW_KEY_BACKSPACE : return CEGUI::Key::Backspace;
//         default         : return 0;
//     }
// }
