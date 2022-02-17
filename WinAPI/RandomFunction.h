#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase<RandomFunction>
{
public:
	RandomFunction() 
	{
		//API 공용함수 : GetTickCount(따로 타이머사 구축이 안되어 있는 환경이면 무조건 서야하는 놈)
		//GetTickCount : OS가 부팅된 후의 경과 시간을 체크 
		//-기본적으로 밀리세턴 단위로 체크가 가능하며 밀리세컨 간위로 시간값을 반환 하기에 난수에 적절하다.
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init() { return S_OK; }

	inline int getInt(int num) 
	{
		return rand() % num;
	}
	//주의사항 0이 나오면 터진다.
	inline int getFromIntTo(int fromNum, int toNum) 
	{
		return rand() % (toNum - fromNum +1) +fromNum;
	}
	//1.00
	float getFloat(void) 
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}
	
	float getFromFloatTo(float fromNum, float toNum) 
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}



};

