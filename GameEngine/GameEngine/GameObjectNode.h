#pragma once
#include "SceneNode.h"
#include <glut.h>
class GameObjectNode :
	public SceneNode
{
public:
	GameObjectNode(std::string name = "GameObjectNode", std::string message = "Hey this is a GameObjectNode");
	~GameObjectNode();
	void SetPosition(glm::vec3 vector);
	void SetPosition(float x, float y, float z);
	//Set rotation
	void SetRotation(GLfloat angle,float x, float y, float z);
	//rotate from current rotation, angle is the addition to the current angle x, y and z are the axis you want to rotate
	void Rotate(GLfloat angle, float x, float y, float z);
	void SetVelocity(int x, int y, int z);
	void SetVelocity(glm::vec3 NewVelocity);

	inline float GetX(){ return m_transformation[0][3]; }
	inline float GetY(){ return m_transformation[1][3]; }
	inline float GetZ(){ return m_transformation[2][3]; }


protected:
	glm::vec3 m_orientation;
	glm::vec3 m_velocity;
};

