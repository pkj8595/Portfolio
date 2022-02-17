#include "Stdafx.h"
#include "Homework0118.h"

HRESULT Homework0118::init(void)
{
	MainGame::init();
	IMAGEMANAGER->addImage("배경", "Resource/Images/1942/1942map.bmp", 1000, 2048*2);
	IMAGEMANAGER->addImage("P_IDLE", "Resource/Images/1942/idle1942.bmp", 33*3, 23*3,TRUE,RGB(255,0,255));
	IMAGEMANAGER->addFrameImage("P_MOVE", "Resource/Images/1942/move1942.bmp", 132*3, 46*3,4,2 ,TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("P_DEAD", "Resource/Images/1942/1942dead.bmp", 240, 72,6,2, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("E_IDLE", "Resource/Images/1942/1942EnemyIdle.bmp", 17*3, 18*3, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PANEL1", "Resource/Images/1942/panel1.bmp", 200, 155, TRUE, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PANEL2", "Resource/Images/1942/panel2.bmp", 200, 155, TRUE, RGB(255, 0, 255));

	_angle = PI;
	_bgSpeed = 0;
	_pSpeed = 0;

	_rcPlayer = RectMakeCenter(WINSIZE_X / 2, 600, 75, 55);

	for (int i = 0; i < ENEMY_COUNT; i++) 
	{
		_enemy[i].rc = RectMake(800,0,15,15);
		_enemy[i].isActive = false;
		_enemy[i].speed = 4;
	}
	_pState = STATE_idle;
	_isLeft = false;
	_index = -1;

	return S_OK;
}

void Homework0118::release(void)
{
	MainGame::release();

}

void Homework0118::update(void)
{
	MainGame::update();
	//_isA = !_isA;

	if (_pState == STATE_dead) 
	{
		
	}
	else 
	{
		_pState = STATE_idle;

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_pState = STATE_left;
			_rcPlayer.left -= 3;
			_rcPlayer.right -= 3;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_pState = STATE_right;
			_rcPlayer.left += 3;
			_rcPlayer.right += 3;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_pSpeed < 300)
			{
				_pSpeed += 0.3;
				_angle += 0.03f;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_pSpeed > 0 && _pSpeed < 300)
			{
				_pSpeed -= 0.3;
				_angle -= 0.03f;
			}
			else
			{
				_pSpeed = 0;
			}
		}
	}
	_ptPannel.x = cosf(_angle) * 100 + 900;
	_ptPannel.y = sinf(_angle) * 100 + (WINSIZE_Y-100);


	if(GetTickCount() % 50 ==0)
	{
		if (_pState == STATE_dead) 
		{
			macroPlayFrameAnimation(IMAGEMANAGER->findImage("P_DEAD"), 0, _index);
		}
		else if(_pState == STATE_left )
		{
			_isLeft = false;
			macroPlayFrameAnimation(IMAGEMANAGER->findImage("P_MOVE"), _isLeft, _index);
		}
		else if (_pState == STATE_right) 
		{
			_isLeft = true;
			macroPlayFrameAnimation(IMAGEMANAGER->findImage("P_MOVE"), _isLeft, _index);
		}
		
		_sponTime++;
		if(_sponTime %2 ==0)
		{
			for (int i = 0; i < ENEMY_COUNT; i++)
			{
				if (_enemy[i].isActive) continue;

				_enemy[i].isActive = true;
				_enemy[i].rc.left = (RND->getInt(5)) * 80 + 320;
				_enemy[i].rc.top = -50;
				_enemy[i].rc.right = _enemy[i].rc.left + 50;
				_enemy[i].rc.bottom = _enemy[i].rc.top + 50;
				_enemy[i].speed = RND->getFromIntTo(1, 3);
				break;
			}
		}
		
	}
	_bgSpeed -= 2 + _pSpeed;


	for (int i = 0; i < ENEMY_COUNT; i++) 
	{
		if(_enemy[i].isActive)
		{
			if (RectCollider(_rcPlayer, _enemy[i].rc)) 
			{
				_pState = STATE_dead;
			}

			cout << "====================" << endl;
			cout<<"top		:"<< _enemy[i].rc.top <<endl;
			cout<<"bottom	:"<< _enemy[i].rc.bottom <<endl;
			_enemy[i].rc.top += _enemy[i].speed + _pSpeed;
			_enemy[i].rc.bottom += _enemy[i].speed+ _pSpeed;

			if (_enemy[i].rc.top > WINSIZE_Y) 
			{
				_enemy[i].isActive = false;
			}
		}
	}

	


}

