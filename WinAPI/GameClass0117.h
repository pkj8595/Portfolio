#pragma once
#include "MainGame.h"


enum ST_pstate
{
	idle=0,
	jump,
	Spider
};

struct Player
{
	RECT rc;
	float speed;
	float gravity;
	bool isGround;
	bool isLeft;
	bool isSpider;
	bool isPlatform;

	Player() 
	{
		speed = 9.5f;
		gravity = 0;
		isGround = false;
		isLeft = false;
		isSpider = false;
		isPlatform = false;
	}
};

class GameClass0117 : public MainGame
{
private:
	int _alphaA, _alphaNum;

	Player _rcPlayer;
	int _floor;

	RECT _wall;
	RECT _platform;

	int _offsetX, _offsetY;
	int _bgSpeed;


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);		
	virtual void render(HDC hdc);


	//int ChangeAlpha(int& alpha, int size);
	void playerMove();
	void jumpStart();
};

