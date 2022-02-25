#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"


enum class SNAKESTATE { SN_IDLE, SN_MOVE, SN_ATTACK, SN_END };
enum class SNAKEDIRECTION { SN_LEFT, SN_RIGHT, SN_UP, SN_DOWN, SN_END };

class Snake:public Enemy
{
private:
	ThreeDirectionMissile*  _threeDirBullet;
	TwoDirectionMissile*	_twoDirBullet;

	SNAKESTATE		_state;
	SNAKEDIRECTION  _direction;

	float	_moveWorldTime;
	float	_playerDistance;
	float	_speed;				//�̵� �ӵ�
	int		_range;				//�÷��̾� Ž�� ����
	int		_randomX, _randomY;
	int		_maxFrameX;
	float	_frameSpeed;


public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);

	void randomPosCreate();
	void randomMove();
	void attack();
	bool playerCheck(); //�÷��̾� �����Լ�
	void frame();

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	Snake();
	virtual ~Snake();
};

