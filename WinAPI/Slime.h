#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"

#define MOVECOOLTIME 1
#define ATTACKCOOLTIME 3

enum class SLIMESTATE
{
	SM_IDLE,
	SM_MOVE,
	SM_ATTACK,
	SM_END
};

enum class SLIMEDIRECTION
{
	SM_LEFT,
	SM_RIGHT,
	SM_UP,
	SM_DOWN,
	SM_END
};

enum class SLIMEATTACK
{
	SLIME_PARTTERN1,
	SLIME_PARTTERN2,
	SLIME_PARTTERN_END
};


class Slime:public Enemy
{
private:
	ThreeDirectionMissile* _slimebullet;
	CircleMissile* _slimeCirclebullet;
	SLIMEDIRECTION _direction;
	SLIMESTATE _state;
	float _speed; //�̵� �ӵ�
	int _randomX, _randomY;
	float _frameSpeed;
	int _index;
	int _frameY;
	float _worldTime;
	float _moveWorldTime;
	float _attacWorldTime;
	float _randomTimeCount;
	float _angle;
	float _range; //�÷��̾� Ž�� ����
	float _time;
	float _playerDistance;
	bool _moveCheck; //���ݽ� ������ üũ
	bool _playerCheck;
	float _attackRange; //���� ��Ÿ�
	float _attackCheck;

	SLIMEATTACK _attackParttern;

	RECT _attRect;

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
	//void bulletParttern(); //�Ѿ� ����

	void attackParttern(); //���� ���� ������

	void circleDirectionBullet();
	void threeDirectionBullet();


public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	Slime();
	virtual ~Slime();
};
