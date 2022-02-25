#pragma once
#include "GameNode.h"
#include "IRectObserved.h"

#define FLAME_COUNT		4.0f



class tagCBullet :public IRectObserved
{
public:
	ObservedType type;
	my::Image* img;
	my::Image* reflectImg;
	RECT rc;
	int radius;
	int count;
	float damage;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;

	void init(void);
	void release(void);
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);
};

//추상 미사일
class AMissile : public GameNode
{
protected:
	vector<tagCBullet*> _vBullet;
	vector<tagCBullet*>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void fire(float x, float y);
	virtual void draw(void);
	virtual void move(void);
	virtual void isRange(void);
	virtual void CheckFire(void);

	AMissile() {}
	virtual ~AMissile() {}
};


//공용총알
class Bullet : public GameNode
{
private:
	vector<tagCBullet*> _vBullet;
	vector<tagCBullet*>::iterator _viBullet;

	const char* _imageName;
	int _bulletMax;
	float _range;
	int _currentFrameX;

public:
	HRESULT init(const char*imageName,int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);
	void CheckFire(void);

	void removeBullet(int arrNum);
	vector<tagCBullet*> getBullet(void) {return _vBullet;}

	Bullet() {}
	virtual ~Bullet() {}
};



class LinearMissile : public AMissile
{
private:
	
public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void move(void);
	virtual void fire(float x, float y);
	virtual void draw(void);
	LinearMissile() {}
	~LinearMissile() {}
};

class CaseShotMissile : public AMissile
{
private:
	int _bulletCount;
	float _firstAngle;
	const float _offsetAngle = 0.1f;

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void move(void);
	virtual void fire(float x, float y);
	virtual void draw(void);

	CaseShotMissile() {}
	~CaseShotMissile() {}
};


class BlackholeMissile : public AMissile 
{
private:
	
public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void move(void);
	virtual void fire(float x, float y);
};


class ThreeDirectionMissile : public AMissile
{
private:
	int _bulletCount;
	float _firstAngle;
	const float _offsetAngle = 0.3f;

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void move(void);
	virtual void fire(float x, float y, float angle);
	virtual void draw(void);
	ThreeDirectionMissile() {}
	~ThreeDirectionMissile() {}
};

class TwoDirectionMissile : public AMissile
{
private:
	int _bulletCount;
	float _firstAngle;
	const float _offsetAngle = 0.3f;

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void move(void);
	virtual void fire(float x, float y, float angle);
	virtual void draw(void);
	TwoDirectionMissile() {}
	~TwoDirectionMissile() {}
};

class CircleMissile :public AMissile
{
private:
	int _bulletCount;
	float _firstAngle;
	const float _offsetAngle = 36.f;

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void move(void);
	virtual void fire(float x, float y);
	virtual void draw(void);
	CircleMissile() {}
	~CircleMissile() {}
};