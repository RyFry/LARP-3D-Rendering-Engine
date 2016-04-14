#ifndef TRANSLATION_HPP
#define TRANSLATION_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Transformation.hpp"

class Translation : public Transformation
{
    glm::vec3 translation;

public:
    Translation();
    Translation(GLfloat x, GLfloat y, GLfloat z);
    Translation(glm::vec3 translation);

    void setTranslation(GLfloat x, GLfloat y, GLfloat z);
    void setX(GLfloat x);
    void setY(GLfloat y);
    void setZ(GLfloat z);

    virtual void applyTransform();
};

#endif
