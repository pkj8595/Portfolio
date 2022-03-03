#pragma once
#include "GameNode.h"
#include "IRectObserved.h"

#define MOVECOOLTIME 1
#define ATTACKCOOLTIME 3
#define MONSTER_MOVE_RANGE_LEFT CAMERAMANAGER->getDisplayCenterX() -252
#define MONSTER_MOVE_RANGE_RIGHT CAMERAMANAGER->getDisplayCenterX() + 148
#define MONSTER_MOVE_RANGE_UP CAMERAMANAGER->getDisplayCenterY() - 230
#define MONSTER_MOVE_RANGE_DOWN CAMERAMANAGER->getDisplayCenterY() + 20



class Player;

//Enemy (기반클래스) : 이 클래스를 기반으로 일반 몬스터들을 만든다고 했을때 문제가 없는지 생각
/*
	코드적 추상화 
	충돌, draw, 확장성,
	hp를 안만드는 이유 : 전투가 일어나기도 전에 필요없는 메모리를 잡아먹기 때문에 전투 할 때만 있으면 된다.
*/

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

	void setHpY(int y) { _hpY = y;}
	float getExp() { return _exp; }
	float getX() { return _x; }
	float getY() { return _y; }

	Enemy(void);
	virtual ~Enemy(void) {}
};

