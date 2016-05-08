#pragma once
#include "SceneNode.h"
#include <glut.h>
class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();
	enum Operation
	{
		Draw,UpdateObjects
	};
	void Traverse();
	void Update();
	//addsNodeAttached to root
	void AddSceneNode(SceneNode* Node);
private:
	void Traverse(SceneNode* Node,Operation operation);
	SceneNode* p_root;
};

