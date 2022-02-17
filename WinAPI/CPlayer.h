#pragma once
class CPlayer
{
private:
	enum EState
	{
		IDLE=0,
		MOVE,
		ATTACK,
		DEFFENCE,
	};

	EState _state;
	RECT _rc;
	bool _isLeft;

	int _maxHp;
	int _hp;
	int _speed;
	int _damage;

public:
	EState getState() { return _state; }
	RECT getRC() { return _rc; }
	int getHp() { return _hp; }
	int getSpeed() { return _speed; }
	int getDamage() { return _damage; }

	void setState(EState state) { _state = state; }
	void setRC(RECT rc) { _rc = rc; }
	void setSpeed(int speed) { _speed = speed; }
	void setHp(int hp) { _hp = hp; }
	void setMaxHp(int maxhp) { _maxHp = maxhp; }
	void setDamage(int damage) { _damage = damage; }
	void beAttacked(int damage) { _hp -= damage; }


	CPlayer():_state(IDLE),_maxHp(10),_hp(10),_speed(3),_damage(10){}
	~CPlayer() {}
};

