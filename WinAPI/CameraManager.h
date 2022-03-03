#pragma once
#include "SingletonBase.h"

class Map;
class CameraManager:public SingletonBase<CameraManager>
{
private:
	float* _playerX;
	float* _playerY;
	Map** _currentMap;

	int _displayAreaRight;
	int _displayAreaBottom;
	int _ratio;
	RECT _cameraRc;
	RECT _clientRect;

public:
	HRESULT init(void);
	void update(void);
	void release(void);

	void setPlayerPosition(float* x, float* y) 
	{
		_playerX = x;
		_playerY = y;
	}
	void setCurrentMap(Map** map)
	{
		_currentMap = map;
	}
	RECT getCameraRect() { return _cameraRc; }
	int getDisplayAreaRight()
	{
		return _displayAreaRight;
	}
	int getDisplayAreaBottom()
	{
		return _displayAreaBottom;
	}
	int getDisplayCenterX()
	{
		return _displayAreaRight/2;
	}
	int getDisplayCenterY()
	{
		return _displayAreaBottom/2;
	}


};