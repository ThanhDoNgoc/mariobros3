#pragma once
#include "GameObject.h"
enum class NextNode
{
	none,
	left,
	right,
	up,
	down
};

struct Edge
{
	int nodeID;
	NextNode direction;
};
class Node : public CGameObject
{
	int nodeID;

	//D3DXVECTOR2 position;

	std::vector<Edge>* adjacentNodes;

	int containedScence;
public:
	Node();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {}
	virtual void TakeDamage() {}
	virtual void Render() {}
	int getNodeID() { return this->nodeID; }
	void setNodeID(int id) { this->nodeID = id; }

	//void setPosition(Vector2 pos);
	//D3DXVECTOR2 getPosition();

	void setScence(int id) { this->containedScence = id; }
	int getScence() { return this->containedScence; }

	std::vector<Edge>* getAdjacentList() { return this->adjacentNodes; };

};

