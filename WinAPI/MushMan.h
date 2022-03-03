#pragma once
#include "Mushroom.h"
#include "Enemy.h"
#include "Mushroom.h"
#include "Bullets.h"

class GuidedBullet;
//�ӽ����� �θ��� ��

enum class MUSHMANSTATE { MU_IDLE, MU_MOVE, MU_ATTACK, MU_DEAD, MU_END };
enum class MUSHMANDIRECTION { MU_LEFT, MU_RIGHT, MU_UP, MU_DOWN };


class MushMan :public Enemy
{
private:
	MUSHMANSTATE	 _state;
	MUSHMANDIRECTION _direction;

	Mushroom* _mushroom;
	GuidedBullet * _mushroomBullet;

	int		_randomX, _randomY;
	int		_maxFrame;

	float _playerX, _playerY;
	float _angle;
	float _speed;				//�̵� �ӵ�
	float _moveWorldTime;
	float _plantMushroomWorldTime;
	float _mushroomLivingTime;
	float _mushroomAttackTime;
	float _deadTime;

	bool _mushroomCreateCheck; //���� ���� ���� üũ
	bool _mushroomRenderCheck;    //���� ���� ���� üũ	
	bool _deadForOb;			  //��� ���� [Enemy�� isActive�� �� ���� ����, deadForOb�� ü�� 0 ����]

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
	void createBullet();

public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

public:
	MushMan();
	virtual ~MushMan();
};

