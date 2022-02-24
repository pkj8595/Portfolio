#pragma once
#include "Stdafx.h"

enum class EITEM_TYPE
{
	EMPTY=0,
	MATERIAL,
	SCROLL,
	ABILITY,
	EQUIP_WEAPOEN_BOW,
	EQUIP_WEAPOEN_SWORD,
	EQUIP_ARMOR,
	EQUIP_HAT,
	EQUIP_SHOES,
};

class CPlayer_Attribute
{
public:
	int	  _hp;				//hp
	int   _maxHp;			//maxhp
	int   _mana;			//mana
	int   _maxMana;			//maxMana
	float _critical;		//크리확률
	float _offencePower;	//공격력
	float _magicPower;		//마법력
	float _speed;			//이동속도
	float _attackSpeed;		//공격속도
	float _damageBalance;	//데미지 밸런스
	float _experience;		//경험치
	float _maxExperience;		//최대 경험치
	float _stamina;			//스테미나
	float _maxStamina;			//최대 스테미나

	CPlayer_Attribute operator+(CPlayer_Attribute other)
	{
		CPlayer_Attribute temp;
		temp._hp = _hp + other._hp;
		temp._maxHp = _maxHp + other._maxHp;
		temp._mana = _mana + other._mana;
		temp._maxMana = _maxMana + other._maxMana;
		temp._critical = _critical + other._critical;
		temp._offencePower = _offencePower + other._offencePower;
		temp._magicPower = _magicPower + other._magicPower;
		temp._speed = _speed + other._speed;
		temp._attackSpeed = _attackSpeed + other._attackSpeed;
		temp._damageBalance = _damageBalance + other._damageBalance;
		temp._experience = _experience + other._experience;
		temp._maxExperience = _maxExperience + other._maxExperience;
		temp._stamina = _stamina + other._stamina;
		temp._maxStamina = _maxStamina + other._maxStamina;
		return temp;
	}

	void operator=(CPlayer_Attribute other)
	{
		_hp = other._hp;
		_maxHp = other._maxHp;
		_mana = other._mana;
		_maxMana = other._maxMana;
		_critical = other._critical;
		_offencePower = other._offencePower;
		_magicPower = other._magicPower;
		_speed = other._speed;
		_attackSpeed = other._attackSpeed;
		_damageBalance = other._damageBalance;
		_experience = other._experience;
		_maxExperience = other._maxExperience;
		_stamina = other._stamina;
		_maxStamina = other._maxStamina;
	}

	CPlayer_Attribute()
	{
		_hp = 0;
		_maxHp = 0;
		_mana = 0;
		_maxMana = 0;
		_critical = 0.0f;
		_offencePower = 0.0f;
		_magicPower = 0.0f;
		_speed = 0.0f;
		_attackSpeed = 0.0f;
		_damageBalance = 0.0f;
		_experience = 0.0f;
		_maxExperience = 0.0f;
		_stamina = 0.0f;
		_maxStamina = 0.0f;
	}
	~CPlayer_Attribute() {}
};

//벡터에 아이템을 넣어서 CPlayer_Attribute를 더해주는 방식
// CPlayer_Attribute, 장착 item 중인 무기 1개, vector<item*>ABILITY
class Item
{
public:
	int _index;
	EITEM_TYPE _type;				//아이템 타입
	string _name;					//name
	string _description;			//설명
	int _imgNum;					//장비 이미지 넘버
	int _equip_level;				//장비 레벨
	int _price;						//가격

	CPlayer_Attribute _attribute;	//능력치

	inline void setItemData(int index,EITEM_TYPE type, string name, string description, int imgNum, int equip_level, int price)
	{
		_index = index;
		_type = type;
		_name= name;
		_description= description;
		_imgNum = imgNum;
		_equip_level= equip_level;
		_price = price;
	}
	inline void setItemAttribute(int   hp,
								 int   maxHp,
								 int   mana,
								 int   maxMana,
								 float critical,
								 float offencePower,
								 float magicPower,
								 float speed,
								 float attackSpeed,
								 float damageBalace,
								 float experience,
								 float stamina)
	{
		_attribute._hp = hp;
		_attribute._maxHp =maxHp;
		_attribute._mana =mana;
		_attribute._maxMana =maxMana;
		_attribute._critical =critical;
		_attribute._offencePower =offencePower;
		_attribute._magicPower =magicPower;
		_attribute._speed =speed;
		_attribute._attackSpeed =attackSpeed;
		_attribute._damageBalance =damageBalace;
		_attribute._experience =experience;
		_attribute._stamina = stamina;
	}

	Item()
	{
		_type = EITEM_TYPE::EMPTY;
		_name = "EMPTY";
		_description = "EMPTY";
		_imgNum = 0;
		_equip_level = 0;
		_price = 0;
	}
	~Item() {}
};

class Player_Skill : public IRectObserved
{
public:
	my::Image* _img;
	RECT rc;
	string _name;
	float _damage;
	float _range;
	ObservedType _type;
	bool _isActive;
	
	void init(void);
	void release(void);
	virtual STObservedData getRectUpdate();
	virtual void collideObject();

};
