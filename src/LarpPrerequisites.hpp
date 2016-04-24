#pragma once

#include <memory>       // shared_ptr, weak_ptr
#include <iostream>
#include <string>
#include <sstream>

#include <GL/glew.h>    // All da OpenGL schtuff

#include "Error.hpp"    // Custom error handling macro

namespace Larp
{
    class ConfigurationLoader;
    class Entity;
    class Mesh;
    class Model;
    class Node;
    class SceneGraph;
    class Shader;
    class Texture;
    class Vertex;

    typedef std::unique_ptr<Entity>     UniqueEntity;
    typedef std::unique_ptr<Model>      UniqueModel;
    typedef std::unique_ptr<Node>       UniqueNode;
    typedef std::unique_ptr<SceneGraph> UniqueSceneGraph;

    typedef Entity*     const EntityPtr;
    typedef Model*      const ModelPtr;
    typedef Node*       const NodePtr;
    typedef SceneGraph* const SceneGraphPtr;
}
