#pragma once
#include "Enemy.h"
#include "Bullets.h"

class ForestFairy :public Enemy
{
public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);
public:
	ForestFairy();
	virtual ~ForestFairy();
};

