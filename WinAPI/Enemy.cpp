#include "Stdafx.h"
#include "Enemy.h"


Enemy::Enemy(void) : _rc(RectMake(0, 0, 0, 0)),
					_currentFrameX(0),
					_currentFrameY(0),
					_x(0.0f),
					_y(0.0f),
					_rndTimeCount(0.0f),
					_worldTimeCount(0.0f),
					_bulletFireCount(0.0f),
					_rndFireCount(0.0f)
{
}

HRESULT Enemy::init(void)
{
	return S_OK;
}

HRESULT Enemy::init(const char* imageName, POINT position)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f,4.5f);

	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->getFrameWidth(), _image->getFrameHeight());

	//Observer code
	_type = ObservedType::MINION;
	_isActive = true;
	RECTOBSERVERMANAGER->registerObserved(this);

	return S_OK;
}

void Enemy::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
}

void Enemy::update(void)
{
	move();
}

void Enemy::render(void)
{
	draw();
	animation();
}

void Enemy::move(void)
{
}

void Enemy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void Enemy::animation(void)
{
	if (_rndTimeCount + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;
		if (_image->getMaxFrameX() < _currentFrameX)
		{
			_currentFrameX = 0;
		}
	}
}

bool Enemy::bulletCountFire(void)
{
	if (_rndFireCount + _bulletFireCount <= TIMEMANAGER->getWorldTime()) 
	{
		
		_bulletFireCount = TIMEMANAGER->getWorldTime();
		_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);

		return true;
	}
	return false;
}


STObservedData Enemy::getRectUpdate(){
	return STObservedData();
}

void Enemy::collideObject(){
}
