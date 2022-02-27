#pragma once
#pragma once
#include "GameNode.h"
	//#include "ItemClass.h"
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

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	virtual STObservedData getRectUpdate();

	void setFrame();
	void changeState();
	void setDirectionByKeyInput();
	void setDirectionByMouseInput();
	void frameUpdate();

	void move();

	void healStamina();
	void checkLevelUp();

	void setCollision();

	//TotalAttribute 합산
	void computeTotalAttribute();

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
	PLAYER_STATE getState() { return _state; }
	void printUI() { _statusUI->render(); }

	bool _isTextShow;
	bool isDead() { return _dead; }
};

