#include "Stdafx.h"
#include "CShapePlayer.h"

CShapePlayer::CShapePlayer() :_isMove(false), _maxHp(6), _hp(6), _speed(6), _pt(PointMake(WINSIZE_X/3, WINSIZE_Y / 2)), _angle(0), _rc(RectF(-10, -10, 20, 20)), _dashRc(RectF(0, 0, 0, 0)), _isDash(false), _beAttackedTime(0), _isBeAttacked(false),_imgKey("")
{
	IMAGEMANAGER->initForGPbitmap("p1", L"Resource/Images/Popol/p1.png", 1);
	IMAGEMANAGER->initForGPbitmap("p2", L"Resource/Images/Popol/p2.png", 1);
	IMAGEMANAGER->initForGPbitmap("p3", L"Resource/Images/Popol/p3.png", 1);
	IMAGEMANAGER->initForGPbitmap("p4", L"Resource/Images/Popol/p4.png", 1);
	IMAGEMANAGER->initForGPbitmap("p5", L"Resource/Images/Popol/p5.png", 1);
}

void CShapePlayer::update(int time)
{
	_isMove = false;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_pt.x - 10 < 0) return;
		_pt.x -= 1;
		_isMove = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_pt.x + 10 > WINSIZE_X) return;
		_pt.x += 1;
		_isMove = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (_pt.y - 10 < 0) return;
		_pt.y -= 1;
		_isMove = true;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_pt.y + 10 > WINSIZE_Y) return;
		_pt.y += 1;
		_isMove = true;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		
		for (int i = 0; i < DASHELL_SIZE; i++)
		{
			if (!_dashEll[i].isActive) 
			{
				_dashEll[i].isActive = true;
				_dashEll[i].penWidth = 30;
				_dashEll[i].radius = 20;
				_dashEll[i].alpha = 255;
				_dashEll[i].color = Color(_dashEll[i].alpha, 255, 255, 255);
				_dashEll[i].pt.X = _pt.x;
				_dashEll[i].pt.Y = _pt.y;

				_dashTime = time;
				_speed = 25;
				_dashRc = RectF(-15, -10, 30, 20);
				_isDash = true;
				break;
			}
		}
	}

	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		_hp++;
	}

	//direction
	_angle = atan2f(_pt.y - _previousPt.y, _pt.x - _previousPt.x);

	if (_isBeAttacked)
	{
		if (!_isMove) 
		{
			_pt.x -= 30;
			_pt.y -= 30;
		}
		else 
		{
			_pt.x += cosf(_angle + PI) * 40;
			_pt.y += sinf(_angle + PI) * 40;
		}

		if (time > _beAttackedTime + 150) 
		{
			_isBeAttacked = false;
		}
	}


	if (_isMove)
	{
		_pt.x += cosf(_angle)* _speed;
		_pt.y += sinf(_angle)* _speed;
		_rc = RectF(-12.5f, -7.5f, 25, 15);

		if (time % 3 == 0)
		{
			for (int i = 0; i < PARTCLE_SIZE; i++)
			{
				if (!_partcle[i].isActive)
				{
					INT y = _pt.y-10 + RND->getInt(20);
					INT x = _pt.x-10 + RND->getInt(20);
					_partcle[i].isActive = true;
					_partcle[i].alpha = 255;
					_partcle[i].rc = Rect(x, y, 8, 8);
					break;
				}
			}
		}
	}
	else 
	{
		_rc = RectF(-10, -10, 20, 20);
	}

	//dash
	if (_dashTime + 200 < time)
	{
		_isDash = false;
		_dashRc = RectF(0, 0, 0, 0);
		_speed = 8;
	}

	//player rotate
	_mPlayer.SetElements(cosf(_angle + PI), sinf(_angle + PI), -sinf(_angle + PI), cosf(_angle + PI), (_pt.x), (_pt.y));

	//particle alpha
	for (int i = 0; i < PARTCLE_SIZE; i++)
	{
		if (_partcle[i].isActive) 
		{
			if (ChangeAlpha(_partcle[i].alpha, -6) < 0) 
			{
				_partcle[i].isActive = false;
			}
		}
	}

	//dash alpha
	for (int i = 0; i < DASHELL_SIZE; i++)
	{
		if (_dashEll[i].isActive) 
		{
			if (ChangeAlpha(_dashEll[i].alpha, -8) < 0)
			{
				_dashEll[i].isActive = false;
				continue;
			}
			INT x = _dashEll[i].pt.X + (_dashEll[i].radius*-1);
			INT y = _dashEll[i].pt.Y + (_dashEll[i].radius*-1);
			INT w = _dashEll[i].radius * 2;
			INT h = _dashEll[i].radius * 2;
			_dashEll[i].color = Color(_dashEll[i].alpha, 220, 255, 255);
			_dashEll[i].radius += 3;
			_dashEll[i].penWidth -=2;
			_dashEll[i].dashEll = Rect(x,y,w,h);
		}
		
	}

	_previousPt = _pt;

}

void CShapePlayer::render(Gdiplus::Graphics *g)
{
	g->SetTransform(&_mPlayer);
	g->DrawRectangle(&Pen(Color(80, 80, 80)), _rc);

	if (_isDash && _isMove) g->FillRectangle(&SolidBrush(Color(255, 255, 255)), _dashRc);

	switch (_hp)
	{
	case 0:
		_imgKey = "";
		break;
	case 1:
		_imgKey = "p1";
		break;
	case 2:
		_imgKey = "p2";
		break;
	case 3:
		_imgKey = "p3";
		break;
	case 4:
		_imgKey = "p4";
		break;
	case 5:
		_imgKey = "p5";
		break;
	case 6:
		_imgKey = "";
		g->FillRectangle(&SolidBrush(Color(0, 255, 255)), _rc);
		break;
	default:
		break;
	}

	if(_imgKey != "")
	{
		if (_isMove) IMAGEMANAGER->renderForGPbitmap(_imgKey,g, -12.5f, -7.5f, 25, 15);
		else IMAGEMANAGER->renderForGPbitmap(_imgKey, g, -10,-10,20,20);
	}

	if (_isBeAttacked) g->FillRectangle(&SolidBrush(Color(255, 255, 255)),GPRectFMakeCenter(30,30));


	g->SetTransform(&Gdiplus::Matrix(1, 0, 0, 1, 0, 0));
	//move effect
	for (int i = 0; i < PARTCLE_SIZE; i++)
	{
		if(_partcle[i].isActive) g->FillRectangle(&SolidBrush(Color(_partcle[i].alpha,0, 140, 255)), _partcle[i].rc);
	}

	//dash effect
	if (_isDash) 
	{
		for (int i = 0; i < DASHELL_SIZE; i++)
		{
			if (_dashEll[i].isActive)
			{
				g->DrawEllipse(&Pen(_dashEll[i].color, _dashEll[i].penWidth), _dashEll[i].dashEll);
			}
		}
	}

	g->SetTransform(&Gdiplus::Matrix(1,0,0,1,-400,-400));
}



void CShapePlayer::beAttacked(long time)
{
	if (!_isDash && time > _beAttackedTime+200)
	{
		_hp--;
		_beAttackedTime = time;
		_isBeAttacked = true;
	}
}