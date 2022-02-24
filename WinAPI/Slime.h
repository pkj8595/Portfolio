#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"

#define COLLRECTSIZEY 30

enum class SLIMESTATE
{
	SM_IDLE,
	SM_MOVE,
	SM_ATTACK,
	SM_END
};

enum class SLIMEDIRECTION
{
	SM_LEFT,
	SM_RIGHT,
	SM_UP,
	SM_DOWN,
	SM_END
};


class Slime:public Enemy
{
private:
	
	Animation* _ani;
	SLIMEDIRECTION _slimeDir;
	SLIMESTATE _slimestate;
	int randomX , randomY;
	float _x, _y;
	float _speed;
	float _angle;
	float _range; //플레이어 탐지 범위
	float _time;
	float _worldTime;

	float _moveRange;
	int _attTime; 


	ThreeDirectionMissile* _slimebullet;
	CircleMissile* _slimeCirclebullet;

	RECT _rc_playerCollCheck;


	float _playerDistance;

	bool _moveCheck;
	bool _attCheck;
	int attRange;

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation();
	//void bulletParttern(); //총알 패턴

	void attack();

	void randomMove();
	bool playerCheck(); //플레이어 감지함수

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject();

	Slime();
	virtual ~Slime();
};

/*
1. 추적 대상이 공격 사거리 안에 있으면 공격 함수 실행
2. 추적 대상 방향으로 바라보기

attack()
{

자신 사망X && 추적 대상과 거리가 공격 사거리 안에 있으면
if()
{
움직임 멈추고

추적 대상 바라본다.

최근 공격 시점에서 일정 시간 지나면 공격 가능

}

}

*/