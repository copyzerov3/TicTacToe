#include "SceneGraph.h"


SceneGraph::SceneGraph()
{
	p_root = new SceneNode( "Root", "This is the root node");
}


SceneGraph::~SceneGraph()
{
	if (p_root)
	{
		delete p_root;
	}
}
void SceneGraph::Traverse()
{
	//p_root->GetMessage();
	if (p_root->GetChildren().size() != 0)
	{
		Traverse(p_root,Draw);
	}
	
}
void SceneGraph::Update()
{
	//p_root->GetMessage();
	if (p_root->GetChildren().size() != 0)
	{
		Traverse(p_root, UpdateObjects);
	}
}
void SceneGraph::Traverse(SceneNode* Node,Operation operation)
{
	for (std::vector<SceneNode*>::iterator it = Node->GetChildren().begin(); it != Node->GetChildren().end(); ++it)
	{
		
		//(*it)->GetMessage();
		if (operation == Draw)
		{
			glPushMatrix();
			(*it)->Render();
		}
		else if (operation == UpdateObjects)
		{
			if ((*it)->ShouldUpdate())
			{
				(*it)->Update();
			}
				
		}

		if ((*it)->GetChildren().size())
		{
			Traverse(*it,operation);
		}
		if (operation == Draw)
			glPopMatrix();
	}
}
void SceneGraph::AddSceneNode(SceneNode* Node)
{
	p_root->AddChild(Node);
}
