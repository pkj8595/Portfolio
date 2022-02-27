#pragma once
#include "Enemy.h"
#include "Bullets.h"


enum class SNAKESTATE { SN_IDLE, SN_MOVE, SN_ATTACK,SN_DEAD, SN_END };
enum class SNAKEDIRECTION { SN_LEFT, SN_RIGHT, SN_UP, SN_DOWN, SN_END };
enum class SNAKEPARTTERN { SN_ATTACK1, SN_ATTACK2 };

class Snake:public Enemy
{
private:
	ThreeDirectionMissile*  _threeDirBullet;
	TwoDirectionMissile*	_twoDirBullet;

	SNAKESTATE		_state;
	SNAKEDIRECTION  _direction;
	SNAKEPARTTERN	_parttern;

	int		_range;				//�÷��̾� Ž�� ����
	int		_randomX, _randomY;
	int		_maxFrameX;
	int		_partternNum;
	float	_moveWorldTime;
	float	_attacWorldTime;
	float	_attackMoveWorldTime;
	float	_deadTimeCount;
	float	_playerDistance;
	float	_attackRange;
	float	_angle;
	float	_frameSpeed;
	float	_speed;				//�̵� �ӵ�

	bool	_playerCheck; //�÷��̾ ���ݹ��� �ȿ� ���Դ��� üũ
	bool	_bulletFireCheck; //�Ѿ� �߻��ߴ��� üũ
	bool	_deadForOb;		//��� ���� [Enemy�� isActive�� �� ���� ����, deadForOb�� ü�� 0 ����]

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

	//�Ѿ� �߻�
	void threeDirectionBullet();
	void twoDirectionBullet();

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	Snake();
	virtual ~Snake();
};

