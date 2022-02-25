#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"

#define MOVECOOLTIME 1
#define ATTACKCOOLTIME 3
#define MONSTER_MOVE_RANGE_LEFT CENTER_X -252
#define MONSTER_MOVE_RANGE_RIGHT CENTER_X + 148
#define MONSTER_MOVE_RANGE_UP CENTER_Y - 230
#define MONSTER_MOVE_RANGE_DOWN CENTER_Y + 20

enum class SLIMESTATE { SL_IDLE, SL_MOVE, SL_ATTACK, SL_DEAD, SL_END };
enum class SLIMEDIRECTION { SL_LEFT, SL_RIGHT, SL_UP, SL_DOWN, SL_END };
enum class SLIMEATTACK { SL_PARTTERN1, SL_PARTTERN2, SL_PARTTERN_END };


class Slime:public Enemy
{
private:
	ThreeDirectionMissile*	_slimebullet;
	CircleMissile*			_slimeCirclebullet;

	SLIMEDIRECTION			_direction;
	SLIMESTATE				_state;
	SLIMEATTACK				_attackParttern;

	float	_speed;				//�̵� �ӵ�
	float	_angle;
	float	_playerDistance;
	float	_moveWorldTime;
	float	_attacWorldTime;
	float	_randomTimeCount;
	float	_frameSpeed;
	float	_deadTimeCount;
	int		_index;
	int		_frameY;
	int		_randomX, _randomY;
	int		_range;				//�÷��̾� Ž�� ����
	int		_attackRange;		//���� ��Ÿ�
	bool	_moveCheck;			//���ݽ� ������ üũ
	bool _deadForOb;


public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void frame();
	void animation();
	void pursuePlayer(); //�÷��̾� ����
	void randomMove(); //�������� �̵� ���
	bool playerCheck(); //�÷��̾� �����Լ�
	void randomPosCreate();
	void attackParttern(); //���� ���� ������
	void circleDirectionBullet();
	void threeDirectionBullet();


public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	Slime();
	virtual ~Slime();
};
