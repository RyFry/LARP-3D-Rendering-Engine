#pragma once

#include <memory>	// unique_ptr

#include "Node.hpp"

class SceneGraph;

typedef std::shared_ptr<SceneGraph> pSceneGraph;

class SceneGraph
{
private:
    pNode _root;
    static pSceneGraph _singleton;
    SceneGraph();
public:
	static pSceneGraph singleton();
	pNode create_child_node();
	void draw(glm::mat4 view, glm::mat4 projection);
	void set_ambient_light(glm::vec3 color);
};
