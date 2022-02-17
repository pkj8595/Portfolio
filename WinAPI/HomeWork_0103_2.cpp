#include "Stdafx.h"
#include "HomeWork_0103_2.h"

HRESULT HomeWork_0103_2::init(void)
{

	for (int i = 0; i < 30; i++) 
	{
		_bullet[i].bullet = RectMakeCenter(0, 0, 20, 20);
		_bullet[i].isActive = false;
	}

	_player = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 40, 40, 90);
	_bulletPoint = PointMake((_player.left + _player.right)*0.5, _player.top);

	return S_OK;
}

void HomeWork_0103_2::release(void)
{
	
}

void HomeWork_0103_2::update(void)
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

	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) 
	{
		_bulletPoint = PointMake((_player.left + _player.right)*0.5, _player.top);
		for (int i = 0; i < 30; i++) 
		{
			if (!_bullet[i].isActive) 
			{
				_bullet[i].isActive = true;
				_bullet[i].bullet = RectMakeCenter(_bulletPoint.x, _bulletPoint.y,10,10);
				break;
			}
		}
	}

	for (int i = 0; i < 30; i++)
	{
		if (_bullet[i].isActive)
		{
			_bullet[i].bullet.top -= 5;
			_bullet[i].bullet.bottom -= 5;
			
			if (_bullet[i].bullet.bottom < 0) 
			{
				_bullet[i].bullet = RectMakeCenter(0, 0, 10, 10);
				_bullet[i].isActive = false;
			}
		}
	}

}

void HomeWork_0103_2::render(HDC hdc)
{

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

	for (int i = 0; i < 30; i++)
	{
		Rectangle(hdc, _bullet[i].bullet.left,
			_bullet[i].bullet.top,
			_bullet[i].bullet.right,
			_bullet[i].bullet.bottom);
	}
}
