#pragma once
#include "Mushroom.h"
#include "Enemy.h"
#include "Mushroom.h"
#include "Bullets.h"

class GuidedBullet;
//머쉬룸을 부르는 애

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
	float _speed;				//이동 속도
	float _moveWorldTime;
	float _plantMushroomWorldTime;
	float _mushroomLivingTime;
	float _mushroomAttackTime;
	float _deadTime;

	bool _mushroomCreateCheck; //버섯 생성 여부 체크
	bool _mushroomRenderCheck;    //버섯 랜더 여부 체크	
	bool _deadForOb;			  //사망 여부 [Enemy의 isActive는 몹 삭제 전용, deadForOb는 체력 0 여부]

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

