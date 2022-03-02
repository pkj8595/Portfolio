#include "Stdafx.h"
#include "CameraManager.h"

HRESULT CameraManager::init()
{

	return S_OK;
}

HRESULT CameraManager::init(int displayAreaRight, int displayAreaBottom)
{
	_displayAreaRight = displayAreaRight;
	_displayAreaBottom = displayAreaBottom;
	_clientRect = &RectMake(0,0,0,0);
	GetClientRect(_hWnd, _clientRect);

	return S_OK;
}

void CameraManager::setPlayerPosition(float* x, float* y)
{
	_playerX = x;
	_playerY = y;
}

void CameraManager::release()
{
}

void CameraManager::startMappingMode(HDC hdc)
{
	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, _displayAreaRight, _displayAreaBottom, NULL);
	SetViewportExtEx(hdc, _clientRect->right, _clientRect->bottom, NULL);

}

void CameraManager::endMappingMode(HDC hdc)
{
	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, _clientRect->right, _clientRect->bottom, NULL);
	SetViewportExtEx(hdc, _clientRect->right, _clientRect->bottom, NULL);
}
