#include "Stdafx.h"
#include "CProjectPlayer.h"
#include "EnemyManager.h"

HRESULT CProjectPlayer::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("player", "Resource/Images/Project/player.bmp", 0.0f, 0.0f, 192 , 135 ,6,3, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("playerBullet1", "Resource/Images/Project/playerBullet1.bmp",  14, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerBullet2", "Resource/Images/Project/playerBullet2.bmp", 8, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerBullet3", "Resource/Images/Project/playerBullet3.bmp", 14, 18, true, RGB(255, 0, 255));
	
	_x = CENTER_X;
	_y = WINSIZE_Y-100;
	_rc = RectMakeCenter(_x, _y,_image->getFrameWidth(), _image->getFrameHeight());
	_currentHp = 10;
	_maxHp = 10;
	_rndTimeCount =0.05;
	_worldTimeCount=0;
	_currentFrameX=0;
	_currentFrameY=0;
	_bulletCoolTime = 0.05f;
	_bulletWorldTime = TIMEMANAGER->getWorldTime();

	_hpBar = new HpImgBar;
	_hpBar->init(&_x,&_y,_rc.right-_rc.left,10,&_currentHp,0,-20);

	_aMissile = nullptr;
	ZeroMemory(&_arrAMissile, sizeof(_arrAMissile));
	_arrAMissile[0] = new LinearMissile;
	_arrAMissile[0]->init(100, 1000);
	_arrAMissile[1] = new CaseShotMissile;
	_arrAMissile[1]->init(20, 500);
	setAMissile(0);

	_type = ObservedType::ROCKET;
	_pState = EPPlayer_State::Idle;
	_previousState = EPPlayer_State::Left;
	_isActive = true;

	_currentAni = new Animation;
	_currentAni->init(192, 135, 32, 45);
	_currentAni->setFPS(16);

	RECTOBSERVERMANAGER->registerObserved(this);
	return S_OK;
}

void CProjectPlayer::release(void)
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);

	if (_arrAMissile[0] != nullptr) _arrAMissile[0]->release();
	if (_arrAMissile[1] != nullptr) _arrAMissile[1]->release();
	SAFE_DELETE(_aMissile);
	RECTOBSERVERMANAGER->removeObserved(this);
}

void CProjectPlayer::update(void)
{
	_pState = EPPlayer_State::Idle;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X ) 
	{
		_pState = EPPlayer_State::Right;
		_x += ROCKET_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
	{
		_pState = EPPlayer_State::Left;
		_x -= ROCKET_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0 )
	{
		_y -= ROCKET_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom< WINSIZE_Y )
	{
		_y += ROCKET_SPEED;
	}
	_currentAni->frameUpdate(TIMEMANAGER->getElapsedTime());

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	//AMissile
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		setAMissile(0);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		setAMissile(1);
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		if (_bulletCoolTime + _bulletWorldTime <= TIMEMANAGER->getWorldTime()) 
		{
			_bulletWorldTime = TIMEMANAGER->getWorldTime();
			fireAMissile();
		}
	}

	_hpBar->update();

	if(_arrAMissile[0] != nullptr) _arrAMissile[0]->update();
	if(_arrAMissile[1] != nullptr) _arrAMissile[1]->update();

}

void CProjectPlayer::render(void)
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _currentAni);

	animation();

	_hpBar->render(getMemDC());
	if (_arrAMissile[0] != nullptr) _arrAMissile[0]->render();
	if (_arrAMissile[1] != nullptr) _arrAMissile[1]->render();
}


//================================
// ### AMissile ###
//================================
void CProjectPlayer::setAMissile(int index)
{
	if (_arrAMissile[index] == nullptr) return;
	_aMissile = _arrAMissile[index];
}

void CProjectPlayer::fireAMissile(void)
{
	if (_aMissile == nullptr) return;
	_aMissile->fire(_x, _y );
}

//================================
// ### animation ###
//================================
void CProjectPlayer::animation(void)
{
	if (_pState != _previousState)
	{
		switch (_pState)
		{
		case EPPlayer_State::Idle:
			_currentFrameY = 0;
			_currentFrameX++;
			if (_image->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameX = 0;
			}
			_currentAni->setPlayFrame(0, 5, false, true);
			_currentAni->AniStart();
			_previousState = EPPlayer_State::Idle;

			break;
		case EPPlayer_State::Right:
			_currentFrameY = 1;
			_currentFrameX++;
			if (_image->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameY = 0;
				_currentFrameX = 0;
			}
			_currentAni->setPlayFrame(6, 11, false, true);
			_currentAni->AniStart();
			_previousState = EPPlayer_State::Right;

			break;
		case EPPlayer_State::Left:
			_currentFrameY = 2;
			_currentFrameX++;
			if (_image->getMaxFrameX() < _currentFrameX)
			{
				_currentFrameY = 0;
				_currentFrameX = 0;
			}
			_currentAni->setPlayFrame(12, 17, false, true);
			_currentAni->AniStart();
			_previousState = EPPlayer_State::Left;

			break;
		default:
			break;
		}

	}
}

STObservedData CProjectPlayer::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_isActive;
	return temp;
}

void CProjectPlayer::collideObject()
{
	_currentHp--;
	if (_currentHp < 0) 
	{
		_isActive = false;
	}
}
