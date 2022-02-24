#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"

//#define PI 3.141592f

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
	SLIMEDIRECTION _direction;
	SLIMESTATE _state;
	float _speed; //�̵� �ӵ�
	int _randomX, _randomY;
	float _worldTime; 
	float _frameSpeed;
	int _index;
	int _frameY;
	float _randomTimeCount;
	float _moveTimeCount;
	
	Animation* _ani;
	SLIMEDIRECTION _slimeDir;
	SLIMESTATE _slimestate;

	SLIMEDIRECTION _beforeSlimeDir;
	SLIMESTATE _beforeSlimestate;

	float _x, _y;
	float _angle;
	float _range; //�÷��̾� Ž�� ����
	float _time;

	float _moveRange;
	int _attTime; 


	ThreeDirectionMissile* _slimebullet;
	CircleMissile* _slimeCirclebullet;

	RECT _rc_playerCollCheck;

	float _playerDistance;

	bool _moveCheck; //���ݽ� ������ üũ


public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void frame();
	void animation();


	void randomValue(int i); //������ �������� �̾Ƴ��� ���
	void randomMove(); //�������� �̵� ���

	//void bulletParttern(); //�Ѿ� ����

	//void attack();
	//
	//void randomMove();
	bool playerCheck(); //�÷��̾� �����Լ�

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	Slime();
	virtual ~Slime();
};
