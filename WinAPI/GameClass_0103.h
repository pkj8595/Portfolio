#pragma once
#include "MainGame.h"

enum CURRENTRECT {
	CURRENTRECT_0,
	CURRENTRECT_1,
	CURRENTRECT_2,
	CURRENTRECT_3,
	CURRENTRECT_4,
	CURRENTRECT_5,
	CURRENTRECT_6,
	CURRENTRECT_7,
	CURRENTRECT_NULL
};

class GameClass_0103 : public Scene_inter
{
private:
	int typeSize;


	CURRENTRECT _currentRect;
	RECT _rc[8];					//두더지 사각형 8개 

	int _index;					//두더지가 나올 인덱스용 변수
	int _count;					//타이머용 카운트
	int _time;					//타이머용 랜덤시간
	int _score;					//점수

	bool _isSelected;
	bool _isOnceCheck;
	//중복체크 방지
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

