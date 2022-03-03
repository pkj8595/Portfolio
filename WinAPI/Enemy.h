#pragma once
#include "GameNode.h"
#include "IRectObserved.h"

#define MOVECOOLTIME 1
#define ATTACKCOOLTIME 3
#define MONSTER_MOVE_RANGE_LEFT CAMERAMANAGER->getDisplayCenterX() -260
#define MONSTER_MOVE_RANGE_RIGHT CAMERAMANAGER->getDisplayCenterX() + 148
#define MONSTER_MOVE_RANGE_UP CAMERAMANAGER->getDisplayCenterY() - 10
#define MONSTER_MOVE_RANGE_DOWN CAMERAMANAGER->getDisplayCenterY() + 250



class Player;

class Enemy : public GameNode, public IRectObserved
{
protected:
	my::Image* _image;
	RECT _rc;
	int _currentFrameX;
	int _currentFrameY;

	float _attack;
	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;
	float _bulletFireCount;
	float _rndFireCount;

	float _exp;

	ObservedType _type;
	bool _isActive;

	POINT _playerPos;
	Player* _player;

	float _hp;
	float _hpY;

	bool _boss;
	bool _miniboss;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move(void);
	virtual void draw(void);
	virtual void animation(void);

	virtual bool bulletCountFire(void);

	virtual RECT getRect(void) { return _rc; }
	virtual bool getIsActive(void) { return _isActive; }

	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);
	bool isBoss() { return _boss; }
	bool isMiniBoss() { return _miniboss; }

public:
	void setPlayerPos(POINT playerPos) { _playerPos = playerPos; }
	void setPlayer(Player& player) { _player = &player; }

	void setHpY(int y) { _hpY = y; }
	float getExp() { return _exp; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getHp() { return _hp; }

	Enemy(void);
	virtual ~Enemy(void) {}
};

