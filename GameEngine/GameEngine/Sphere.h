#pragma once
#include "GameObjectNode.h"
#include <glut.h>
#include <GL.H>
class Sphere :public GameObjectNode
{
public:
	Sphere(GLdouble Radius,std::string name = "Sphere", std::string message = "This is a Sphere Scene Node");
	~Sphere();

	virtual void Render();
	virtual void Update();
private:
	GLdouble m_radius;
};

