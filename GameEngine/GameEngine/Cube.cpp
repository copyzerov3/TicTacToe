#include "Cube.h"


Cube::Cube(GLdouble Width, std::string name, std::string message) :GameObjectNode(name, message), m_width(Width), CellValue(0)
{
}


Cube::~Cube()
{
}

void Cube::Render()
{
	if (CellValue == -1)
	{
		glColor3f(1, 0, 0);
	}
	else if (CellValue == 1)
	{
		glColor3f(0, 0, 1);
	}
	else
	{
		glColor3f(1, 1, 1);
	}

	glTranslatef(m_transformation[0][3], m_transformation[1][3], m_transformation[2][3]);
	glRotatef(m_transformation[3][0], 1, 0, 0);
	glRotatef(m_transformation[3][1], 0, 1, 0);
	glRotatef(m_transformation[3][2], 0, 0, 1);
	glutSolidCube(m_width);

}

void Cube::Update()
{
	//Rotate(1.0, 1.0, 1.0, 0);
}
bool Cube::IsPointWithin(int x, int y)
{
	return (x > (GetX()-50) && GetX() + m_width-50 > x) && (y > GetY()-50 && GetY() + m_width -50> y);
}
