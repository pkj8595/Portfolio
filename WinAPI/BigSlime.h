#pragma once
#include "Enemy.h"
#include "Bullets.h"
class BigSlime : public Enemy
{
private:

	my::Image* _bossHpFrameImage;
	my::Image* _bossHpImage;
	my::Image* _bossHpDamageImage;
	float _maxHP;
	int _bossHpAlpha;
	float _hpWidth;
	float _damageHpWidth;
	int _hpY;

	NormalBullet* _normalBullet;				//≈∫∏∑ ø©∑Ø∞≥
	BubbleBullet* _bubbleBullet;				//≈´ ≈∫»Ø->¿€¿∫ ≈∫»Ø ø©∑Ø∞≥
	enum class STATE { STOP, WALK, ATTACK_BUBBLE, ATTACK_NORMAL, DEAD };
	enum class DIRECTION { DOWN = 0, LEFT, RIGHT, UP };

	RECT _fixRC;
	STATE _state;
	DIRECTION _direction;

	bool _alreadyShot;
	float _angle;

	bool _deadForOb;
	int _frameX, _frameY;
	int _frameSet;			

	int _stopSet;				
	int _walkRndSet;		
	int _attackSet;
	float _frameDelayTime;

	int _deadCount;
public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	void hpUpdate();
	void hpRender(int x, int y);

	void frameUpdate();
	void setDirection();
	void move();

	void changeState(STATE state);
	void changeDirectionState();
	void changeAnotherState();


	BigSlime() : _frameY(0) {}
	virtual ~BigSlime() {}
};

