#pragma once
#include "GameNode.h"
#include "Bullets.h"
#include "ProgressBar.h"
#include "HpImgBar.h"
#include "Animation.h"

#define ROCKET_SPEED	3.0f

class EnemyManager;

enum EWeapon 
{
	MISSILE,BEAM
};

enum class EPPlayer_State
{
	Idle =0,
	Right,
	Left
};

class CProjectPlayer : public GameNode, public IRectObserved
{
private:
	my::Image* _image;
	HpImgBar* _hpBar;
	EPPlayer_State _pState;
	EPPlayer_State _previousState;
	RECT _rc;
	float _x, _y;

	float _currentHp;
	float _maxHp;
	float _bulletCoolTime;
	float _bulletWorldTime;

	//animation
	float _rndTimeCount;
	float _worldTimeCount;
	int _currentFrameX;
	int _currentFrameY;

	Animation* _currentAni;

	//AMissile
	AMissile* _aMissile;		//실질적으로 쓰이는 미사일
	AMissile* _arrAMissile[5];	//마사일 창고

	//observer
	ObservedType _type;
	bool _isActive;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }
	RECT getRect(void) { return _rc; }
	bool getIsActive() { return _isActive; }

	inline void hitDamage(float damage) 
	{
		if (_currentHp <= 0) 
		{
			_currentHp = 0; 
			return;
		}
		_currentHp -= damage;
	}

	//스프레티지
	void setAMissile(int index);
	void fireAMissile(void);

	//animation
	void animation(void);

	//observer
	virtual STObservedData getRectUpdate();
	virtual void collideObject();
	

	CProjectPlayer() {}
	~CProjectPlayer() {}
};

