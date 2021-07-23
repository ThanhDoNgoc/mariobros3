#pragma once
#define CAMERA_WIDTH	768
#define CAMERA_HEIGHT	576
#define CAMERA_SPEED	1.5f
class CGameObject;

class Camera
{
	float CamPosX=0;
	float CamPosY=0;

	float CamWidth=0;
	float CamHeight=0;

	CGameObject* target=0;

	float limitTop=0;
	float limitLeft=0;
	float limitBottom=0;
	float limidRight=0;

	bool isFollow = true;
	bool isStatic = false;



public:

	Camera();

	void SetCamPos(int CamPosX, int CamPosY);
	void SetCamSize(float CamWidth, float CamHeight);
	void SetCamTarget(CGameObject* target);
	
	int GetCamPosX();
	int GetCamPosY();

	float GetCamWidth(); 
	float GetCamHeight();

	void SetCamLimit(float left, float top, float right, float bottom);

	void setIsFollow(bool camfollow);
	bool IsFollow();

	void setIsStatic(bool camstatic);
	bool IsStatic();

	void SetScollX(bool sX);
	void SetScoolY(bool sY);

	void Update();

};

