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
	//GetClientRect(_hWnd, &_clientRect);
	_computeCameraPt = POINT{ 0,0 };
	return S_OK;
}

void CameraManager::update(void)
{
	if (*_currentMap != nullptr) 
	{
		_computeCameraPt.x = *_playerX;
		_computeCameraPt.y = *_playerY;

		if (_computeCameraPt.x - _displayAreaRight * 0.5 < 0  )
		{
			cout << "left" << endl;
			_computeCameraPt.x = _displayAreaRight * 0.5;
		}
		if (_computeCameraPt.x + _displayAreaRight * 0.5 > (*_currentMap)->getMapAreaRect().right)
		{
			cout << "right" << endl;
			_computeCameraPt.x = (*_currentMap)->getMapAreaRect().right - (_displayAreaRight * 0.5);
		}

		if (_computeCameraPt.y - _displayAreaBottom * 0.5 < 0)
		{
			cout << "top" << endl;
			_computeCameraPt.y = _displayAreaBottom * 0.5;
		}
		if (_computeCameraPt.y + _displayAreaBottom * 0.5 > (*_currentMap)->getMapAreaRect().bottom)
		{
			cout << "bottom" << endl;
			_computeCameraPt.y = (*_currentMap)->getMapAreaRect().bottom - (_displayAreaBottom * 0.5);
		}

		_cameraRc = RectMakeCenter((int)_computeCameraPt.x,(int) _computeCameraPt.y, 960, 540);

	}
	else
	{
		_cameraRc = RectMakeCenter(*_playerX, *_playerY, 960, 540);
	}
}

void CameraManager::release(void)
{
}