void Homework0118::render(HDC hdc)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	IMAGEMANAGER->loopRender("배경", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), 0, _bgSpeed);

	switch (_pState)
	{
	case Homework0118::STATE_idle:
		IMAGEMANAGER->render("P_IDLE", getMemDC(),_rcPlayer.left-12,_rcPlayer.top-10);

		break;
	case Homework0118::STATE_left:
		IMAGEMANAGER->frameRender("P_MOVE", getMemDC(),_rcPlayer.left,_rcPlayer.top);

		break;
	case Homework0118::STATE_right:
		IMAGEMANAGER->frameRender("P_MOVE", getMemDC(), _rcPlayer.left, _rcPlayer.top);

		break;
	case Homework0118::STATE_dead:
		IMAGEMANAGER->frameRender("P_DEAD", getMemDC(), _rcPlayer.left, _rcPlayer.top);

		break;
	default:
		break;
	}

	IMAGEMANAGER->render("PANEL1", getMemDC(), 800, WINSIZE_Y - 200);
	IMAGEMANAGER->render("PANEL2", getMemDC(), 800, WINSIZE_Y - 200);

	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN currentPen;
	currentPen = (HPEN)SelectObject(getMemDC(), pen);
	LineMake(getMemDC(), 900, WINSIZE_Y - 100, _ptPannel.x, _ptPannel.y);
	DeleteObject(pen);
	


	for (int i = 0; i < ENEMY_COUNT; i++) 
	{
		if(_enemy[i].isActive)
		{
			IMAGEMANAGER->render("E_IDLE", getMemDC(), _enemy[i].rc.left, _enemy[i].rc.top);
		}
	}
		
	if (KEYMANAGER->isToggleKey(VK_F1)) 
	{
		RectangleMakeToRECT(getMemDC(), _rcPlayer);
		for (int i = 0; i < ENEMY_COUNT; i++)
		{
			if(_enemy[i].isActive)
			RectangleMakeToRECT(getMemDC(),_enemy[i].rc);
		}
	}

	this->getBackBuffer()->render(getHDC());
}

void Homework0118::macroPlayFrameAnimation(my::Image * image, bool isleft, int & index)
{
	if (!isleft)
	{
		image->setFrameY(1);
		index--;
		if (index < 0)
		{
			index = image->getMaxFrameX();
		}

		image->setFrameX(index);
	}
	else
	{
		image->setFrameY(0);
		index++;
		if (index > image->getMaxFrameX())
		{
			index = 0;
		}

		image->setFrameX(index);
	}
}

bool Homework0118::macroPlayOnceFrameAnimation(my::Image * image, bool isleft, int & index, bool & isAnimating)
{
	if (isAnimating)
	{
		if (!isleft)
		{
			image->setFrameY(1);
			index--;
			if (index < 0 || index >image->getMaxFrameX())
			{
				index = image->getMaxFrameX();
			}

			image->setFrameX(index);
			if (index == 0) isAnimating = false;
		}
		else
		{
			image->setFrameY(0);
			index++;
			if (index > image->getMaxFrameX() || index < 0)
			{
				index = 0;
			}

			image->setFrameX(index);
			if (index == image->getMaxFrameX()) isAnimating = false;
		}
	}

	return false;
}
