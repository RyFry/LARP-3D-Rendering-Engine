#pragma once

#include "Error.hpp" // Throwing errors

// Std. Includes
#include <vector>    // vector

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * An abstract camera class that processes input and calculates the corresponding Eular Angles,
 * Vectors and Matrices for use in OpenGL
 */
class Camera
{
public:
    /**
     * Enum that defines several directions for the Camera to move
     */
    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    /**
     * Default yaw for a Camera object when not provided to the constructor
     */
    static const GLfloat YAW;
    /**
     * Default pitch for a Camera object when not provided to the constructor
     */
    static const GLfloat PITCH;
    /**
     * Default speed for a Camera object when not provided to the constructor
     */
    static const GLfloat SPEED;
    /**
     * Default sensitivity for a Camera object.
     */
    static const GLfloat SENSITIVITY;
    /**
     * Default zoom for a Camera object.
     */
    static const GLfloat ZOOM;

    /**
     * Current position of the camera
     */
    glm::vec3 _position;
    /**
     * Vector representing which direction the Camera is facing.
     * Used when calculating how the Camera moves forward and backward.
     */
    glm::vec3 _front;
    /**
     * The vector used to calculate the Camera's lookAt matrix.
     */
    glm::vec3 _up;
    /**
     * Vector representing the x-axis in view space. Also used to calculate
     * how the Camera moves left and right.
     */
    glm::vec3 _right;
    /**
     * The world's up vector used to update the Camera's view matrix.
     */
    glm::vec3 _world_up;
    /**
     * This Camera's yaw in degrees
     */
    GLfloat _yaw;
    /**
     * This Camera's pitch in degrees
     */
    GLfloat _pitch;
    /**
     * Determines how fast the Camera moves
     */
    GLfloat _movement_speed;
    /**
     * Determines how much the Camera rotates on mouse movement
     */
    GLfloat _mouse_sensitivity;
    /**
     * The current zoom of the Camera
     */
    GLfloat _zoom;

    /**
     * Constructor
     * @param position The starting position of the Camera as a glm::vec3. If
     *                 not provided the Camera will be centered at the origin.
     * @param up The up vector for the world. If not provided the y-axis will be
     *           used as the world up vector
     * @param yaw The initial yaw for the Camera. If not provided, the Camera will
     *            start pointing down the -z-axis
     * @param pitch The initial pitch of the Camera. If not provided, the Camera will
     *              start on the xz-plane
     */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           GLfloat yaw = YAW,
           GLfloat pitch = PITCH);
    /**
     * Constructor
     * @param pos_x The starting x position of the Camera.
     * @param pos_y The starting y position of the Camera.
     * @param pos_z The starting z position of the Camera.
     * @param up_x The x-value of the world up vector of the Camera.
     * @param up_y The y-value of the world up vector of the Camera.
     * @param up_z The z-value of the world up vector of the Camera.
     * @param yaw The initial yaw for the Camera. If not provided, the Camera will
     *            start pointing down the -z-axis
     * @param pitch The initial pitch of the Camera. If not provided, the Camera will
     *              start on the xz-plane
     */
    Camera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z,
           GLfloat up_x, GLfloat up_y, GLfloat up_z,
           GLfloat yaw = YAW, GLfloat pitch = PITCH);
    /**
     * @return the view matrix calculated using Euler angles and the lookAt matrix
     */
    glm::mat4 get_view_matrix();
    /**
     * Processes input received from any keyboard-like input system.
     * @param direction A direction to move the Camera. Must be one of the directions
     *                  predefined in the CameraMovement enum.
     * @param delta_time The duration of time between frames. Used to avoid variable camera speeds
     * @see CameraMovement
     * @throws std::runtime_error whenever direction is not one of those defined by CameraMovement
     */
    void process_keyboard(CameraMovement direction, GLfloat delta_time);
    /**
     * Processes input received from a mouse input system.
     * @param x_offset The value used to update the Camera's yaw. A positive x_offset will yaw
     *                 the Camera counter-clockwise.
     * @param y_offset The value used to update the Camera's pitch. A positive y_offset will
     *                 pitch the Camera up.
     * @param constrain_pitch If true, the Camera's pitch will be constrained to the range [-89.0, 89.0] degrees.
     *                        Useful to avoid Gimbal lock. If not provided, the Camera's pitch will be constrained
     */
    void process_mouse_movement(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch = true);
    /**
     * Processes input received from a mouse scroll-wheel event.
     * @param y_offset The offset of the input device used to zoom the camera. A positive offset
     *                 zooms the camera in by reducing the FOV in degrees, while a negative
     *                 offset zooms the camera out.
     */
    void process_mouse_scroll(GLfloat y_offset);

private:
    /**
     * Calculates the front vector from the Camera's (updated) Eular Angles
     */
    void update_camera_vectors();
};
