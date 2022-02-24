#pragma once
#include "GameNode.h"
#include "Enemy.h"
#include "Bullets.h"

class Player;
class EnemyManager: public GameNode
{
private:
	//** ���������� ���ϰ� ���͸� ������
	//*** ������ ���������� �����Ѵ� >> ��üȭ�ı�..?
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

