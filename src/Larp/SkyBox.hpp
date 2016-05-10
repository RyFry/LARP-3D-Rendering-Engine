#pragma once

#include <vector>

#include "LarpPrerequisites.hpp"
#include "Mesh.hpp" // Vertex
#include "Shader.hpp"

namespace Larp
{
    class SkyBox
    {
    private:
        TextureID _texture_id;
        VAO _VAO;
        VBO _VBO;
        std::vector<glm::vec3> _vertices;
        Shader* _shader;

        void setup_skybox(std::vector<const GLchar*> faces);
        void add_vertices();
    public:
        SkyBox(std::string pos_x, std::string neg_x,
               std::string pos_y, std::string neg_y,
               std::string pos_z, std::string neg_z);
        SkyBox(std::vector<const GLchar*> faces);
        void draw(const glm::mat4& view, const glm::mat4& projection);
    };
}
