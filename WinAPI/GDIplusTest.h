#pragma once
#include "GameNode.h"
#include "CShapePlayer.h"
#include "MapPatternController.h"

class GDIplusTest : public GameNode
{
private:
	Gdiplus::Graphics* _g;
	Gdiplus::Matrix _baseMatrix;
	CShapePlayer _cplayer;
	MapPatternController _mapController;

	DWORD	_time;
	DWORD	_timeStart;
	DWORD	_pauseTime;
	DWORD	_addTime;
	bool	_gameStop;

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);


	GDIplusTest() {}
	~GDIplusTest() {}


};

