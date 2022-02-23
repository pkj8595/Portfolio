#pragma once
#include "GameNode.h"

struct tagWeapon
{
	my::Image* img;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	float weaponTick;
	bool fire;
};

class NormalWeapon : public GameNode
{
private:
	vector<tagWeapon> _vWeapon;
	vector<tagWeapon>::iterator _viWeapon;

	float _range;
	int _bulletMax;
	int _fixX, _fixY;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle);
	void draw();
	void move();

	NormalWeapon(){}
	~NormalWeapon(){}
};
class SwordWeapon : public GameNode
{
private:
	vector<tagWeapon> _vWeapon;
	vector<tagWeapon>::iterator _viWeapon;

	int _effectMax;
	int _direction;

	float* _x;
	float* _y;
	int _fixX, _fixY;
public:
	HRESULT init(float* x, float* y);
	void release(void);
	void update(void);
	void render(void);

	void fire(int combo, int direction);
	void draw();
	void move();
	void updateFrame();

	SwordWeapon() {}
	~SwordWeapon() {}
};


class BowWeapon : public GameNode
{
};
