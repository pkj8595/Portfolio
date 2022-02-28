#pragma once
#include "GameNode.h"
//#include "ItemClass.h"
#include "PlayerWeapon.h"
#include "PlayerStatusUI.h"
#include "IRectObserved.h"
#include "Inventory.h"
#include "EffectManager.h"

class Player : public GameNode, public IRectObserved
{
private:
	EffectManager* _efm;

	ObservedType _type;
	//State, Frame
	enum class PLAYER_STATE { STOP, WALK, DODGE, ATTACK_NONE, ATTACK_SWORD, ATTACK_BOW, DEAD};
	enum class PLAYER_DIRECTION {LEFTDOWN, DOWN, RIGHTDOWN, LEFT, RIGHT, LEFTUP, UP, RIGHTUP };
	my::Image* _image;
	my::Image* _hitBG;
	my::Image* _dodgeBG;
	int _hitAlpha;
	int _dodgeAlpha;
	int _level;

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
	//Item, UI
	CPlayer_Attribute _status;
	CPlayer_Attribute _totalStatus;
	Item** _equipItem;

	int _beforeItemSize;
	int _currentItemSize;

	SwordWeapon* _sword;
	NormalWeapon* _normal;
	BowWeapon* _bow;
	PlayerStatusUI* _statusUI;

	Inventory* _inventory;


private:
	//weaponClass
	my::Image* _swordStackImage;
	my::Image* _bowStackImage;
	
	int _swordStack;
	int _bowStack;
	bool _alreadyAddBowStack;
	bool _tripleshot;
	float _tripleShotStartCount;

	float _attackCount;

	void showSwordStack();
	void showBowStack();
	void checkBowStack();

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

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

	void healStamina();

	void setCollision();

	//TotalAttribute 합산
	void computeTotalAttribute();

	float calculatePhysicalDamage();
	float calculateMagicDamage();

	void setLevelUp();
	void setDead();
	Inventory* getInventory() { return _inventory; }
public:
	//접근자, 지정자

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

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
	void printUI() { _statusUI->render(); }
	void printStack();
	void printInventory();
	void printHitBG();
	
	bool _isTextShow;
	bool isDead() { return _dead; }


	void addExp(int exp) { _status._experience += exp; }
	
	NormalWeapon* getNormalWeapon() { return _normal; }
	BowWeapon* getBowWeapon() { return _bow; }
};

//검
//setAttack의 else if ~~EQUIP TYPE 부분에서 1타 처리
//setSwordAttack에서 2, 3, 4, 5타부분 처리
//맨 위쪽에서 패리 공격 추가
//case 3에서 집중스택 쌓기 추가

//활,일반공격
//