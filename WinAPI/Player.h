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
	int _hitInvTime;		//�ǰ� �� �����ð�

	bool _dodge;
	bool _attack;
	bool _swordSpecialAttack;

	float _frameTick;
	float _stateFrameTick;			//���º� ������ ���� ������
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

	//TotalAttribute �ջ�
	void computeTotalAttribute();

	float calculatePhysicalDamage();
	float calculateMagicDamage();

	void setLevelUp();
	void setDead();
	Inventory* getInventory() { return _inventory; }
public:
	//������, ������

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

//��
//setAttack�� else if ~~EQUIP TYPE �κп��� 1Ÿ ó��
//setSwordAttack���� 2, 3, 4, 5Ÿ�κ� ó��
//�� ���ʿ��� �и� ���� �߰�
//case 3���� ���߽��� �ױ� �߰�

//Ȱ,�Ϲݰ���
//