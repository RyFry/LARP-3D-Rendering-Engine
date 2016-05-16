#pragma once

#include <memory>       // shared_ptr, weak_ptr
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define GLEW_STATIC
#include <GL/glew.h>    // All da OpenGL schtuff
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>

#include "Error.hpp"    // Custom error handling macro

namespace Larp
{
    class AnimationHandler;
    class ConfigurationLoader;
    class CustomConfigurationLoader;
    class DirectionalLight;
    class Entity;
    class Mesh;
    class Model;
    class Node;
    class PointLight;
    class SceneGraph;
    class Shader;
    class SkyBox;
    class SpotLight;
    class Texture;
    class Time;

    typedef std::unique_ptr<ConfigurationLoader>       UniqueConfigurationLoader;
    typedef std::unique_ptr<CustomConfigurationLoader> UniqueCustomConfigurationLoader;
    typedef std::unique_ptr<DirectionalLight>          UniqueDirectional;
    typedef std::unique_ptr<Entity>                    UniqueEntity;
    typedef std::unique_ptr<Model>                     UniqueModel;
    typedef std::unique_ptr<Node>                      UniqueNode;
    typedef std::unique_ptr<PointLight>                UniquePoint;
    typedef std::unique_ptr<SceneGraph>                UniqueSceneGraph;
    typedef std::unique_ptr<Shader>                    UniqueShader;
    typedef std::unique_ptr<SkyBox>                    UniqueSkyBox;
    typedef std::unique_ptr<SpotLight>                 UniqueSpot;
    typedef std::unique_ptr<Texture>                   UniqueTexture;

    // I am removing these, because the const causes problems in
    // some places, and we might as well just use * at that point
    // typedef Entity*                const EntityPtr;
    // typedef DirectionalLight*      const DirectionalLightPtr;
    // typedef Model*                 const ModelPtr;
    // typedef Node*                  const NodePtr;
    // typedef PointLight*            const PointLightPtr;
    // typedef SceneGraph*            const SceneGraphPtr;
    // typedef SpotLight*             const SpotLightPtr;
    // typedef Texture*               const TexturePtr;

    // For internal use only
    typedef GLuint VAO;
    typedef GLuint VBO;
    typedef GLuint EBO;
    typedef GLuint ShaderProgram;
    typedef GLuint TextureID;
}
