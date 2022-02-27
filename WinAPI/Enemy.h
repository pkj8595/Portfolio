#pragma once
#include "GameNode.h"
#include "IRectObserved.h"

#define MOVECOOLTIME 1
#define ATTACKCOOLTIME 3
#define MONSTER_MOVE_RANGE_LEFT CENTER_X -252
#define MONSTER_MOVE_RANGE_RIGHT CENTER_X + 148
#define MONSTER_MOVE_RANGE_UP CENTER_Y - 230
#define MONSTER_MOVE_RANGE_DOWN CENTER_Y + 20



class Player;

//Enemy (���Ŭ����) : �� Ŭ������ ������� �Ϲ� ���͵��� ����ٰ� ������ ������ ������ ����
/*
	�ڵ��� �߻�ȭ 
	�浹, draw, Ȯ�强,
	hp�� �ȸ���� ���� : ������ �Ͼ�⵵ ���� �ʿ���� �޸𸮸� ��ƸԱ� ������ ���� �� ���� ������ �ȴ�.
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

	ObservedType _type;
	bool _isActive;

	POINT _playerPos;
	Player* _player;

	float _hp;

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

public:
	void setPlayerPos(POINT playerPos) { _playerPos = playerPos; }
	void setPlayer(Player& player) { _player = &player; }

	Enemy(void);
	virtual ~Enemy(void) {}
};

