#pragma once
#include "MainGame.h"

/*
과제 1 슬라이드 퍼즐
-치트필수
-화면왼쪽에 원본 출력 <-->화면 오른쪽에는 9등분 된 이미지 출력
-9등분된 이미지 제일 아래 오른쪽 칸이 시작칸
-퍼즐이 완성되면 알파블랜딩 효과로 이미지가 나타난다.
-입력방식 마우스 키보드 둘다

*/
#define PUZZLE_START_X		430
#define PUZZLE_START_Y		200

class Homework_0113_1 : public MainGame
{
private:
	struct ST_SLICE
	{
		//mycustom::Image *sliceImg;
		int index;
		int num;
		RECT rc;
		bool isEndPz;
	};

	my::Image *_puzzleImg;
	ST_SLICE _rcPuzzle[3][3];


	my::Image *_GameStartImg;
	my::Image *_CheetImg;
	RECT _rcGameStart;
	RECT _rcCheet;

	bool _isGameStart;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);	//삼각함수는 update가 중요	
	virtual void render(HDC hdc);

	void RectShuffle(RECT* rc, int arrSize, int shuffleCount);

	Homework_0113_1() {}
	~Homework_0113_1() {}
};

