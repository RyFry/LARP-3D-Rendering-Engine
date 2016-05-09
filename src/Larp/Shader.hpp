#pragma once

#include "LarpPrerequisites.hpp"
#include "LightFactory.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "ConfigurationLoader.hpp"

namespace Larp
{
    class Shader
    {
    public:
        /**
         * The ID of the OpenGL Program associated with this Shader
         */
        ShaderProgram _program;

        static Shader* _shadow_shader;

        static std::vector<glm::mat4> _light_space_matrix;

        /**
         * If the model at path is not already loaded, then it will be loaded and cached.
         * @param vertex_path   The path to the desired vertex shader.
         * @param fragment_path The path to the desired fragment shader.
         * @param geometry_path The path to the desired geometry shader. If not provided, the default OpenGL
         *                      geometry shader will be used (Recommended except when needed).
         */
        static Shader* create(const GLchar * vertex_path, const GLchar * fragment_path, const GLchar * geometry_path = nullptr);

        /**
         * Tells OpenGL to use this Shader's compiled shader program
         */
        void use();

        static Shader* get_depth_map_shader();
        static Shader* get_shadow_map_shader();
        static Shader* get_default_shader();
        static Shader* get_skybox_shader();

        void set_shininess(const GLfloat shininess);

        void set_view_position(const glm::vec3& view_pos);

        void set_mvp(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);

        // TODO: move this functionality into light factory
        void set_directional_lights();
        // TODO: move this functionality into light factory
        void set_point_lights();

        // The default value for light position should not by in the same axis as the up vector in the lookat function
        static glm::mat4 calculate_light_space_matrix(glm::vec3 light_pos = glm::vec3(0.0f, 10.0f, 1.0f), GLfloat near_plane = 0.1f, GLfloat far_plane = 100.0f);
        void set_light_space_matrix(const glm::mat4& light_space_matrix, GLuint index);
        static void prepare_depth_map(GLuint index);
        static void unbind_depth_map();
        void set_dir_light_position(glm::vec3 light_pos = glm::vec3(0.0f, 10.0f, 0.1f));
        void enable_shadow_texture(GLuint index);
    private:
        /**
         * A cache of compiled Shaders.
         */
        static std::unordered_map<std::string, UniqueShader> _compiled_shaders;
        /**
         * Checks if the OpenGL code has been called to configure the depth map
         */
        static bool _depth_map_configured;
        /**
         * A framebuffer object for rendering the depth map
         */
        static GLuint _depth_map_FBO;
        /**
         * A 2D texture that is used as the framebuffer's depth buffer
         */
        static std::vector<GLuint> _depth_map_texture;

        static const GLuint SHADOW_WIDTH;
        static const GLuint SHADOW_HEIGHT;
        /**
         * Constructor
         * @param vertex_path   The path to the desired vertex shader.
         * @param fragment_path The path to the desired fragment shader.
         * @param geometry_path The path to the desired geometry shader. If not provided, the default OpenGL
         *                      geometry shader will be used (Recommended except when needed).
         */
        Shader(const GLchar * vertex_path, const GLchar * fragment_path, const GLchar * geometry_path = nullptr);
        /**
         * Loads a shader given its path relative to where the program is being run
         * @param shader_path The path to the shader program to be loaded
         */
        static std::string load_shader(const GLchar * shader_path);

        /**
         * Compiles a loaded shader program
         * @param shader_code The text version of the shader program as an OpenGL string.
         * @param shader_type The type of shader to compile. Must be one of GL_VERTEX_SHADER, GL_FRAGMENT_SHADER,
         *                    or GL_FRAGMENT_SHADER. Other valid shader types are defined; however, only the former 3
         *                    are currently supported.
         * @see https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glCreateShader.xml for other valid shader types.
         */
        static GLuint compile_shader(const GLchar * shader_code, GLenum shader_type);
    };
}
