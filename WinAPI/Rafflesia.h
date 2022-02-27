#pragma once
#include "Enemy.h"
#include "Bullets.h"

enum class RAFFLESIASTATE { RA_IDLE, RA_ATTACK, RA_DEAD, RA_END };


class Rafflesia:public Enemy
{
private:
	ThornBullet* _bullet;

	RAFFLESIASTATE _state;
	int		_range;				//�÷��̾� Ž�� ����
	
	float	_attackMoveWorldTime;
	float	_deadTimeCount;
	float	_playerDistance;

	bool	_deadForOb;		//��� ���� [Enemy�� isActive�� �� ���� ����, deadForOb�� ü�� 0 ����]
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

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	Rafflesia();
	virtual ~Rafflesia();
};

