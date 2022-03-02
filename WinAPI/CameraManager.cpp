#include "Stdafx.h"
#include "CameraManager.h"

HRESULT CameraManager::init(void)
{
	_displayAreaRight = 960;
	_displayAreaBottom = 540;

	return S_OK;
}

HRESULT CameraManager::init(int displayAreaRight, int displayAreaBottom)
{
	_displayAreaRight = displayAreaRight;
	_displayAreaBottom = displayAreaBottom;

	return S_OK;
}

void CameraManager::setPlayerPosition(float* x, float* y)
{
	_playerX = x;
	_playerY = y;
}

void CameraManager::release(void)
{
}
