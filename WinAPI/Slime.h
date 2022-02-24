#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"

#define PI 3.141592f

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
	float _speed; //이동 속도
	int _randomX, _randomY;
	float _worldTime; 
	float _frameSpeed;
	int _index;
	int _frameY;
	float _randomTimeCount;
	float _moveTimeCount;
	float _playerDistance;
	float _range; //플레이어 탐지 범위
	bool _moveCheck; //공격시 움직임 체크


public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void frame();
	void animation();


	void randomValue(int i); //정수를 랜덤으로 뽑아내는 기능
	void randomMove(); //랜덤으로 이동 기능

	//void bulletParttern(); //총알 패턴

	//void attack();
	//
	//void randomMove();
	bool playerCheck(); //플레이어 감지함수

public:
	Slime();
	virtual ~Slime();
};

/*private:
	//Animation* _ani;
	//SLIMEDIRECTION _slimeDir;
	//SLIMESTATE _slimestate;
	//int randomX , randomY;
	//float _x, _y;
	//float _speed;
	//float _angle;
	//float _range; //플레이어 탐지 범위
	//float _time;
	//float _worldTime;

	//float _moveRange;
	//int _attTime;


	//ThreeDirectionMissile* _slimebullet;
	//CircleMissile* _slimeCirclebullet;

	//RECT _rc_playerCollCheck;


	//float _playerDistance;

	//bool _moveCheck;
	//bool _attCheck;
	//int attRange;*/

/*
switch (_slimeDir)
	{
	case SLIMEDIRECTION::SM_LEFT: //왼쪽일 때
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
				_ani->setPlayFrame(3, 6, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(15, 18, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(27, 30, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_RIGHT: //오른쪽일 때
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
				_ani->setPlayFrame(6, 9, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(18, 21, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(30, 33, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_UP: //위쪽
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
			_ani->setPlayFrame(9, 12, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(21, 24, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(33, 36, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_DOWN: //아래쪽
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
			_ani->setPlayFrame(0, 3, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(12, 15, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(24, 27, false, true);
			break;
		}
		break;



*/

/*



*/