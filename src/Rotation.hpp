#ifndef ROTATION_HPP
#define ROTATION_HPP

#include <GL/glew.h>
#include <glm/gtc/quaternion.hpp>

#include "Transformation.hpp"

class Rotation : public Transformation
{
    glm::quat quaternion;

public:
    Rotation();
    Rotation(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    Rotation(glm::vec3 axis, GLfloat w);
    Rotation(glm::quat quaternion);

    void setRotation(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void setX(GLfloat x);
    void setY(GLfloat y);
    void setZ(GLfloat z);
    void setW(GLfloat w);

    virtual void applyTransform();
};

#endif
