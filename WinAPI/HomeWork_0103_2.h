#pragma once
#include "MainGame.h"
#include "StickMan.h"

struct ST_BULLET 
{
	RECT bullet;
	bool isActive;
};

class HomeWork_0103_2 : public Scene_inter
{
private:
	ST_BULLET _bullet[30];
	StickMan _man;

	RECT _player;
	POINT _bulletPoint;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);
};

