#pragma once

#include <d3dx9.h>
#include "GameObject.h"
#include "Camera.h"

class Camera;

class CScene
{
protected:
	int id;
	LPCWSTR sceneFilePath;

	Camera* camera; 

public: 
	CScene(int id, LPCWSTR filePath);

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 

	virtual void OnKeyUp(int KeyCode) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;

	virtual void AddObject(LPGAMEOBJECT object) = 0;
	virtual void DeleteObject(LPGAMEOBJECT object) = 0;

	virtual Camera* GetCamera();
};
typedef CScene * LPSCENE;
