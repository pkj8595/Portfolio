#pragma once
#include "Enemy.h"
#include "HpImgBar.h"


class Minion :public Enemy
{
private:
	enum MI_PATTERN 
	{
		PATTERN_1=0,
		PATTERN_2, 
		PATTERN_3
	};
private:
	HpImgBar* _hpBar;

	MI_PATTERN _pattern;
	POINT _point;
	float _angle;
	float _angleSpeed;
	float _speed;

	float _hp;

public:
	Minion();
	~Minion();

	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void pattern1(void);
	void pattern2(void);
	void pattern3(void);

	virtual STObservedData getRectUpdate();
	virtual void collideObject();

};

