#pragma once
#include "MainGame.h"
#include "BattleGamePlayer.h"
#include "cmath"

#define PIE			3.1415926535
#define RADIAN		(180/PIE)
#define COMPUTE_RADIAN(X)	((X * PIE)/(180 * RADIAN))

struct tagSkill_Reflection
{
	bool isActive;
	RECT rc;
	int time;
	int timeCount;
};

struct tagSkill_Shield
{
	bool isActive;
	RECT rc;
	int time;
	int timeCount;
};

struct tagSkill_timeStop
{
	bool isActive;
	int time;
	int timeCount;
};

struct tagSkill_Tornado
{
	bool isActive;
	RECT rc;
	int speed;
	int damage;
	int time;
	int timeCount;
	int x;
	int y;
};



class HomeWork_0104 : public Scene_inter
{
private:
	RECT _startRc[2];
	BattleGamePlayer _player[2];
	int temp;
	int _count;

	tagSkill_Reflection skill_Reflection;
	tagSkill_Shield skill_Shield;
	tagSkill_timeStop skill_timeStop;
	tagSkill_Tornado skill_Tornado;

	bool isGameOver;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	bool RectIsCollider(RECT * rec1, RECT * rec2);


	HomeWork_0104() {}
	~HomeWork_0104() {}
};

