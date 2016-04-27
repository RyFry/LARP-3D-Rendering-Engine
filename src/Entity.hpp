#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <vector>

#include "LarpPrerequisites.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

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
        ModelPtr _model;

        /**
         * Default Constructor
         */
        Entity();
        /**
         * Constructor
         * @param shader A Shader object used during rendering
         * @param model The Model to draw during rendering
         */
        Entity(const Shader& shader, ModelPtr model);

    public:
        /**
         * Creates a EntityPtr
         * @param shader A Shader object used during rendering
         * @param model The Model to draw during rendering
         * @return The EntityPtr with the same shader and model passed as parameters
         */
        static EntityPtr create(const Shader& shader, ModelPtr model);
        /**
         * Draws the model atteched to this entity using the
         * associated shader
         * @param model The parent's model matrix. Used to calculate
         *              this Entity's model matrix prior to rendering
         * @param view The view matrix to apply during rendering. This should
         *             be obtained from a Camera object.
         * @param projection The projection matrix to apply during rendering.
         *                   This should also be obtained from a Camera object.
         * @param view_pos The camera view position to apply during rendering.
         *                 This should be obtained from a Camera object and passed in
         *                 via the SceneGraph.
         * @param directional_lights The vector of directional lights currently held
         *                           by the SceneGraph. If the vector is not empty, these
         *                           should be incorporated in the lighting calculations.
         * @param point_lights The vector of point lights currently held
         *                      by the SceneGraph. If the vector is not empty, these
         *                      should be incorporated in the lighting calculations.
         * @param spot_lights The vector of spot lights currently held
         *                    by the SceneGraph. If the vector is not empty, these
         *                    should be incorporated in the lighting calculations.
         * @warning This method assumes that each model has provided shaders with
         *          variables matching those specified in the method.
         */
        void draw(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection,
                  const glm::vec3& view_pos,
                  const std::vector<UniqueDirectional>& directional_lights,
                  const std::vector<UniquePoint>& point_lights,
                  const std::vector<UniqueSpot>& spot_lights);
        GLfloat get_width() const;
        GLfloat get_height() const;
        GLfloat get_depth() const;
    };
}
