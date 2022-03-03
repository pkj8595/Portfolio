#include "Stdafx.h"
#include "CameraManager.h"
#include "Map.h"

HRESULT CameraManager::init(void)
{
	_displayAreaRight = 960;
	_displayAreaBottom = 540;
	_cameraRc = RectMake(0, 0, 960, 540);
	_currentMap = nullptr;
	_ratio = 100;

	return S_OK;
}

void CameraManager::update(void)
{
	if (*_currentMap != nullptr) {}
	_cameraRc = RectMakeCenter(*_playerX, *_playerY, 960, 540);
}

void CameraManager::release(void)
{
}
