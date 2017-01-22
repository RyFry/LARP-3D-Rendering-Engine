#include "Camera.hpp"

const GLfloat Camera::sc_yaw         = -90.0f;
const GLfloat Camera::sc_pitch       = 0.0f;
const GLfloat Camera::sc_speed       = 3.0f;
const GLfloat Camera::sc_sensitivity = 0.25f;
const GLfloat Camera::sc_zoom        = 45.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_movement_speed(Camera::sc_speed),
      m_mouse_sensitivity(Camera::sc_sensitivity),
      m_zoom(sc_zoom)
{
    m_position = position;
    m_world_up = up;
    m_yaw = yaw;
    m_pitch = pitch;
    this->update_camera_vectors();
}

Camera::Camera(GLfloat pos_x, GLfloat pos_y, GLfloat pos_z,
               GLfloat up_x, GLfloat up_y, GLfloat up_z,
               GLfloat yaw, GLfloat pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
      m_movement_speed(Camera::sc_speed),
      m_mouse_sensitivity(Camera::sc_sensitivity),
      m_zoom(sc_zoom)
{
    m_position = glm::vec3(pos_x, pos_y, pos_z);
    m_world_up = glm::vec3(up_x, up_y, up_z);
    m_yaw = yaw;
    m_pitch = pitch;
    this->update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::process_keyboard(CameraMovement direction, GLfloat delta_time)
{
    GLfloat velocity = m_movement_speed * delta_time;
    switch (direction)
    {
    case FORWARD:
        m_position += m_front * velocity;
        break;
    case BACKWARD:
        m_position -= m_front * velocity;
        break;
    case LEFT:
        m_position -= m_right * velocity;
        break;
    case RIGHT:
        m_position += m_right * velocity;
        break;
    case UP:
        m_position.y += Camera::sc_speed * delta_time / 2.0;
        break;
    case DOWN:
        m_position.y -= Camera::sc_speed * delta_time / 2.0;
        break;
    default:
        THROW_RUNTIME_ERROR("Invalid CameraMovement passed.");
    }
}

void Camera::process_mouse_movement(GLfloat x_offset, GLfloat y_offset, GLboolean constrain_pitch)
{
    x_offset *= m_mouse_sensitivity;
    y_offset *= m_mouse_sensitivity;

    m_yaw   += x_offset;
    m_pitch += y_offset;


    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrain_pitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // Update front, Right and Up Vectors using the updated Eular angles
    this->update_camera_vectors();
}

void Camera::process_mouse_scroll(GLfloat y_offset)
{
    if (m_zoom >= 1.0f && m_zoom <= 45.0f)
        m_zoom -= y_offset;
    if (m_zoom <= 1.0f)
        m_zoom = 1.0f;
    if (m_zoom >= 45.0f)
        m_zoom = 45.0f;
}

void Camera::update_camera_vectors()
{
    // Calculate the new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    // Also re-calculate the _right and _up vector
    m_right = glm::normalize(glm::cross(m_front, m_world_up));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
