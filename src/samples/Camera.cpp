#include "Camera.hpp"

const GLfloat Camera::YAW         = -90.0f;
const GLfloat Camera::PITCH       = 0.0f;
const GLfloat Camera::SPEED       = 3.0f;
const GLfloat Camera::SENSITIVITY = 0.25f;
const GLfloat Camera::ZOOM        = 45.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
    : _front(glm::vec3(0.0f, 0.0f, -1.0f)),
      _movement_speed(Camera::SPEED),
      _mouse_sensitivity(Camera::SENSITIVITY),
      _zoom(ZOOM)
{
    this->_position = position;
    this->_world_up = up;
    this->_yaw = yaw;
    this->_pitch = pitch;
    this->update_camera_vectors();
}

Camera::Camera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z,
               GLfloat up_x, GLfloat up_y, GLfloat up_z,
               GLfloat yaw, GLfloat pitch)
    : _front(glm::vec3(0.0f, 0.0f, -1.0f)),
      _movement_speed(Camera::SPEED),
      _mouse_sensitivity(Camera::SENSITIVITY),
      _zoom(ZOOM)
{
    this->_position = glm::vec3(pos_x, pos_y, pos_z);
    this->_world_up = glm::vec3(up_x, up_y, up_z);
    this->_yaw = yaw;
    this->_pitch = pitch;
    this->update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(this->_position, this->_position + this->_front, this->_up);
}

void Camera::process_keyboard(CameraMovement direction, GLfloat delta_time)
{
    GLfloat velocity = this->_movement_speed * delta_time;
    switch (direction)
    {
    case FORWARD:
        this->_position += this->_front * velocity;
        break;
    case BACKWARD:
        this->_position -= this->_front * velocity;
        break;
    case LEFT:
        this->_position -= this->_right * velocity;
        break;
    case RIGHT:
        this->_position += this->_right * velocity;
        break;
    case UP:
        this->_position.y += Camera::SPEED * delta_time / 2.0;
        break;
    case DOWN:
        this->_position.y -= Camera::SPEED * delta_time / 2.0;
        break;
    default:
        THROW_RUNTIME_ERROR("Invalid CameraMovement passed.");
    }
}

void Camera::process_mouse_movement(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch)
{
    x_offset *= this->_mouse_sensitivity;
    y_offset *= this->_mouse_sensitivity;

    this->_yaw   += x_offset;
    this->_pitch += y_offset;


    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrain_pitch)
    {
        if (this->_pitch > 89.0f)
            this->_pitch = 89.0f;
        if (this->_pitch < -89.0f)
            this->_pitch = -89.0f;
    }

    // Update front, Right and Up Vectors using the updated Eular angles
    this->update_camera_vectors();
}

void Camera::process_mouse_scroll(GLfloat y_offset)
{
    if (this->_zoom >= 1.0f && this->_zoom <= 45.0f)
        this->_zoom -= y_offset;
    if (this->_zoom <= 1.0f)
        this->_zoom = 1.0f;
    if (this->_zoom >= 45.0f)
        this->_zoom = 45.0f;
}

void Camera::update_camera_vectors()
{
    // Calculate the new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    front.y = sin(glm::radians(this->_pitch));
    front.z = sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
    this->_front = glm::normalize(front);
    // Also re-calculate the _right and _up vector
    this->_right = glm::normalize(glm::cross(this->_front, this->_world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->_up    = glm::normalize(glm::cross(this->_right, this->_front));
}
