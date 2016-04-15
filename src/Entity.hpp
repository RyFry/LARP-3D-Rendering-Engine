#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "Model.hpp"
#include "Shader.hpp"

class Entity;

typedef std::shared_ptr<Entity> pEntity;

class Entity
{
    Shader _shader;
    Model _model;

public:
    Entity(const Shader& shader, const Model& model);
    // Entity(const std::string model,
    //        const std::string vert_shader,
    //        const std::string frag_shader,
    //        const std::string geom_shader = "");
    void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
};
