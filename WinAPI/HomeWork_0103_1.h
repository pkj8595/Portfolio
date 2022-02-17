#pragma once
#include "MainGame.h"
#include "StickMan.h"




class HomeWork_0103_1 : public Scene_inter
{
private:
	StickMan _man;
	RECT _rc[100];
	RECT _player;
	RECT _temp;

	int _rXPos;
	int _time;
	int	_timeCount;
	int _count;

	bool _isGameStart;
	bool _isGameStop;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	HomeWork_0103_1() {}
	~HomeWork_0103_1() {}
	
};

/*
실습 겸 과제1. 똥피하기
- 시작 버튼을 누르면서 게임이 시작된다.
-게임이 시작되고 플레이어가 죽을때까지 버틴 시간을 화면에 출력
-필수기능 : 재시작 + 다시하기

과제 2 : 총알 발사

-하단에서 좌우로 움직일 수 있는 플레이어
-스페이스 바를 누르면 플레이어가 총알을 발사한다.(B->T)

과제 3. 악어 이빨
-악어 이빨은 최소 12개 이상
-악어 이빨에 물렸을 때 입을 받아야 한다.

*/