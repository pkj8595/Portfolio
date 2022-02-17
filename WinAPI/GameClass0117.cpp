#include "Stdafx.h"
#include "GameClass0117.h"

HRESULT GameClass0117::init(void)
{
	MainGame::init();

	IMAGEMANAGER->addImage("데드스페이스", "Resource/Images/Background/background4.bmp", WINSIZE_X, WINSIZE_Y);

	_rcPlayer.rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 450, 50, 50);

	_floor = WINSIZE_Y;
	_alphaA = 0;
	_alphaNum = 1;

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_wall = RECT{500,500,600,WINSIZE_Y};
	_platform = RectMakeCenter(300,400,100,30);
	return S_OK;
}

void GameClass0117::release(void)
{
	MainGame::release();

}

void GameClass0117::update(void)
{
	MainGame::update();

	_bgSpeed += 4;

	/*_alphaA += _alphaNum;
	if (_alphaA <= 0 || _alphaA >= 255) _alphaNum = _alphaNum * -1;*/

	//if (KEYMANAGER->isToggleKey(VK_F4)) 
	//{
	//	//cout << boolalpha;	
	//	//system("pause");		
	//}

	if(KEYMANAGER->isOnceKeyDown(VK_SPACE) && _rcPlayer.isGround)
	{
		cout<<"==================jump==================" << endl;
		jumpStart();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//항상 풀로 true
		if (_rcPlayer.rc.left <= 0);
		else 
		{
			_rcPlayer.rc.left -= 8;
			_rcPlayer.rc.right -= 8;
			_rcPlayer.isLeft = true;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_rcPlayer.rc.right >= WINSIZE_X);
		else
		{
			_rcPlayer.rc.left += 8;
			_rcPlayer.rc.right += 8;
			_rcPlayer.isLeft = false;
		}
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (!_rcPlayer.isSpider);
		else
		{
			_rcPlayer.rc.top -= 8;
			_rcPlayer.rc.bottom -= 8;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_rcPlayer.rc.bottom >= WINSIZE_Y);
		else
		{
			_rcPlayer.rc.top += 8;
			_rcPlayer.rc.bottom += 8;
		}
	}

	
	//cout <<"Player : "<< _rcPlayer.rc.left << ", "<<_rcPlayer.rc.top << ", "<<_rcPlayer.rc.right << ", "<<_rcPlayer.rc.bottom << ", " << endl;

	playerMove();

}

void GameClass0117::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	//IMAGEMANAGER->alphaRender("데드스페이스", getMemDC(), ChangeAlpha(_alphaA,_alphaNum));

	IMAGEMANAGER->loopRender("데드스페이스", getMemDC(), &RectMake(0,0,WINSIZE_X,WINSIZE_Y),_bgSpeed,0);


	Rectangle(getMemDC(), _rcPlayer.rc.left, _rcPlayer.rc.top, _rcPlayer.rc.right, _rcPlayer.rc.bottom);

	RectangleMakeToRECT(getMemDC(), _wall);
	RectangleMakeToRECT(getMemDC(), _platform);

	if (RectCollider(_rcPlayer.rc, _wall))
	{
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
		FillRect(hdc, &_rcPlayer.rc, brush);
		DeleteObject(brush);

	}

	this->getBackBuffer()->render(getHDC());
}

/*
isJump;
isLeft;
isSpider;


점프 뛴 상태에서 방향키를 누르고 있으면 천천히 내려옴 
방향키를 누르고있지 않으면 떨어짐 
*/

void GameClass0117::playerMove()
{

	if (_rcPlayer.rc.bottom >= _floor)
	{
		_rcPlayer.isGround = true;
		_rcPlayer.rc.bottom = _floor;
		_rcPlayer.rc.top = _floor-50;

		//지면에서 벽에 붙이칠때
		if (RectCollider(_rcPlayer.rc, _wall))
		{
			if (!_rcPlayer.isLeft)
			{
				_rcPlayer.rc.left = _wall.left - 50;
				_rcPlayer.rc.right = _wall.left;
			}
			else if(_rcPlayer.isLeft)
			{
				_rcPlayer.rc.left = _wall.right;
				_rcPlayer.rc.right = _wall.right + 50;
			}
		}
	}

	//공중에 있는지 판별
	if ((RectCollider(_rcPlayer.rc, _wall) || RectCollider(_rcPlayer.rc, _platform) || _rcPlayer.rc.bottom >= _floor) )
	{
		_rcPlayer.isGround = true;
	}
	else 
	{
		_rcPlayer.isGround = false;
	}


	//점프시 
	if (!_rcPlayer.isGround && !_rcPlayer.isPlatform)
	{
		_rcPlayer.rc.bottom -= _rcPlayer.speed + _rcPlayer.gravity;
		_rcPlayer.rc.top -= _rcPlayer.speed + _rcPlayer.gravity;
		_rcPlayer.gravity -= 0.3f;
	}

	//벽에 붙었을때
	if (RectCollider(_rcPlayer.rc, _wall) &&
		_rcPlayer.rc.bottom > _wall.top)
	{
		_rcPlayer.isPlatform = true;
		_rcPlayer.isSpider = true;

		if (_rcPlayer.rc.top < _wall.top &&
			_rcPlayer.rc.left < _wall.right &&
			_rcPlayer.rc.right > _wall.left &&
			_rcPlayer.rc.bottom >= _wall.top)
		{
			_rcPlayer.rc.bottom = _wall.top;
			_rcPlayer.rc.top = _wall.top - 50;
			_rcPlayer.isSpider = false;
		}
		else 
		{
			if (!_rcPlayer.isLeft)
			{
				_rcPlayer.rc.left = _wall.left - 50;
				_rcPlayer.rc.right = _wall.left;
			}
			else if (_rcPlayer.isLeft)
			{
				_rcPlayer.rc.left = _wall.right;
				_rcPlayer.rc.right = _wall.right + 50;
			}

			if (_rcPlayer.rc.top != _wall.top)
			{
				_rcPlayer.rc.bottom += 1;
				_rcPlayer.rc.top += 1;
			}
		}
		
	}
	//_platform
	else if (RectCollider(_rcPlayer.rc, _platform) &&
		_rcPlayer.rc.bottom > _platform.top)
	{
		_rcPlayer.isPlatform = true;
		_rcPlayer.isSpider = true;

		if (_rcPlayer.rc.top < _platform.top &&
			_rcPlayer.rc.left < _platform.right &&
			_rcPlayer.rc.right > _platform.left &&
			_rcPlayer.rc.bottom >= _platform.top)
		{
			_rcPlayer.rc.bottom = _platform.top;
			_rcPlayer.rc.top = _platform.top - 50;
			_rcPlayer.isSpider = false;
		}
		else
		{
			if (!_rcPlayer.isLeft)
			{
				_rcPlayer.rc.left = _platform.left - 50;
				_rcPlayer.rc.right = _platform.left;
			}
			else if (_rcPlayer.isLeft)
			{
				_rcPlayer.rc.left = _platform.right;
				_rcPlayer.rc.right = _platform.right + 50;
			}

			if (_rcPlayer.rc.top != _platform.top)
			{
				_rcPlayer.rc.bottom += 1;
				_rcPlayer.rc.top += 1;
			}
		}

	}
	else 
	{
		_rcPlayer.isPlatform = false;
		_rcPlayer.isSpider = false;
	}

}

void GameClass0117::jumpStart()
{
	_rcPlayer.isGround = false;
	_rcPlayer.rc.top -= 1;
	_rcPlayer.rc.bottom -= 1;
	_rcPlayer.speed = 9.5f;
	_rcPlayer.gravity = 0.0f;
}

