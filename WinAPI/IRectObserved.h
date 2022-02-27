#pragma once
#include "Stdafx.h"

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

	tagObservedInfo()
	{
		typeKey = nullptr;
		rc = nullptr;
		isActive = nullptr;
		damage = nullptr;
		angle = nullptr;
		number = nullptr;
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

