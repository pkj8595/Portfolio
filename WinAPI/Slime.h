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
	float _speed; //이동 속도
	int _randomX, _randomY;
	float _frameSpeed;
	int _index;
	int _frameY;
	float _worldTime;
	float _moveWorldTime;
	float _attacWorldTime;
	float _randomTimeCount;
	float _angle;
	float _range; //플레이어 탐지 범위
	float _time;
	float _playerDistance;
	bool _moveCheck; //공격시 움직임 체크
	bool _playerCheck;
	float _attackRange; //공격 사거리
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
	void pursuePlayer(); //플레이어 추적
	void randomMove(); //랜덤으로 이동 기능
	bool playerCheck(); //플레이어 감지함수

	void randomPosCreate();
	//void bulletParttern(); //총알 패턴

	void attackParttern(); //공격 패턴 정해줌

	void circleDirectionBullet();
	void threeDirectionBullet();


public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	Slime();
	virtual ~Slime();
};
