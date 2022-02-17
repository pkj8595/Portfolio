#pragma once

#define _USE_MATH_DEFINES // 메스 위에 잡아야함
#include "math.h"

#define BULLET_RADIUS	40
#define BULLET_SPEED	4

typedef struct tagCostomFloatRect
{
	float left;
	float top;
	float right;
	float bottom;
} FLOAT_RECT;

typedef struct tagCostomFloatPoint
{
	float x;
	float y;
} FLOAT_POINT;


struct tagCannon2 {
	FLOAT_POINT center;
	FLOAT_POINT cannonEnd;
	int radius;
	int length;
	float angle;
};

struct tagBullet2
{
	FLOAT_RECT rc;
	bool isFire;
	float angle;
	int yDir;
	int xDir;
	TCHAR teststr[255];
};


class HomeWork_0107_2 : public Scene_inter
{
private:
	tagCannon2 _cannon;
	tagBullet2 _bullet[30];

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	
	void ReflectionCircle(int index,  float aY, float bY, float aX, float bX);
	void Fire(void);

};

