#pragma once

#include "LarpPrerequisites.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Larp
{
    class Shader
    {
    public:
        /**
         * The ID of the OpenGL Program associated with this Shader
         */
        GLuint _program;

        /**
         * Constructor
         * @param vertex_path   The path to the desired vertex shader.
         * @param fragment_path The path to the desired fragment shader.
         * @param geometry_path The path to the desired geometry shader. If not provided, the default OpenGL
         *                      geometry shader will be used (Recommended except when needed).
         */
        Shader(const GLchar * vertex_path, const GLchar * fragment_path, const GLchar * geometry_path = nullptr);

        /**
         * Tells OpenGL to use this Shader's compiled shader program
         */
        void use();
    private:
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
