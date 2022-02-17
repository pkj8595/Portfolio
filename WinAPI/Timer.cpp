#include "Stdafx.h"
#include "Timer.h"

HRESULT Timer::init(void)
{
	//QueryPerformanceFrequency():1초당 진동 수를체크하며
	//고성능타이머를 지원하면 ture,아니라면 false반환
	//LARGE_INTEGER 공용체
	//_periodFrequency : 값에 초당 파악 할 수 있는 시간이 들어간다.
	//밀리세컨까지 계산이 가능하다면 1000의 값이 그대로 들어간다.
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//OS에서 승인받으면 들어옴
		_isHardware = true;

		//QueryPerformanceCounter() : 특점 시점에서 몇번 진동했는가를 체크
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		//초당 시간을 계산할 수 있는 시간 주기
		_timeScale = 1.0f / _periodFrequency;
	}
	//고성능 타이머지원을 안한다면
	else
	{
		_isHardware = false;
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;

	return S_OK;
}

//lockFPS 수직동기화걸기
void Timer::tick(float lockFPS)
{
	if (_isHardware) 
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else 
	{
		_curTime = timeGetTime();
	}

	//마지막 시간과 현재 시간의 경과량 측정
	_timeElapsed = (_curTime - _lastTime)*_timeScale;

	if (lockFPS > 0.0f) {
		while (_timeElapsed < (1.0f / lockFPS)) 
		{
			if (_isHardware) 
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			}
			else 
			{
				_curTime = timeGetTime();
			}
			_timeElapsed = (_curTime - _lastTime)*_timeScale;
		}
	}

	//마지막 시간 기록
	_lastTime = _curTime;
	//초당 프레임 카운트 증가
	_FPSFrameCount++;
	//초당 프레임 시간 경과량 측정
	_FPSTimeElapsed += _timeElapsed;
	//전체 시간 경과량 측정
	_worldTime += _timeElapsed;

	//프레임 1초마다 초기화
	if (_FPSTimeElapsed > 1.0f) 
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}


}

//현재 FPS 
unsigned long Timer::getFrameRate(char* str) const
{
	if (str != nullptr) 
	{
		wsprintf(str, "FPS: %d", _frameRate);
	}
	return _frameRate;
}

