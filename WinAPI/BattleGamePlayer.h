#pragma once
#include "HPprogressBar.h"
#include "iSkill.h"

#define BULLET_MAX	30

//발사체 관리
struct tagBattleBullet
{
	RECT rc;
	bool isfire;
	int _direction;
	
};

class BattleGamePlayer
{
private:
	HPprogressBar _hpBar;
	//iSkill *_skill[3];
	RECT _rc;
	int _hp;
	int _maxHp;
	int _speed;
	int _damage;
	int _directionSave;
	bool _isDie;
	bool _isFirst;
	COLORREF _rgb;
	

public:
	tagBattleBullet _bullet[BULLET_MAX];

	BattleGamePlayer();
	BattleGamePlayer(RECT rc,int hp,int speed,int damage , COLORREF rgb, bool isFirst,int derection);
	~BattleGamePlayer();
	
	void render(HDC hdc);
	void update();

	void fire(void);

	//void SetSkill(iSkill* skill);
	//bool TriggerSkill(int key);

	void beAttacked(int damage) { _hp -= damage; }


public:
	
	RECT getRC() { return _rc; }
	int getHp() { return _hp; }
	int getSpeed() { return _speed; }
	int getDamage() { return _damage; }
	bool getIsDie() { return _isDie; }
	

	void setIsDie(bool isDie) { _isDie = isDie; }
	void setSpeed(int speed) { _speed = speed; }
	void setHp(int hp) { _hp = hp; }
	void setMaxHp(int maxhp) { _maxHp = maxhp; }
	void setDamage(int damage) { _damage = damage; }
};

