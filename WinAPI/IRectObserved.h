#pragma once
#include "Stdafx.h"

enum class ObservedType
{
	ROCKET = 0,
	ROCKET_MISSILE,
	MINION,
	MINION_MISSILE,
	PLAYER_SWORD
};

typedef struct tagObservedInfo
{
	ObservedType* typeKey;
	RECT* rc;
	bool* isActive;	//적이 충돌했을때 
	float* damage;
	float* angle;
}STObservedData;

//순수 가상 클래스 -> 인터페이스
class IRectObserved 
{
public:
	virtual STObservedData getRectUpdate() = 0;
	virtual void collideObject(STObservedData obData) = 0;	//type 충돌된 상대 객체

	IRectObserved() {}
	virtual ~IRectObserved() {}
};

