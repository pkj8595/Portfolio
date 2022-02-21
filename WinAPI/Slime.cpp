#include "Stdafx.h"
#include "Slime.h"

Slime::Slime()
{
}

Slime::~Slime()
{


}

HRESULT Slime::init(const char * imageName, POINT position)
{
	IMAGEMANAGER->addImage("EnemyBullet", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/bullet4.bmp", 32, 32, true, RGB(255, 0, 255));

	Enemy::init(imageName,position);
	_x = position.x;
	_y = position.y;
	_speed = 1.f;
	_time = 150;

	_slimeDir = SLIMEDIRECTION::SM_DOWN;
	_slimestate = SLIMESTATE::SM_IDLE;

	_ani = new Animation;
	_ani->init(_image->getWidth(), _image->getHeight(),96,96);
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(2);
	_ani->AniStart();

	_bullet = new Bullet;
	_bullet->init("EnemyBullet", 5, 300);


	return S_OK;
}

void Slime::release(void)
{
	Enemy::release();
}

void Slime::update(void)
{
	Enemy::update();
	_bullet->update();

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_bullet->fire(_x, _y, 50, 2);
	}
}

void Slime::render(void)
{
	Enemy::render();
	_bullet->render();
}

void Slime::move(void)
{
	/*
	랜덤 이동
	x,y는 랜덤으로 이동한다. 
	random , getint -1,0,1  
	x축
	-1 = 좌 이동
	0  = 대기
	1  = 우 이동

	y축
	-1 = 상 이동
	0  = 대기 
	1  = 하 이동

	시간값 -> 랜덤 쿨타임 돌려준다.
	*/

	
	if (_time <= 0) //확인용
	{
		//randomX = RND->getInt(3) - 1;
		//randomY = RND->getInt(3) - 1;
		_time = 150;
	}
	_time--;

	//_x += randomX * _speed;
	//_y += randomY * _speed;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//
	//}

	if (randomX == -1)
	{
		_slimeDir = SLIMEDIRECTION::SM_LEFT;
		_slimestate = SLIMESTATE::SM_MOVE;
	}

	 if (randomX == 1)
	{
		_slimeDir = SLIMEDIRECTION::SM_RIGHT;
		_slimestate = SLIMESTATE::SM_MOVE;
	}

	 if (randomX == 0)
	{
		_slimeDir = _slimeDir;
		_slimestate = SLIMESTATE::SM_IDLE;
	}

	if (randomY == -1)
	{
		_slimeDir = SLIMEDIRECTION::SM_UP;
		_slimestate = SLIMESTATE::SM_MOVE;
	}

	 if (randomY == 1)
	{
		_slimeDir = SLIMEDIRECTION::SM_DOWN;
		_slimestate = SLIMESTATE::SM_MOVE;
	}

	 if (randomY == 0)
	{
		_slimeDir = _slimeDir;
		_slimestate = SLIMESTATE::SM_IDLE;
	}

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void Slime::draw(void)
{
	//_image->frameRender(getMemDC(), _rc.left, _rc.top);
	_image->aniRender(getMemDC(),_rc.left,_rc.top, _ani);

	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	cout << randomX << endl;
	//system("pause");
}

void Slime::animation(void)
{
	switch (_slimeDir)
	{
	case SLIMEDIRECTION::SM_LEFT: //왼쪽일 때
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
				_ani->setPlayFrame(4, 6, false, true);
			break;
		
		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(16, 18, false, true);
			break;
		
		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(28, 30, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_RIGHT: //오른쪽일 때
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
				_ani->setPlayFrame(7, 9, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(19, 21, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(31, 33, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_UP: //위쪽
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
			_ani->setPlayFrame(10, 12, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(22, 24, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(34, 36, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_DOWN: //아래쪽
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
			_ani->setPlayFrame(1, 3, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(13, 15, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(25, 27, false, true);
			break;
		}
		break;
	}
}
