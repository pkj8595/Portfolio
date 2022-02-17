#include "Stdafx.h"
#include "HomeWork_0103_1.h"

HRESULT HomeWork_0103_1::init(void)
{

	for (int j = 0; j < 100; j++) 
	{
		_rc[j] = RectMakeCenter(0,0, 50, 50);
	}
	_player = RectMakeCenter(WINSIZE_X/2, WINSIZE_Y-40, 40, 90);
	_time =30;
	_rXPos = 0;
	_count =0;
	_timeCount = 0;
	_isGameStart = false;
	_isGameStop = false;

	_man.setState(IDLE);

	return S_OK;
}

void HomeWork_0103_1::release(void)
{
}

void HomeWork_0103_1::update(void)
{

	//게임시작
	if (!_isGameStart) 
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_isGameStart = true;
		}
		return;
	}
	else if (!_isGameStop) 
	{
		_man.setState(IDLE);
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_man.setState(L_MOVE);

			_player.left -= 3;
			_player.right -= 3;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_man.setState(R_MOVE);

			_player.left += 3;
			_player.right += 3;
		}

		_timeCount++;
		if (_timeCount % _time == 0)
		{
			_rXPos = RND->getFromIntTo(30, 770);
			_rc[_count].left = _rXPos - 25;
			_rc[_count].right = _rXPos + 25;
			if (_count < 100) { _count++; }

			_time = RND->getFromIntTo(60, 150);
		}

		//생성된 배열 내려가기
		for (int i = 0; i < _count; i++)
		{
			_rc[i].bottom += 3;
			_rc[i].top += 3;

			if (_rc[i].top > WINSIZE_Y)
			{
				_rc[i].bottom = 50;
				_rc[i].top = 0;
			}

			if (IntersectRect(&_temp, &_player, &_rc[i]))
			{
				_isGameStop = true;
			}
		}
	}
	else 
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) 
		{
			for (int i = 0; i < 100; i++)
			{
				_rc[i].bottom = 0;
				_rc[i].top = -50;
			}
			_timeCount = 0;
			_count = 0;
			_time = 30;
			_rXPos = 0;
			_player = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 40, 40, 90);
			_isGameStop = false;
			_isGameStart = false;
		}
	}

}

void HomeWork_0103_1::render(HDC hdc)
{
	if (!_isGameStart) 
	{
		_man.IdleMan(hdc,&_player);
		char strGameStart[128];
		wsprintf(strGameStart, "====GAME START====");
		TextOut(hdc, WINSIZE_X/2-60, WINSIZE_Y/2, strGameStart, strlen(strGameStart));
		return;
	}

	char strGameScore[128];
	wsprintf(strGameScore, "score : %d", _timeCount);
	TextOut(hdc, 10, 10, strGameScore, strlen(strGameScore));

	for (int i = 0; i < 100; i++)
	{
		Rectangle(hdc, _rc[i].left,
			_rc[i].top,
			_rc[i].right,
			_rc[i].bottom);
		
	}

	switch (_man.getState())
	{
	case IDLE:
		_man.IdleMan(hdc, &_player);
		break;
	case L_MOVE:
		_man.LeftMoveMan(hdc, &_player);
		break;
	case R_MOVE:
		_man.RightMoveMan(hdc, &_player);
		break;
	}

	//Rectangle(hdc, _player.left, _player.top, _player.right, _player.bottom);

	if (_isGameStop) 
	{
		char strGameOver[128];
		wsprintf(strGameOver, "====GAMGE OVER====");
		TextOut(hdc, WINSIZE_X / 2 - 60, WINSIZE_Y / 2, strGameOver, strlen(strGameOver));
		char strReplay[128];
		wsprintf(strReplay, "스페이스바를 누르면 재시작");
		TextOut(hdc, WINSIZE_X / 2 - 60, WINSIZE_Y / 2+20, strReplay, strlen(strReplay));
	}

}


