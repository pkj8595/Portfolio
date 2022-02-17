#include "Stdafx.h"
#include "Homework_0114_frameImg.h"

HRESULT Homework_0114_frameImg::init(void)
{
	MainGame::init();


	_background = new my::Image;
	_background->init("Resource/Images/Background/backgroundVS.bmp", 1400, 600);

	_playerIdle = new my::Image;
	_playerIdle->init("Resource/Images/Frame/idle.bmp", 0, 0, 3834, 852, 9, 2, true, RGB(255, 0, 255));

	_playerMove = new my::Image;
	_playerMove->init("Resource/Images/Frame/walking2_magenta.bmp", 0, 0, 4686, 852, 11, 2, true, RGB(255, 0, 255));

	_playerAttack = new my::Image;
	_playerAttack->init("Resource/Images/Frame/stab.bmp", 0, 0, 7020, 814, 9, 2, true, RGB(255, 0, 255));

	_playerMAttack = new my::Image;
	_playerMAttack->init("Resource/Images/Frame/Mstabs.bmp", 0, 0, 9152, 800, 11, 2, true, RGB(255, 0, 255));

	_playerCicleAttack = new my::Image;
	_playerCicleAttack->init("Resource/Images/Frame/cicleMotionList.bmp", 0, 0, 5814, 1276, 9, 2, true, RGB(255, 0, 255));

	_playerVictory = new my::Image;
	_playerVictory->init("Resource/Images/Frame/vMotionList.bmp", 0, 0, 14444, 886, 23, 2, true, RGB(255, 0, 255));


	_rcPlayer = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 300, 400);

	_state = STATE_IDLE;

	_count = 0;
	_index = 0;

	return S_OK;
}

void Homework_0114_frameImg::release(void)
{
	MainGame::release();
	SAFE_DELETE(_playerIdle);
	SAFE_DELETE(_playerMove);
	SAFE_DELETE(_playerAttack);
	SAFE_DELETE(_playerMAttack);
	SAFE_DELETE(_playerCicleAttack);
	SAFE_DELETE(_playerVictory);
	SAFE_DELETE(_background);
}

void Homework_0114_frameImg::update(void)
{
	MainGame::update();


	if(KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_rcPlayer.left -= 5;
		_rcPlayer.right -= 5;
		_state = STATE_MOVE;
		_isLeft = true;

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_rcPlayer.left += 5;
		_rcPlayer.right += 5;
		_state = STATE_MOVE;
		_isLeft = false;
	}


	if (!(GetAsyncKeyState(VK_LEFT) & 0x8000) &&
		!(GetAsyncKeyState(VK_RIGHT) & 0x8000) && 
		!_isAnimating)
	{
		_state = STATE_IDLE;
		_playerIdle->setFrameY(static_cast<int>(!_isLeft));
	}
	_count++;


	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_playerAttack->setFrameY(static_cast<int>(!_isLeft));
		_state = STATE_ATTACK;
		_isAnimating = true;
		_index = -1;

	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_playerMAttack->setFrameY(static_cast<int>(!_isLeft));
		_state = STATE_M_ATTACK;
		_isAnimating = true;
		_index = -1;

	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_playerCicleAttack->setFrameY(static_cast<int>(!_isLeft));
		_state = STATE_CICLE;
		_isAnimating = true;
		_index = -1;

	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		_playerVictory->setFrameY(static_cast<int>(!_isLeft));
		_state = STATE_VICTORY;
		_isAnimating = true;
		_index = -1;

	}

	if (_count % 5 == 0) 
	{
		switch (_state)
		{
		case STATE_IDLE:
			PlayFrameAnimation(_playerIdle, _isLeft, _index);
			_isAnimating = false;
			break;

		case STATE_MOVE:
			PlayFrameAnimation(_playerMove, _isLeft, _index);
			_isAnimating = false;
			break;

		case STATE_ATTACK:
			PlayOnceAnimation(_playerAttack, _isLeft, _index,_isAnimating);

			break;
		case STATE_M_ATTACK:
			PlayOnceAnimation(_playerMAttack, _isLeft, _index, _isAnimating);

			break;
		case STATE_CICLE:
			PlayOnceAnimation(_playerCicleAttack, _isLeft, _index, _isAnimating);

			break;
		case STATE_VICTORY:
			PlayOnceAnimation(_playerVictory, _isLeft, _index, _isAnimating);

			break;
		default:
			break;
		}
	}
	

}

void Homework_0114_frameImg::render(HDC hdc)
{
	HDC memDc = this->getBackBuffer()->getMemDC();
	PatBlt(memDc, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	_background->render(memDc, 0, 50);


	if (KEYMANAGER->isToggleKey(VK_F1)) 
	{
		RectangleMakeToRECT(memDc, _rcPlayer);
	}

	switch (_state) 
	{
	case STATE_IDLE:
		_playerIdle->frameRender(memDc, _rcPlayer.left, _rcPlayer.top);
		break;
	case STATE_MOVE:
		_playerMove->frameRender(memDc, _rcPlayer.left, _rcPlayer.top);
		break;
	case STATE_ATTACK:
		if (_isLeft) 
		{
			_playerAttack->frameRender(memDc, _rcPlayer.left-300, _rcPlayer.top);
		}
		else 
		{
			_playerAttack->frameRender(memDc, _rcPlayer.left, _rcPlayer.top);
		}
		
		break;
	case STATE_M_ATTACK:
		if (_isLeft)
		{
			_playerMAttack->frameRender(memDc, _rcPlayer.left-300, _rcPlayer.top);
		}
		else 
		{
			_playerMAttack->frameRender(memDc, _rcPlayer.left, _rcPlayer.top);
		}
		
		break;
	case STATE_CICLE:
		if (_isLeft)
		{
			_playerCicleAttack->frameRender(memDc, _rcPlayer.left-80, _rcPlayer.top-140);
		}
		else
		{
			_playerCicleAttack->frameRender(memDc, _rcPlayer.left-130, _rcPlayer.top-140);
		}
		
		break;
	case STATE_VICTORY:
		if (_isLeft)
		{
			_playerVictory->frameRender(memDc, _rcPlayer.left-215, _rcPlayer.top);
		}
		else
		{
			_playerVictory->frameRender(memDc, _rcPlayer.left+15, _rcPlayer.top+5);
		}
		break;
	}

	this->getBackBuffer()->render(hdc, 0, 0);
}


void Homework_0114_frameImg::PlayFrameAnimation(my::Image * image, bool isleft, int &index)
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

bool Homework_0114_frameImg::PlayOnceAnimation(my::Image * image, bool isleft, int &index, bool &isAnimating)
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
