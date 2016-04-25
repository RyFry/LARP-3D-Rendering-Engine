#include "Shader.hpp"

namespace Larp
{
    Shader::Shader(const GLchar * vertex_path, const GLchar * fragment_path, const GLchar * geometry_path)
    {
        // Retrieve the vertex/fragment source code from filePath
        _vertex_code = Shader::load_shader(vertex_path);
        _fragment_code = Shader::load_shader(fragment_path);
        _geometry_code = Shader::load_shader(geometry_path);     
    }

    void Shader::use()
    {
        glUseProgram(this->_program);
    }

    void Shader::enable_directional_lighting()
    {
        // 1. Find the position in the fragment source code to be modified
        std::string text("#define DIRECTIONAL_LIGHT 0");
        std::size_t pos = this->_fragment_code.find(text);
        if (pos == std::string::npos)
        {
            THROW_RUNTIME_ERROR("This shader does not support directional lighting");
        }
        pos += text.size() - 1;

        // 2. Enable directional lighting calculations
        this->_fragment_code[pos] = 1;
    }

    void Shader::set_number_point_lights(GLfloat light_number)
    {
        // 1. Ensure light number provided does not exceed the max number of point lights
        if (light_number > this->_max_lights)
        {
            THROW_RUNTIME_ERROR("Specified number of point lights exceeds maximum value");
        }

        // 2. Find the position in the fragment source code to be modified
        std::string text("#define NR_POINT_LIGHTS 0");
        std::size_t pos = this->_fragment_code.find(text);
        if (pos == std::string::npos)
        {
            THROW_RUNTIME_ERROR("This shader does not support point lights");
        }
        pos += text.size() - 1;

        // 3. Set the number of point lights
        this->_fragment_code[pos] = light_number;
    }

    void Shader::set_number_spot_lights(GLfloat light_number)
    {
        // 1. Ensure light number provided does not exceed the max number of spot lights
        if (light_number > this->_max_lights)
        {
            THROW_RUNTIME_ERROR("Specified number of spot lights exceeds maximum value");
        }

        // 2. Find the position in the fragment source code to be modified
        std::string text("#define NR_SPOT_LIGHTS 0");
        std::size_t pos = this->_fragment_code.find(text);
        if (pos == std::string::npos)
        {
            THROW_RUNTIME_ERROR("This shader does not support spot lights");
        }
        pos += text.size() - 1;
        
        // 3. Set the number of spot lights
        this->_fragment_code[pos] = light_number;
    }

    void Shader::build_shader()
    {
        // 1. Convert the vertex/fragment source code to a c string
        const GLchar * v_shader_code = this->_vertex_code.c_str();
        const GLchar * f_shader_code = this->_fragment_code.c_str();
        const GLchar * g_shader_code = this->_geometry_code.c_str();

        // 2. Compile shaders
        GLuint vertex = Shader::compile_shader(v_shader_code, GL_VERTEX_SHADER);
        GLuint fragment = Shader::compile_shader(f_shader_code, GL_FRAGMENT_SHADER);
        GLuint geometry = 0;
        if (!this->_geometry_code.empty())
            geometry = Shader::compile_shader(g_shader_code, GL_GEOMETRY_SHADER);

        // Shader Program
        this->_program = glCreateProgram();
        glAttachShader(this->_program, vertex);
        glAttachShader(this->_program, fragment);
        if (!this->_geometry_code.empty())
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
        if (!this->_geometry_code.empty())
            glDeleteShader(geometry);
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
            THROW_RUNTIME_ERROR(std::string("Error compiling ") +
                                error + std::string(" [") + std::string(infoLog) + std::string("]"));
        }

        return shader;
    }
}
