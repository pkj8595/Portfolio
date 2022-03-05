#pragma once
#include "GameNode.h"
#include "PlayerWeapon.h"
#include "PlayerStatusUI.h"
#include "Inventory.h"

class LobbyPlayer : public GameNode
{
private:
	ObservedType _type;
	//State, Frame
	enum class PLAYER_STATE { STOP, WALK,DEAD };
	enum class PLAYER_DIRECTION { LEFTDOWN, DOWN, RIGHTDOWN, LEFT, RIGHT, LEFTUP, UP, RIGHTUP };
	my::Image* _image;
	int _level;
	PLAYER_STATE _state;
	PLAYER_DIRECTION _direction;
	RECT _rc;
	float _x;
	float _y;
	int _stateFrameCount;
	bool _isTextShow;

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

	int _beforeItemSize;
	int _currentItemSize;


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

	void move();

	void healStamina();
	void checkLevelUp();

	void setCollision();


public:
	//������, ������

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }

	void setisShowText(bool ShowText) 
	{ 
		_isTextShow = ShowText; 
	}

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
	PLAYER_STATE getState() { return _state; }

	bool isDead() { return _dead; }
};

