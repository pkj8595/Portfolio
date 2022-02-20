#pragma once
#include "Stdafx.h"

enum class ObservedType
{
	ROCKET = 0,
	ROCKET_MISSILE,
	MINION,
	MINION_MISSILE
};

typedef struct tagObservedInfo
{
	ObservedType* typeKey;
	RECT* rc;
	bool* isActive;	//적이 충졸했을때 

}STObservedData;

class IRectObserved 
{
public:
	virtual STObservedData getRectUpdate() = 0;
	virtual void collideObject() = 0;

	IRectObserved() {}
	virtual ~IRectObserved() {}
};

