#pragma once

class CGameObject;

class Camera
{
	int CamPosX;
	int CamPosY;

	float CamWidth;
	float CamHeight;

	CGameObject* target;

public:

	void SetCamPos(int CamPosX, int CamPosY);
	void SetCamSize(float CamWidth, float CamHeight);
	void SetCamTarget(CGameObject* target);
	
	int GetCamPosX();
	int GetCamPosY();

	float GetCamWidth(); 
	float GetCamHeight();

	void Update();

};

