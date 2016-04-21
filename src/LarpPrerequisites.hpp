#pragma once

#include <memory>       // shared_ptr, weak_ptr

#include <GL/glew.h>    // All da OpenGL schtuff

#include "Error.hpp"    // Custom error handling macro

namespace Larp
{
    class Camera;
    class Entity;
    class Mesh;
    class Model;
    class Node;
    class SceneGraph;
    class Shader;
    class Texture;
    class Vertex;

    typedef std::shared_ptr<Node> pNode;
    typedef std::shared_ptr<Entity> pEntity;
    typedef std::shared_ptr<SceneGraph> pSceneGraph;
}
