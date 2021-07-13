#pragma once
#include "GameObject.h"
#include "Node.h"
class NodeMap :public CGameObject
{
	std::unordered_map<int, Node*> nodes;
public:
	NodeMap();

	void InsertNode(Node* node);

	Node* getNode(int id);
	virtual void GetBoundingBox(float &l, float &t,float &r, float &b){}
	virtual void TakeDamage(){}
	virtual void Render(){}
};

