#pragma once
#include "Enemy.h"
#include "Bullets.h"

#define FRAMEDELAY		0.5f;

class KingSlime : public Enemy
{
private:
	my::Image* _bossNameImage;
	int _bossNameAlpha;
	bool _bossNameFadeIn;

	my::Image* _bossHpFrameImage;
	my::Image* _bossHpImage;
	my::Image* _bossHpDamageImage;
	float _maxHP;
	int _bossHpAlpha;
	float _hpWidth;
	float _damageHpWidth;

	NormalBullet* _normalBullet;				//ź�� ������
	BubbleBullet* _bubbleBullet;				//ū źȯ->���� źȯ ������
	enum class STATE {STOP, WALK, ATTACK_BUBBLE, ATTACK_NORMAL, DEAD};
	enum class DIRECTION {DOWN = 0, LEFT, RIGHT, UP};

	RECT _fixRC;
	STATE _state;
	DIRECTION _direction;

	bool _alreadyShot;
	float _angle;

	bool _deadForOb;
	int _frameX, _frameY;
	int _frameSet;			//3������ ������ �� ����.

	int _stopSet;				//������ ������ ������ ���� ��������
	int _walkRndSet;		//�÷��̾ ���� �ɾ���� ����. (4~7 ����)
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

	void bossNameUpdate();
	void hpUpdate();
	void hpRender(int x, int y);

	void frameUpdate();
	void setDirection();
	void move();

	void changeState(STATE state);
	void changeDirectionState();
	void changeAnotherState();

	KingSlime() : _frameY(0) {}
	virtual ~KingSlime() {}
};

