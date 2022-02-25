#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"


enum class SNAMESTATE { SNAKE_IDLE, SNAKE_MOVE, SNAKE_ATTACK, SNAKE_END };
enum class SNAKEDIRECTION { SNAKE_LEFT, SNAKE_RIGHT, SNAKE_UP, SNAKE_DOWN, SNAKE_END };

class Snake:public Enemy
{
private:
	Animation* _ani;
	int randomX, randomY;
	float _x, _y;
	float _speed;
	float _angle;
	float _range;
	float _time;
	SNAKEDIRECTION  _direction;
	SNAMESTATE _stae;
	float _playerDistance;

	bool _moveCheck;
	int attRange;
	float _worldTime;
	int _attTime;

	ThreeDirectionMissile* _threebullet;
	TwoDirectionMissile* _twobullet;

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);

	void randomMove();
	void attack();
	bool playerCheck(); //플레이어 감지함수

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	Snake();
	virtual ~Snake();
};

