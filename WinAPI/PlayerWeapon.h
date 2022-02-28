#pragma once
#include "GameNode.h"
#include "IRectObserved.h"

class tagWeapon : public IRectObserved
{
public:
	ObservedType type;
	my::Image* img;
	RECT imageRc;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	float weaponTick;
	float damage;
	bool fire;
	bool firstHit;
	bool sword;

	void init(void);
	void release(void);
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	void setDamage(float damage) { this->damage = damage; }
	void setFirstHit(bool firstHit) { this->firstHit = firstHit; }
	void setSword(bool sword) { this->sword = sword; }
};

class NormalWeapon : public GameNode
{
private:
	vector<tagWeapon*> _vWeapon;
	vector<tagWeapon*>::iterator _viWeapon;

	float _range;
	int _bulletMax;
	int _fixX, _fixY;

public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float damage, float x, float y, float angle);
	void draw();
	void move();

	vector<tagWeapon*> getWeapon() { return _vWeapon; }
	POINT getPoint(int index) { return { (int)_vWeapon[index]->x, (int)_vWeapon[index]->y }; }
	void removeBullet(int index);

	NormalWeapon(){}
	~NormalWeapon(){}
};
class SwordWeapon : public GameNode
{
private:
	vector<tagWeapon*> _vWeapon;
	vector<tagWeapon*>::iterator _viWeapon;

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

	void fire(float damage, int combo, int direction);
	void draw();
	void move();
	void updateFrame();



	SwordWeapon() {}
	~SwordWeapon() {}
};


class BowWeapon : public GameNode
{
private:
	vector<tagWeapon*> _vWeapon;
	vector<tagWeapon*>::iterator _viWeapon;

	float _range;
	int _bulletMax;
	int _fixX, _fixY;
public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float damage, float x, float y, float angle);
	void draw();
	void move();

	bool isFiring()
	{
		if (_vWeapon.size() == 0) return false;
		else return true;
	}

	vector<tagWeapon*> getWeapon() { return _vWeapon; }
	POINT getPoint(int index) { return { (int)_vWeapon[index]->x, (int)_vWeapon[index]->y }; }
	void removeBullet(int index);

	BowWeapon() {}
	~BowWeapon() {}
};
