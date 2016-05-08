#include "SceneNode.h"

unsigned int SceneNode::ActorIDCount = 0;
SceneNode::SceneNode(std::string name, std::string message) :m_name(name), m_message(message), m_shouldUpdate(true)
{
	m_ActorID = SceneNode::ActorIDCount;
	SceneNode::ActorIDCount++;
}
SceneNode::~SceneNode()
{
	if (m_childrenNodes.size() != 0)
	{
		for (std::vector<SceneNode*>::iterator it = m_childrenNodes.begin(); it != m_childrenNodes.end(); ++it)
		{
			delete(*it);
		}
	}
}

bool SceneNode::ShouldUpdate(){ return m_shouldUpdate; }
unsigned int SceneNode::GetActorID() const { return m_ActorID; }
void SceneNode::SetActorID(const unsigned int ActorID){ m_ActorID = ActorID; }
void SceneNode::AddChild(SceneNode* Child)
{
	Child->SetParent(this);
	m_childrenNodes.push_back(Child);
}
void SceneNode::GetMessage() const
{
	printf(m_message.c_str());
	printf("\n");
}
glm::f32mat4 SceneNode::GetTransformation()
{
	return m_transformation;
}
void SceneNode::SetTransformation(glm::mat4 transformation)
{
	m_transformation = transformation;
}
SceneNode* SceneNode::GetParent() const
{
	return p_parent;
}
std::string SceneNode::GetName() const
{
	return m_name;
}
void SceneNode::Render()
{
}
void SceneNode::Update()
{

}
void SceneNode::SetParent(SceneNode* Parent)
{
	p_parent = Parent;
}
std::vector<SceneNode*> & SceneNode::GetChildren()
{
	return m_childrenNodes;
}
