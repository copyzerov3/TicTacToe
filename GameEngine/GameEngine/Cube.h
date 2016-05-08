#pragma once
#include "GameObjectNode.h"
#include <glut.h>
class Cube:public GameObjectNode
{
public:
	Cube(GLdouble Width,std::string name = "Cube", std::string message = "This is a Cube Scene Node");
	~Cube();

	virtual void Render();
	virtual void Update();
	inline bool IsAvailable(){ return(CellValue == 0); }
	inline void SetCellValue(int num){ CellValue = num; }
	inline int GetCellValue(){	return CellValue;}
	inline GLdouble GetWidth(){ return m_width; }
	bool IsPointWithin(int x, int y);
private:
	GLdouble m_width;
	int CellValue;
};

