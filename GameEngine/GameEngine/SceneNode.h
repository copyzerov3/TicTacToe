#pragma once
#include <stdio.h>
#include <glm.hpp>
#include <vector>
#include <string>
#include <gtc\matrix_access.hpp>
class SceneNode
{
public:
	SceneNode(std::string name="DefaultName",std::string message = "This is a Scene Node");
	~SceneNode();

	void AddChild(SceneNode* Child);
	void GetMessage() const;
	glm::f32mat4 GetTransformation();
	void SetTransformation(glm ::mat4 transformation);
	std::vector<SceneNode*> & GetChildren();
	SceneNode* GetParent() const;
	std::string GetName() const;
	virtual void Render();
	virtual void Update();
	bool ShouldUpdate();

	void SetActorID(const unsigned int ActorID);
	unsigned int GetActorID() const;

	static unsigned int ActorIDCount;

protected:
	void SetParent(SceneNode* Parent);

	glm::mat4 m_transformation;
	unsigned int m_ActorID;
	std::vector<SceneNode*> m_childrenNodes;
	SceneNode* p_parent;
	std::string m_message,m_name;
	bool m_shouldUpdate;

	
};

