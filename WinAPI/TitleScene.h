#pragma once
#include "GameNode.h"

class TitleScene : public GameNode
{
private:
	my::Image* _bg;
	my::Image* _gameName;
	my::Image* _start;
	my::Image* _continue;
	my::Image* _exit;
	my::Image* _changeScreen;
	my::Image* _startBlackScreen;

	RECT _bgRc;
	RECT _startRc;
	RECT _continueRc;
	RECT _exitRc;
	RECT _crashRc;

	float _changeScreenAlpha;
	float _startScreenAlpha;

	bool _isStart;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

