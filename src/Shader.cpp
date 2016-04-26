#include "Shader.hpp"

namespace Larp
{
    Shader::Shader(const GLchar * vertex_path, const GLchar * fragment_path, const GLchar * geometry_path)
    {
        // 1. Retrieve the vertex/fragment source code from filePath
        std::string vertex_code = Shader::load_shader(vertex_path);
        std::string fragment_code = Shader::load_shader(fragment_path);
        std::string geometry_code = Shader::load_shader(geometry_path);

        const GLchar * v_shader_code = vertex_code.c_str();
        const GLchar * f_shader_code = fragment_code.c_str();
        const GLchar * g_shader_code = geometry_code.c_str();
        // 2. Compile shaders
        GLuint vertex = Shader::compile_shader(v_shader_code, GL_VERTEX_SHADER);
        GLuint fragment = Shader::compile_shader(f_shader_code, GL_FRAGMENT_SHADER);
        GLuint geometry = 0;
        if (geometry_path != nullptr)
            geometry = Shader::compile_shader(g_shader_code, GL_GEOMETRY_SHADER);
        // Shader Program
        this->_program = glCreateProgram();
        glAttachShader(this->_program, vertex);
        glAttachShader(this->_program, fragment);
        if (geometry_path != nullptr)
            glAttachShader(this->_program, geometry);
        glLinkProgram(this->_program);
        // Print linking errors if any
        GLint success;
        GLchar infoLog[512];
        glGetProgramiv(this->_program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(this->_program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometry_path != nullptr)
            glDeleteShader(geometry);   
    }

    void Shader::use()
    {
        glUseProgram(this->_program);
    }

    std::string Shader::load_shader(const GLchar * shader_path)
    {
        if (shader_path == nullptr)
            return std::string();

        std::string shader_code;
        std::ifstream shader_file;
        shader_file.exceptions(std::ifstream::badbit);
        try
        {
            // Open file
            shader_file.open(shader_path);
            std::stringstream shader_stream;
            // Read file's buffer contents into stream
            shader_stream << shader_file.rdbuf();
            // Close file handler
            shader_file.close();
            // Convert stream into string
            shader_code = shader_stream.str();
        }
        catch (std::ifstream::failure e)
        {
            THROW_RUNTIME_ERROR("Shader file not read successfully " << e.what());
        }

        return shader_code;
    }

    GLuint Shader::compile_shader(const GLchar * shader_code, GLenum shader_type)
    {
        GLuint shader;
        GLint success;
        GLsizei length;
        GLchar infoLog[512];

        shader = glCreateShader(shader_type);
        glShaderSource(shader, 1, &shader_code, NULL);
        glCompileShader(shader);
        // Throw runtime error if compile failed
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            std::string error;
            switch (shader_type)
            {
            case GL_VERTEX_SHADER:
                error = "GL_VERTEX_SHADER";
                break;
            case GL_FRAGMENT_SHADER:
                error = "GL_FRAGMENT_SHADER";
                break;
            case GL_GEOMETRY_SHADER:
                error = "GL_GEOMETRY_SHADER";
                break;
            default:
                error = "UNSUPPORTED_SHADER_TYPE";
                break;
            }
            glGetShaderInfoLog(shader, 512, &length, infoLog);
            THROW_RUNTIME_ERROR("Error compiling " << error << " [" << infoLog << "]");
        }

        return shader;
    }
}
