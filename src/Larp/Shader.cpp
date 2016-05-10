#include "Shader.hpp"

namespace Larp
{
    Shader* Shader::_shadow_shader = nullptr;
    glm::mat4 Shader::_light_space_matrix;
    std::unordered_map<std::string, UniqueShader> Shader::_compiled_shaders;
    GLuint Shader::_depth_map_FBO;
    GLuint Shader::_depth_map_texture;
    bool Shader::_depth_map_configured = false;

    const GLuint Shader::SHADOW_WIDTH = 1024;
    const GLuint Shader::SHADOW_HEIGHT = 1024;

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
        _shadow_shader = create("shaders/shadow_mapping_depth.vert", "shaders/shadow_mapping_depth.frag");
        return _shadow_shader;
    }

    Shader* Shader::get_shadow_map_shader()
    {
        return create("shaders/my_shadow_mapping.vert", "shaders/my_shadow_mapping.frag");
    }

    Shader* Shader::get_default_shader()
    {
        return create("shaders/lighting.vert", "shaders/lighting.frag");
    }

    Shader* Shader::get_skybox_shader()
    {
        return create("shaders/skybox.vert", "shaders/skybox.frag");
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

    glm::mat4 Shader::calculate_light_space_matrix(glm::vec3 light_pos)
    {
        glm::mat4 light_projection, light_view;
        glm::mat4 light_space_matrix;
        GLfloat near_plane = 0.1f, far_plane = 100.0f;
        light_projection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, near_plane, far_plane);
        //light_projection = glm::perspective(45.0f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // Note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene.
        light_view = glm::lookAt(-light_pos * 20.0f, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.000001584f));
        light_space_matrix = light_projection * light_view;
        return light_space_matrix;
    }

    void Shader::set_light_space_matrix(const glm::mat4& light_space_matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(this->_program, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(light_space_matrix));
    }

    void Shader::prepare_depth_map()
    {
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, _depth_map_FBO);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void Shader::unbind_depth_map()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // move this into a function
        Larp::ConfigurationLoader config("larp.cfg");
        glViewport(0, 0, config.get_width(), config.get_height()); // need to make these values a variable, possibly in larp prereqs
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Shader::set_dir_light_position(glm::vec3 light_pos)
    {
        glUniform3fv(glGetUniformLocation(this->_program, "lightPos"), 1, glm::value_ptr(light_pos));
    }

    void Shader::enable_shadow_texture()
    {
        glUniform1i(glGetUniformLocation(this->_program, "shadowMap"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _depth_map_texture);
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
        ShaderProgram vertex = Shader::compile_shader(v_shader_code, GL_VERTEX_SHADER);
        ShaderProgram fragment = Shader::compile_shader(f_shader_code, GL_FRAGMENT_SHADER);
        ShaderProgram geometry = 0;
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

    ShaderProgram Shader::compile_shader(const GLchar * shader_code, GLenum shader_type)
    {
        ShaderProgram shader;
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
