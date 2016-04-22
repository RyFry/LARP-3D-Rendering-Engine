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

    typedef std::shared_ptr<Entity> SharedEntity;
    typedef Entity* const EntityPtr;
    typedef std::unique_ptr<Node> UniqueNode;
    typedef Node* const NodePtr;
    typedef std::unique_ptr<SceneGraph> UniqueSceneGraph;
    typedef SceneGraph* const SceneGraphPtr;
}
