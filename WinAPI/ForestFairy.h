#pragma once
#include "Enemy.h"
#include "Bullets.h"

enum class FAIRYSTATE {FA_MOVE, FA_ATTAACK, FA_DEAD, FA_END};
enum class FAIRYDIRECTION {FA_LEFT, FA_RIGHT, FA_UP, FA_DOWN};

class ForestFairy :public Enemy
{
private:
	FAIRYSTATE _state;
	FAIRYDIRECTION _direction;

	float _deadTimeCount;
	float _moveWorldTime;
	float _angle;
	float _speed;
	float _frameSpeed;
	float _playerDistance;

	int   _randomX, _randomY;
	int	  _range;

	bool  _deadForOb;		//��� ���� [Enemy�� isActive�� �� ���� ����, deadForOb�� ü�� 0 ����]

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);
	void frame();

	void randomPosCreate();
	void randomMove();
	void attack();
	bool playerCheck(); //�÷��̾� �����Լ�

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	ForestFairy();
	virtual ~ForestFairy();
};

