#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"

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
	float _time;
	float _worldTime;

	Bullet* _bullet;

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);

public:
	Slime();
	virtual ~Slime();
};
