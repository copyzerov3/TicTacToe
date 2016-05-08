#include "GameObjectNode.h"


GameObjectNode::GameObjectNode(std::string name, std::string message) :SceneNode(name, message)
{
}


GameObjectNode::~GameObjectNode()
{
}

void GameObjectNode::SetVelocity(int x, int y, int z)
{
	m_velocity[0] = x;
	m_velocity[1] = y;
	m_velocity[2] = z;
}
void GameObjectNode::SetVelocity(glm::vec3 NewVelocity)
{
	SetVelocity(NewVelocity[0], NewVelocity[1], NewVelocity[3]);
}

void GameObjectNode::SetPosition(glm::vec3 Vector)
{
	SetPosition(Vector[0], Vector[1], Vector[2]);
}
void GameObjectNode::SetPosition(float x, float y, float z)
{
	m_transformation[0][3] = x;
	m_transformation[1][3] = y;
	m_transformation[2][3] = z;
}

void GameObjectNode::SetRotation(GLfloat angle,float x, float y, float z)
{
	if (x >= 1)
	{
		m_transformation[3][0] = angle;
	}
	if (y >= 1)
	{
		m_transformation[3][1] = angle;
	}
	if (z >= 1)
	{
		m_transformation[3][2] = angle;
	}
}
void GameObjectNode::Rotate(GLfloat angle, float x, float y, float z)
{
	if (x >= 1)
	{
		m_transformation[3][0] += angle;
	}
	if (y >= 1)
	{
		m_transformation[3][1] += angle;
	}
	if (z >= 1)
	{
		m_transformation[3][2] += angle;
	}
}
