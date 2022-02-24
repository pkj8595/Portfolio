#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class Player;
class EnemyManager: public GameNode
{
private:
	//** 더블포인터 패턴과 벡터를 엮을때
	//*** 프랜드 정보은닉을 무시한다 >> 객체화파괴..?
	typedef vector<Enemy*> vEnemy;
	typedef vector<Enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

	Bullet* _bullet;
	Player* _pPlayer;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void removeMinion(int arrNum);
	void checkActive(void);

	void minionBulletFire(void);

	Bullet* getBullet(void) { return _bullet; }
	void setRoketMemoryAddress(Player* rk) { _pPlayer = rk; }
	vEnemy getEnemy() { return _vMinion; }
	void clearMinion() { _vMinion.clear(); }

	EnemyManager();
	~EnemyManager();
};

