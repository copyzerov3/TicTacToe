#pragma once
#include "Cube.h"
class Button:public Cube
{
public:
	Button(GLdouble Width, std::string TextOnButton, std::string name = "Button Node",std::string message = "This a button Node");
	~Button();

	virtual void Render();
	virtual void Update();
private:
	std::string TextOnButton;
	
};

