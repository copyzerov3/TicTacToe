#include "Sphere.h"


Sphere::Sphere(GLdouble Radius, std::string name, std::string message) :GameObjectNode(name, message), m_radius(Radius)
{
}


Sphere::~Sphere()
{
}

void Sphere::Render()
{
	glTranslatef(m_transformation[0][3], m_transformation[1][3], m_transformation[2][3]);
	glRotatef(m_transformation[3][0], 1, 0, 0);
	glRotatef(m_transformation[3][1], 0, 1, 0);
	glRotatef(m_transformation[3][2], 0, 0, 1);
	glutSolidSphere(m_radius, 64, 64);
}

void Sphere::Update()
{
	//Rotate(1.0, 1.0, 0, 0);
}
