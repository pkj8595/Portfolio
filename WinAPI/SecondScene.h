#pragma once
#include "GameNode.h"
#include "TempSoundTest.h"

class SecondScene : public GameNode
{
private:
	TempSoundTest* _tempSound;

	float _alpha;
	float _offsetX, _offsetY;
	float _bgSpeed;

	int _textBufferCnt;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	SecondScene() {}
	~SecondScene() {}
};

