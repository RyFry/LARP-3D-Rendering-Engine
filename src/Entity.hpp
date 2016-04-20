#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "LarpPrerequisites.hpp"
#include "Model.hpp"
#include "Shader.hpp"

namespace Larp
{
    class Entity
    {
    private:
        /**
         * The Shader used during rendering of the Model attached
         * to this Entity.
         */
        Shader _shader;
        /**
         * The Model rendered.
         */
        Model _model;

        /**
         * Default Constructor
         */
        Entity();
        /**
         * Constructor
         * @param shader A Shader object used during rendering
         * @param model The Model to draw during rendering
         */
        Entity(const Shader& shader, const Model& model);

    public:
        /**
         * Creates a pEntity
         * @param shader A Shader object used during rendering
         * @param model The Model to draw during rendering
         * @return The pEntity with the same shader and model passed as parameters
         */
        static pEntity create(const Shader& shader, const Model& model);
        /**
         * Draws the model atteched to this entity using the
         * associated shader
         * @param model The parent's model matrix. Used to calculate
         *              this Entity's model matrix prior to rendering
         * @param view The view matrix to apply during rendering. This should
         *             be obtained from a Camera object.
         * @param projection The projection matrix to apply during rendering.
         *                   This should also be obtained from a Camera object.
         */
        void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
    };
}