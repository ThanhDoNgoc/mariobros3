#pragma once
#define CAMERA_WIDTH	768
#define CAMERA_HEIGHT	720
class CGameObject;

class Camera
{
	int CamPosX;
	int CamPosY;

	float CamWidth;
	float CamHeight;

	CGameObject* target;

	float limitTop;
	float limitLeft;
	float limitBottom;
	float limidRight;

	bool isFollow;
	bool isStatic;

	bool scrollX;
	bool scrollY;


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

