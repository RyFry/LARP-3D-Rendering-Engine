#ifndef SCALE_HPP
#define SCALE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Transformation.hpp"

class Scale : public Transformation
{
    glm::vec3 scale;

public:
    Scale();
    Scale(GLfloat x, GLfloat y, GLfloat z);

    void setScale(GLfloat x, GLfloat y, GLfloat z);
    void setX(GLfloat x);
    void setY(GLfloat y);
    void setZ(GLfloat z);

    virtual void applyTransform();
};

#endif
