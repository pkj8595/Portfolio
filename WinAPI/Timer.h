#pragma once
/*
- 기존에 사용한 API 공용함수 >> 개쓰레기 버그 있음.
저해상도 타이머
GetTickCount();		>> 32bit >> 주기 1/1000
GetTickCount64();	>> 64bit 각잡고 

타이머를 나눌때 좋은 타이머인지 확인하는법은 저해상도이냐 고해상도이냐

해상도에 따라 진동폭이 다름 

*/

/*
고해상도 주기 = 1/9000000 
Timer  
-시간을 측정하는 함수들은 굉장히 많고 기본적으로 윈도우가 시작된 이후 Milli Second단위로 반환

-보통 타이머를 구현할때 알아둬야 할 개념은 #해상도#와 #클럭#
클럭과 해상도를 기억해야한다.

해상도 ? 
- 다양한 시간 함수들은 시간을 측정하기 위한 Tick 계산로직이 있다. 
	ㄴ 1분을 기준으로 얼마나 많은 프레임으로 나눌 수 있는지를 뜻한다.
-1분동안 얼마나 많은 Tick으로 나눠서 시간의 정확도를 높이느냐에 따라서 고해상도와 저해상도로 나뉜다.

Clock(진동수)
-타이머에서 얘기하는 클럭은 CPU 클럭(Clock)을 의미한다.
-클럭 자체는 디지털 회로의 전기적 진동 수 이며 Hz로 표기
ㄴ 1Hz : 1초라는 가정하에 신호(0 or 1)를 1번 준다.
	ㄴ 1비트를 한번 옮긴다는 의미 

- 1GHz = 10^9  제곱 -> 10억
- 3.00GHz -> 30억번
	ㄴ 1초에 30억개의 bit를 옮길 수 있다.
	ㄴ다쓰진 못한다. 다른 프로그램들이 있기 때문에

## 고성능 타이머의 경우 성능 향상시키기 위해서는 중첩이 필요하다.
	ㄴ대략 9백만분의 1초까지 측정
	
-기본적으로 셋팅하고 사용할 시 백만분의 1초까지 측정가능

923경...중첩의 중첩을해서 cpu의 연산을 메모리에 할당?

## 함수의 클럭수가 너무 높으면 OS가 실행시키지 않는다.

*/

class Timer
{
private:
	float _timeScale;		//경과시간
	float _timeElapsed;		//마지막 시간과 현재시간의 경과값
	bool _isHardware;		//고성능 타이머 지원 여부

	//INT64_MAX
	//32bit에서 사용할때 4바이트 
	//64bit에서 사용할때 8바이트
	__int64 _curTime;			//현재 시간
	__int64 _lastTime;			//이전 시간
	__int64 _periodFrequency;	//시간주기

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init(void);
	//현재 시간을 계산
	void tick(float lockFPS = 0.0f);	//강제로 60으로 잠군다.
	
	//현재 FPS
	unsigned long getFrameRate(char* str = nullptr) const;
	//마지막 시간과 현재 시간의 경과량 FPS산출
	inline float getElapsedTime(void) const { return _timeElapsed; }
	//전체 경과 시간
	inline float getWorldTime(void) const { return _worldTime; }

	Timer() {}
	~Timer() {}
};

