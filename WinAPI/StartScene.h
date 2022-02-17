#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:
	float _alpha;
	float _bgAlpha;
	bool _isAlphaIncrece;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	StartScene() {}
	~StartScene() {}

};

