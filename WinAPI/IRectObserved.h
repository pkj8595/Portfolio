#pragma once
#include "Stdafx.h"


//=====================================
//	## ObjectObserved ##
//=====================================
enum class ObservedType
{
	ROCKET = 0,
	ROCKET_MISSILE,
	MINION,
	MINION_MISSILE,
	PLAYER_SWORD,
	ITEM
};

typedef struct tagObservedInfo
{
	ObservedType* typeKey;
	RECT* rc;
	bool* isActive;	//���� �浹������ 
	float* damage;
	float* angle;
	int* number;
	bool* magic;

	tagObservedInfo()
	{
		typeKey = nullptr;
		rc = nullptr;
		isActive = nullptr;
		damage = nullptr;
		angle = nullptr;
		number = nullptr;
		magic = nullptr;
	}
}STObservedData;

//���� ���� Ŭ���� -> �������̽�
class IRectObserved 
{
public:
	virtual STObservedData getRectUpdate() = 0;
	virtual void collideObject(STObservedData obData) = 0;	//type �浹�� ��� ��ü

	IRectObserved() {}
	virtual ~IRectObserved() {}
};

//=====================================
//	## EventObserved ##
//=====================================

enum class EventObservedType
{
	SHOP =0,
	CHEST,
	ANVIL
};

typedef struct tagEventObservedInfo
{
	EventObservedType* typeKey;
	RECT* rc;
	bool* isActive;	
	int* num;

	tagEventObservedInfo()
	{
		typeKey = nullptr;
		rc = nullptr;
		isActive = nullptr;
		num = nullptr;
	}
}STEventObservedData;

class IEventObservered
{
public:
	virtual STEventObservedData getEventUpdate() = 0;
	virtual void collideEventObject(STEventObservedData obEventData) = 0;

	IEventObservered() {}
	~IEventObservered() {}
};

