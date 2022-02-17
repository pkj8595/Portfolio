#pragma once
#include "MainGame.h"

/*

조건 총원 25명-> 20명
과제 1
레이싱 게임
-이미지 필수 (배경+자동차+(플레이어+적)+ 계기판)
- 계시판은 반드시 있어야 한다.
-계기판은 차 속력에 따라 변화한다.
-속도감이 생명
-플레이어와 적이 충돌하면 폭파 이펙트가 터지면서 게임종료

*/
#define ENEMY_COUNT		20

class Homework0118 : public MainGame
{
private:
	enum P_STATE
	{
		STATE_idle = 0,
		STATE_left,
		STATE_right,
		STATE_dead
	};

	struct Enemy 
	{
		RECT rc;
		bool isActive;
		int speed;
	};

	P_STATE _pState;
	RECT _rcPlayer;
	float _pSpeed;
	int _index;

	Enemy _enemy[ENEMY_COUNT];

	double _bgSpeed;
	bool _isLeft;
	bool _isA;
	int _sponTime;

	POINT _ptPannel;
	float _angle;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);		
	virtual void render(HDC hdc);

	Homework0118() {}
	~Homework0118() {}

	void macroPlayFrameAnimation(my::Image * image, bool isleft, int & index);

	bool macroPlayOnceFrameAnimation(my::Image * image, bool isleft, int & index, bool & isAnimating);

};

