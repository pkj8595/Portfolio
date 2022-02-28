#pragma once
#include "Enemy.h"
#include "Bullets.h"

#define RAFFLESIA_BULLET_SIZE_X 40
#define RAFFLESIA_BULLET_SIZE_Y 60

enum class RAFFLESIASTATE { RA_IDLE, RA_ATTACK, RA_DEAD, RA_END };


class Rafflesia:public Enemy
{
private:
	ThornBullet* _bullet;

	RAFFLESIASTATE _state;
	int		_range;				//�÷��̾� Ž�� ����
	float	_attackPosCheckTime;
	float	_attackWorldTime;
	float	_deadTimeCount;
	float	_playerDistance;

	float	_playerPosX, _playerPosY;
	bool	_deadForOb;		//��� ���� [Enemy�� isActive�� �� ���� ����, deadForOb�� ü�� 0 ����]
	bool	_attackPositionCheck; //������ġ üũ 


public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);

	void frame();
	bool PlayerCheck();
	void attack();
	void attackPosCheck(); 

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	Rafflesia();
	virtual ~Rafflesia();
};

