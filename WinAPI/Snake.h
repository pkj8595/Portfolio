#pragma once
#include "Enemy.h"
#include "Bullets.h"


enum class SNAKESTATE { SN_IDLE, SN_MOVE, SN_ATTACK,SN_DEAD, SN_END };
enum class SNAKEDIRECTION { SN_LEFT, SN_RIGHT, SN_UP, SN_DOWN, SN_END };
enum class SNAKEPARTTERN { SN_ATTACK1, SN_ATTACK2 };

class Snake:public Enemy
{
private:
	ThreeDirectionMissile*  _threeDirBullet;
	TwoDirectionMissile*	_twoDirBullet;

	SNAKESTATE		_state;
	SNAKEDIRECTION  _direction;
	SNAKEPARTTERN	_parttern;

	int		_range;				//플레이어 탐지 범위
	int		_randomX, _randomY;
	int		_maxFrameX;
	int		_partternNum;
	float	_moveWorldTime;
	float	_attacWorldTime;
	float	_attackMoveWorldTime;
	float	_deadTimeCount;
	float	_playerDistance;
	float	_attackRange;
	float	_angle;
	float	_frameSpeed;
	float	_speed;				//이동 속도

	bool	_playerCheck; //플레이어가 공격범위 안에 들어왔는지 체크
	bool	_bulletFireCheck; //총알 발사했는지 체크
	bool	_deadForOb;		//사망 여부 [Enemy의 isActive는 몹 삭제 전용, deadForOb는 체력 0 여부]

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);

	void randomPosCreate();
	void randomMove();
	void attack();
	bool playerCheck(); //플레이어 감지함수
	void frame();

	//총알 발사
	void threeDirectionBullet();
	void twoDirectionBullet();

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	Snake();
	virtual ~Snake();
};

