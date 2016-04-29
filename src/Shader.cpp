#include "Shader.hpp"

namespace Larp
{
    std::unordered_map<std::string, UniqueShader> Shader::_compiled_shaders;
    GLuint Shader::_depth_map_FBO;
    GLuint Shader::_depth_map_texture;
    bool Shader::_depth_map_configured = false;

    // ----------------
    // Public functions
    // ----------------

    Shader* Shader::create(const GLchar * vertex_path, const GLchar * fragment_path, const GLchar * geometry_path)
    {
        std::stringstream ss;
        ss << vertex_path << fragment_path;

        if (geometry_path)
            ss << geometry_path;

        std::string appended_paths = ss.str();

        if (_compiled_shaders.find(appended_paths) == _compiled_shaders.end())
        {
            _compiled_shaders.emplace(appended_paths, UniqueShader(new Shader(vertex_path, fragment_path, geometry_path)));
        }
        return _compiled_shaders.at(appended_paths).get();
    }

    void Shader::use()
    {
        glUseProgram(this->_program);
    }

    Shader* Shader::get_depth_map_shader()
    {
        if (!_depth_map_configured)
        {
            const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
            // Configure depth map FBO
            glGenFramebuffers(1, &_depth_map_FBO);
            // - Create depth texture
            glGenTextures(1, &_depth_map_texture);
            glBindTexture(GL_TEXTURE_2D, _depth_map_texture);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

            glBindFramebuffer(GL_FRAMEBUFFER, _depth_map_FBO);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depth_map_texture, 0);
            glDrawBuffer(GL_NONE);
            glReadBuffer(GL_NONE);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        return create("shaders/shadow_mapping_depth.vert", "shaders/shadow_mapping_depth.frag");
    }

    Shader* Shader::get_shadow_map_shader()
    {
        return create("shaders/shadow_mapping.vert", "shaders/shadow_mapping.frag");
    }

    Shader* Shader::get_default_shader()
    {
        return create("shaders/lighting.vert", "shaders/lighting.frag");
    }

    void Shader::set_shininess(const GLfloat shininess)
    {
        glUniform1f(glGetUniformLocation(this->_program, "material.shininess"), shininess);
    }

    void Shader::set_view_position(const glm::vec3& view_pos)
    {
        glUniform3f(glGetUniformLocation(this->_program, "viewPos"), view_pos.x, view_pos.y, view_pos.z);
    }

    void Shader::set_mvp(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
    {
        glUniformMatrix4fv(glGetUniformLocation(this->_program, "projection"), 1, GL_FALSE,
                           glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(this->_program, "view"), 1, GL_FALSE,
                           glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(this->_program, "model"), 1, GL_FALSE,
                           glm::value_ptr(model));
    }

    void Shader::set_directional_lights()
    {
        std::vector<UniqueDirectional>& lights = LightFactory::_directional_lights;
        
        bool use_directional_lighting = !lights.empty();
        glUniform1i(glGetUniformLocation(this->_program, "directionalLight"), use_directional_lighting);

        if (use_directional_lighting)
        {
          glUniform3f(glGetUniformLocation(this->_program, "dirLight.direction"), lights[0]->_direction.x, lights[0]->_direction.y, lights[0]->_direction.z);
          glUniform3f(glGetUniformLocation(this->_program, "dirLight.ambient"), lights[0]->_ambient.x, lights[0]->_ambient.y, lights[0]->_ambient.z);
          glUniform3f(glGetUniformLocation(this->_program, "dirLight.diffuse"), lights[0]->_diffuse.x, lights[0]->_diffuse.y, lights[0]->_diffuse.z);
          glUniform3f(glGetUniformLocation(this->_program, "dirLight.specular"), lights[0]->_specular.x, lights[0]->_specular.y, lights[0]->_specular.z);
        }
    }

    void Shader::set_point_lights()
    {
        std::vector<UniquePoint>& lights = LightFactory::_point_lights;

        int num_point_lights = lights.size();
        glUniform1i(glGetUniformLocation(this->_program, "numPointLights"), num_point_lights);
        
        for (int i = 0; i < num_point_lights; ++i)
        {
          glUniform3f(glGetUniformLocation(this->_program, ("pointLights[" + std::to_string(i) + "].position").c_str()), lights[i]->_position.x, lights[i]->_position.y, lights[i]->_position.z);
          glUniform3f(glGetUniformLocation(this->_program, ("pointLights[" + std::to_string(i) + "].ambient").c_str()), lights[i]->_ambient.x, lights[i]->_ambient.y, lights[i]->_ambient.z);
          glUniform3f(glGetUniformLocation(this->_program, ("pointLights[" + std::to_string(i) + "].diffuse").c_str()), lights[i]->_diffuse.x, lights[i]->_diffuse.y, lights[i]->_diffuse.z);
          glUniform3f(glGetUniformLocation(this->_program, ("pointLights[" + std::to_string(i) + "].specular").c_str()), lights[i]->_specular.x, lights[i]->_specular.y, lights[i]->_specular.z);
          glUniform1f(glGetUniformLocation(this->_program, ("pointLights[" + std::to_string(i) + "].constant").c_str()), lights[i]->_constant);
          glUniform1f(glGetUniformLocation(this->_program, ("pointLights[" + std::to_string(i) + "].linear").c_str()), lights[i]->_linear);
          glUniform1f(glGetUniformLocation(this->_program, ("pointLights[" + std::to_string(i) + "].quadratic").c_str()), lights[i]->_quadratic);
        }
    }

    // -----------------
    // Private functions
    // -----------------

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
