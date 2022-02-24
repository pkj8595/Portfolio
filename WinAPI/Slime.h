#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"

#define COLLRECTSIZEY 30

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


class Slime:public Enemy
{
private:
	
	Animation* _ani;
	SLIMEDIRECTION _slimeDir;
	SLIMESTATE _slimestate;
	int randomX , randomY;
	float _x, _y;
	float _speed;
	float _angle;
	float _range; //�÷��̾� Ž�� ����
	float _time;
	float _worldTime;

	float _moveRange;
	int _attTime; 


	ThreeDirectionMissile* _slimebullet;
	CircleMissile* _slimeCirclebullet;

	RECT _rc_playerCollCheck;


	float _playerDistance;

	bool _moveCheck;
	bool _attCheck;
	int attRange;

public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation();
	//void bulletParttern(); //�Ѿ� ����

	void attack();

	void randomMove();
	bool playerCheck(); //�÷��̾� �����Լ�

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject();

	Slime();
	virtual ~Slime();
};

/*
1. ���� ����� ���� ��Ÿ� �ȿ� ������ ���� �Լ� ����
2. ���� ��� �������� �ٶ󺸱�

attack()
{

�ڽ� ���X && ���� ���� �Ÿ��� ���� ��Ÿ� �ȿ� ������
if()
{
������ ���߰�

���� ��� �ٶ󺻴�.

�ֱ� ���� �������� ���� �ð� ������ ���� ����

}

}

*/