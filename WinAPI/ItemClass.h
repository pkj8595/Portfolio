#pragma once
#include "Stdafx.h"

enum class EITEM_TYPE
{
	EMPTY=0,
	POTION,
	SCROLL,
	ABILITY,
	EQUIP_WEAPON_BOW,
	EQUIP_WEAPON_SWORD,
	EQUIP_ARMOR,
	EQUIP_HAT,
	EQUIP_SHOES,
	MATERIAL,
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
	float _maxExperience;	//최대 경험치
	float _stamina;			//스테미나
	float _maxStamina;		//최대 스테미나

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

class EnchantItem
{
public:
	int			_index;
	string		_name;				//name
	int			_equip_level;		//장비 레벨
	int			_durability;		//내구도
	int			_maxDurability;		//최대내구도
	string		_enchantStr;		//인챈트

	CPlayer_Attribute _attribute;	//능력치

	void toString(void)
	{
		cout << "=============================================" << endl;
		cout << "_index			:" << _index << endl;
		cout << "_name			:" << _name << endl;
		cout << "_equip_level		:" << _equip_level << endl;
		cout << "_durability			:" << _durability << endl;
		cout << "_maxDurability			:" << _maxDurability << endl;
		cout << "hp			:" << _attribute._hp << endl;
		cout << "maxHp			:" << _attribute._maxHp << endl;
		cout << "mana			:" << _attribute._mana << endl;
		cout << "maxMana			:" << _attribute._maxMana << endl;
		cout << "critical		:" << _attribute._critical << endl;
		cout << "offencePower		:" << _attribute._offencePower << endl;
		cout << "magicPower		:" << _attribute._magicPower << endl;
		cout << "speed			:" << _attribute._speed << endl;
		cout << "attackSpeed		:" << _attribute._attackSpeed << endl;
		cout << "damageBalance		:" << _attribute._damageBalance << endl;
		cout << "experience		:" << _attribute._experience << endl;
		cout << "maxExperience		:" << _attribute._maxExperience << endl;
		cout << "stamina			:" << _attribute._stamina << endl;
		cout << "maxStamina		:" << _attribute._maxStamina << endl;
	}

	EnchantItem()
	{
		_index = 0;
		_name = "EMPTY";
		_equip_level = 0;
		_durability = 0;
		_maxDurability = 0;
		_enchantStr = "";
	}
	~EnchantItem() {}
};

class Item
{
public:
	int			_index;
	int			_imgNum;			//장비 이미지 넘버
	EITEM_TYPE	_type;				//아이템 타입
	string		_name;				//name
	string		_description;		//설명
	int			_equip_level;		//장비 레벨
	int			_price;				//가격
	int			_durability;		//내구도
	int			_maxDurability;		//최대내구도
	string		_enchantStr;		//인챈트

	CPlayer_Attribute _attribute;	//능력치

	void toString(void)
	{
		cout << "=============================================" << endl;
		cout << "_index			:" <<_index << endl;
		cout << "_type			:" <<(int)_type << endl;
		cout << "_name			:" <<_name << endl;
		cout << "_description		:" <<_description << endl;
		cout << "_imgNum			:" <<_imgNum << endl;
		cout << "_equip_level		:" <<_equip_level << endl;
		cout << "_price			:" << _price << endl;
		cout << "_durability			:" << _durability << endl;
		cout << "_maxDurability			:" << _maxDurability << endl;
		cout << "hp			:" << _attribute._hp << endl;
		cout << "maxHp			:" << _attribute._maxHp << endl;
		cout << "mana			:" << _attribute._mana << endl;
		cout << "maxMana			:" << _attribute._maxMana << endl;
		cout << "critical		:" << _attribute._critical << endl;
		cout << "offencePower		:" << _attribute._offencePower << endl;
		cout << "magicPower		:" << _attribute._magicPower << endl;
		cout << "speed			:" << _attribute._speed << endl;
		cout << "attackSpeed		:" << _attribute._attackSpeed << endl;
		cout << "damageBalance		:" << _attribute._damageBalance << endl;
		cout << "experience		:" << _attribute._experience << endl;
		cout << "maxExperience		:" << _attribute._maxExperience << endl;
		cout << "stamina			:" << _attribute._stamina << endl;
		cout << "maxStamina		:" << _attribute._maxStamina << endl;
	}

	void operator=(Item other)
	{
		_index= other._index;
		_imgNum=other._imgNum;
		_type = other._type;
		_name = other._name;
		_description = other._description;
		_equip_level = other._equip_level;
		_price = other._price;
		_durability = other._durability;
		_maxDurability = other._maxDurability;
		_enchantStr = other._enchantStr;
		_attribute = other._attribute;
	}

	bool getEnchantedItem(EnchantItem other)
	{
		if (_enchantStr != "") { return false; }
		_name = other._name + _name;
		_durability = other._durability + _durability;
		_maxDurability = other._maxDurability + _maxDurability;
		_enchantStr = other._enchantStr + _enchantStr;
		_attribute = other._attribute + _attribute;
		return true;
	}

	Item()
	{
		_index = 0;
		_type = EITEM_TYPE::EMPTY;
		_name = "EMPTY";
		_description = "EMPTY";
		_imgNum = 0;
		_equip_level = 0;
		_price = 0;
		_durability=0;
		_maxDurability=0;
		_enchantStr = "";
	}
	~Item() {}
};

