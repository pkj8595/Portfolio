#pragma once
#include "Enemy.h"
#include "Bullets.h"

enum class FAIRYSTATE { FA_MOVE, FA_ATTACK, FA_DEAD, FA_END };
enum class FAIRYDIRECTION { FA_LEFT, FA_RIGHT, FA_UP, FA_DOWN };
enum class FAIRYATTACK { FA_NORMAL, FA_FAIRY, FA_BUBBLE };

class ForestFairy :public Enemy
{
private:
	NormalBullet* _normalBullet;
	FairyBullet* _fairyBullet;
	BubbleBullet* _bubbleBullet;

	FAIRYSTATE _state;
	FAIRYDIRECTION _direction;
	FAIRYATTACK _attackParttern;

	float _angle;
	float _speed;
	float _moveWorldTime;
	float _playerDistance;
	float _attackDistance;
	float _frameSpeed;
	float _deadTimeCount;

	float _attackCoolTime;

	int   _randomX, _randomY;
	int	  _range;
	int	  _maxFrameX;
	int	  _frameX, _frameY;

	bool  _deadForOb;	

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
	bool playerCheck(); 
	void normalBullet();
	void fariyBullet();
	void bubbleBullet();
public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	ForestFairy();
	virtual ~ForestFairy();
};