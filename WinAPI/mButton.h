#pragma once
#include "GameNode.h"

class mCallback
{
	virtual void callbackMethod(void) = 0;
};

class mButton : public GameNode , public mCallback
{
private:
	my::Image* _btnImg;
	RECT _btnRc;
	int _x, _y;
	int _frameX;
	//mCallback* _mCallback;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(const char* filename, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	bool isOnClick(POINT mousePt);
	//void setCallback(mCallback* callback){_mCallback = callback;}
	void setFrameX(int frameX) { _frameX = frameX; }

	void callbackMethod(void) {}

	mButton();
	virtual~mButton();
};