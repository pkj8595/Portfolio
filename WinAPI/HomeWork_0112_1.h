#pragma once
#include "MainGame.h"


struct tagCannon0113 {
	POINT center;
	POINT cannonEnd;
	int radius;
	int length;
	float angle;
};

struct tagBullet0113
{
	RECT rc;
	bool isFire;
	float angle;
	/*int yDir;
	int xDir;*/
	//TCHAR teststr[255];
};


class HomeWork_0112_1 : public MainGame
{
private:

	tagBullet0113 _bullet[30];
	tagCannon0113 _cannon;
	RECT _apple[10];

	RECT _treeRect;

	my::Image* _background;
	my::Image* _appleSprite;
	my::Image* _bulletSprite;
	my::Image* _cannonSprite;
	my::Image* _treeSprite;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);	
	virtual void render(HDC hdc);

};

