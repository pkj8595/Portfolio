#pragma once
#include "SingletonBase.h"

class CameraManager:public SingletonBase<CameraManager>
{

private:
	float* _playerX;
	float* _playerY;
	LPRECT _clientRect;

	int _displayAreaRight;
	int _displayAreaBottom;

	LPRECT _mappingRc;
	LPPOINT _mouseMappingPt;

public:
	HRESULT init();
	HRESULT init(int right,int bottom);
	void setPlayerPosition(float* x,float* y);
	void release();
	void startMappingMode(HDC hdc);
	void endMappingMode(HDC hdc);
};

