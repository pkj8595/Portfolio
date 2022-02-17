#pragma once


/*
	생성자 생성 
	Render와 update에 함수 삽입
*/
class HPprogressBar
{
private:
	float _nHp;

	RECT _rectMaxHp;
	RECT _rectHp;
	float _nMaxHp;
	float temp;
public:
	HPprogressBar() {}
	HPprogressBar(int hp);
	//프로그래스바 랜더
	void RenderHpbar(HDC hdc);

	//프로그래스바 정보갱신 위치,체력
	void UpdateHpBar(RECT * tager, int nHp);

};

