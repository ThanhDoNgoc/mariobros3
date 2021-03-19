#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;

	this->camera = new Camera();
}

Camera* CScene::GetCamera()
{
	return camera;
}
