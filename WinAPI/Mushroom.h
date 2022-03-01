#pragma once
#include "Enemy.h"
#include "Bullets.h"

class Mushroom:public Enemy
{
private:

	bool	_deadForOb;		//��� ���� [Enemy�� isActive�� �� ���� ����, deadForOb�� ü�� 0 ����]

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);
	
	void fire(); 

public:
	void setPos(float x, float y) { _x = x, _y = y;}

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	Mushroom();
	virtual ~Mushroom();
};

