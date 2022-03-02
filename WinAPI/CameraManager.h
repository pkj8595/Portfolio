#pragma once
#include "SingletonBase.h"

class CameraManager:public SingletonBase<CameraManager>
{

private:
	float* _playerX;
	float* _playerY;

	int _displayAreaRight;
	int _displayAreaBottom;

public:
	HRESULT init(void);
	HRESULT init(int right,int bottom);
	void release(void);
	void setPlayerPosition(float* x,float* y);
};

