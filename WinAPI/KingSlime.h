#pragma once
#include "Enemy.h"

#define FRAMEDELAY		0.5f;

class KingSlime : public Enemy
{
private:
	//NormalBullet* _normalBullet				ź�� ������
	//BubbleBullet	* _bubbleBullet				ū źȯ->���� źȯ ������
	//BounceBullet* _bounceBullet				ƨ��� źȯ
	enum class STATE {STOP, WALK, ATTACK_BUBBLE, ATTACK_NORMAL, ATTACK_BOUNCE};
	enum class DIRECTION {DOWN = 0, LEFT, RIGHT, UP};

	STATE _state;
	DIRECTION _direction;

	bool _deadForOb;
	int _frameX, _frameY;
	int _frameSet;			//3������ ������ �� ����.

	int _stopSet;				//������ ������ ������ ���� ��������
	int _walkRndSet;		//�÷��̾ ���� �ɾ���� ����. (4~7 ����)
	int _attackSet;
	float _frameDelayTime;
public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	void frameUpdate();
	void move();

	void changeState(STATE state);
	void changeAnotherState();

	KingSlime() : _frameY(0) {}
	virtual ~KingSlime() {}
};
