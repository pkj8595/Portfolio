#include "Stdafx.h"
#include "GameClass_0103.h"

HRESULT GameClass_0103::init()
{
	_currentRect = CURRENTRECT_NULL;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_rc[i * 4 + j] = RectMakeCenter(100 + j * 200,
				200 + i * 200,
				100,
				100
			);
		}
	}

	_index = 0;
	_count = 0;
	_score = 0;
	_time = RND->getFromFloatTo(30, 60);

	_isSelected = false;
	_isOnceCheck = false;

	return S_OK;
}

void GameClass_0103::release()
{
}

void GameClass_0103::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//PrInRect() : 렉트안에 POINT (x, y)가 있는지 검사하여 포인트가 
		//			   사각형 안에 있으면 true를 반환하는 API 함수
		//사각형이랑 마우스가 충돌 됐는지 
		if (PtInRect(&_rc[_index], _ptMouse) &&
			!_isOnceCheck)
		{
			_score += 100;
			_isOnceCheck = true;
		}
	}
	if (!_isSelected)
	{
		_count++;
		if (_count % _time == 0)
		{
			_count = 0;
			_index = RND->getInt(8);
			_currentRect = (CURRENTRECT)_index;
			_isSelected = true;
		}
	}
	else
	{
		_count++;
		if (_count % _time == 0)
		{
			_isOnceCheck = false;
			_isSelected = false;
			_currentRect = CURRENTRECT_NULL;
			_time = RND->getFromIntTo(30, 60);
			_index = 100;
		}

	}
}

void GameClass_0103::render(HDC hdc)
{
	for (int i = 0; i < 8; i++)
	{
		Rectangle(hdc, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}
	char strScore[128];
	wsprintf(strScore, "Score : %d", _score);
	TextOut(hdc, 50, 100, strScore, strlen(strScore));

	if (_isSelected)
	{
		int r = RND->getInt(256);
		int g = RND->getInt(256);
		int b = RND->getInt(256);

		//브러쉬 RGB 설정
		HBRUSH brush = CreateSolidBrush(RGB(r, g, b));

		//렉트에 색 채워주기
		FillRect(hdc, &_rc[_index], brush);

		//브러쉬 제거(브러쉬를 썻으면 반드시 지워줘야한다.)
		DeleteObject(brush);
	}
}

