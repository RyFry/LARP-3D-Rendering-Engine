#pragma once

#include <memory>       // shared_ptr, weak_ptr
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Error.hpp"    // Custom error handling macro

namespace Larp
{
    class AnimationHandler;
    class ConfigurationLoader;
    class DirectionalLight;
    class Entity;
    class Mesh;
    class Model;
    class Node;
    class PointLight;
    class SceneGraph;
    class Shader;
    class SpotLight;
    class Texture;
    class Time;
    class Vertex;

    typedef std::unique_ptr<DirectionalLight> UniqueDirectional;
    typedef std::unique_ptr<Entity>           UniqueEntity;
    typedef std::unique_ptr<Model>            UniqueModel;
    typedef std::unique_ptr<Node>             UniqueNode;
    typedef std::unique_ptr<PointLight>       UniquePoint;
    typedef std::unique_ptr<SceneGraph>       UniqueSceneGraph;
    typedef std::unique_ptr<SpotLight>        UniqueSpot;

    typedef Entity*                const EntityPtr;
    typedef DirectionalLight*      const DirectionalLightPtr;
    typedef Model*                 const ModelPtr;
    typedef Node*                  const NodePtr;
    typedef PointLight*            const PointLightPtr;
    typedef SceneGraph*            const SceneGraphPtr;
    typedef SpotLight*             const SpotLightPtr;

}
