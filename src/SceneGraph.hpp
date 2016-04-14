#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <memory>

#include "RootNode.hpp"

class SceneGraph
{
    std::unique_ptr<RootNode> root;
};



#endif
