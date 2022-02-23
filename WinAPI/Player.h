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

//��
//setAttack�� else if ~~EQUIP TYPE �κп��� 1Ÿ ó��
//setSwordAttack���� 2, 3, 4, 5Ÿ�κ� ó��
//�� ���ʿ��� �и� ���� �߰�
//case 3���� ���߽��� �ױ� �߰�

//Ȱ,�Ϲݰ���
//