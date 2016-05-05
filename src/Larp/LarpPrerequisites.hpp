#pragma once

#include <memory>       // shared_ptr, weak_ptr
#include <iostream>
#include <string>
#include <sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>    // All da OpenGL schtuff
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>

#include "Error.hpp"    // Custom error handling macro

namespace Larp
{
    class ConfigurationLoader;
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

    typedef std::unique_ptr<DirectionalLight> UniqueDirectional;
    typedef std::unique_ptr<Entity>           UniqueEntity;
    typedef std::unique_ptr<Model>            UniqueModel;
    typedef std::unique_ptr<Node>             UniqueNode;
    typedef std::unique_ptr<PointLight>       UniquePoint;
    typedef std::unique_ptr<SceneGraph>       UniqueSceneGraph;
    typedef std::unique_ptr<SkyBox>           UniqueSkyBox;
    typedef std::unique_ptr<SpotLight>        UniqueSpot;

    typedef Entity*           EntityPtr;
    typedef DirectionalLight* DirectionalLightPtr;
    typedef Model*            ModelPtr;
    typedef Node*             NodePtr;
    typedef PointLight*       PointLightPtr;
    typedef SceneGraph*       SceneGraphPtr;
    typedef Shader*           ShaderPtr;
    typedef SkyBox*           SkyBoxPtr;
    typedef SpotLight*        SpotLightPtr;

    // For internal use only
    typedef GLuint VAO;
    typedef GLuint VBO;
    typedef GLuint EBO;
    typedef GLuint ShaderProgram;
    typedef GLuint TextureID;
}
