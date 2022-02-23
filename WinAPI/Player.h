#pragma once
#include "GameNode.h"
#include "ItemClass.h"
#include "PlayerWeapon.h"

class Player : public GameNode {
private:
	//State, Frame
	enum class PLAYER_STATE { STOP, WALK, DODGE, ATTACK_NONE, ATTACK_SWORD, ATTACK_BOW, DEAD};
	enum class PLAYER_DIRECTION {LEFTDOWN, DOWN, RIGHTDOWN, LEFT, RIGHT, LEFTUP, UP, RIGHTUP };
	my::Image* _image;

	PLAYER_STATE _state;
	PLAYER_DIRECTION _direction;
	RECT _rc;
	float _x;
	float _y;
	int _stateFrameCount;
	float _comboCooldown;
	float _specialAttackCooldown;
	int _comboCount;

	
	bool _hit;
	int _hitInvTime;		//피격 후 무적시간

	bool _dodge;
	bool _attack;
	bool _swordSpecialAttack;

	float _frameTick;
	float _stateFrameTick;			//상태별 프레임 간격 딜레이
	int _startFrame;
	int _currentFrame;
	int _endFrame;

	bool _dead;

private:
	//Item
	CPlayer_Attribute _status;
	vector<Item*> _ability;
	Item* _equipItem;

	SwordWeapon* _sword;
	NormalWeapon* _normal;

private:
	//weaponClass

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setFrame();
	void changeState();
	void setDirectionByKeyInput();
	void setDirectionByMouseInput();
	void frameUpdate();

	void setDodge();
	void setAttack();
	void setSwordAttack();
	void setSwordSpecialAttack();
	void move();

	void setCollision();


public:
	//get, set

	RECT getRect() { return _rc; }

	POINT getPosition()
	{
		POINT pos = { _x, _y };
		return pos;
	}
	void setPosition(int x, int y)
	{
		_x = x;
		_y = y;
	}
	PLAYER_STATE getState() { return _state;	 }
};

//검
//setAttack의 else if ~~EQUIP TYPE 부분에서 1타 처리
//setSwordAttack에서 2, 3, 4, 5타부분 처리
//맨 위쪽에서 패리 공격 추가
//case 3에서 집중스택 쌓기 추가

//활,일반공격
//