#include "Stdafx.h"
#include "BattleGamePlayer.h"

BattleGamePlayer::BattleGamePlayer()
{
	_rc = RectMakeCenter(0,0,30,30);//생성자
	_hp = 100;
	_maxHp = 100;
	_speed = 3;
	_damage = 10;
	_isDie = false;

	/*_skill[0] = nullptr;
	_skill[1] = nullptr;
	_skill[2] = nullptr;*/
	_hpBar = HPprogressBar(_hp);
	_rgb = RGB(0, 255, 0);
	for (int i = 0; i < BULLET_MAX; i++)
	{
		_bullet[i]._direction = 1;
	}
}

BattleGamePlayer::BattleGamePlayer(RECT rc, int hp, int speed, int damage, COLORREF rgb, bool isFirst,int derection)
{
	_rc = rc;//생성자
	_hp = hp;
	_maxHp = hp;
	_speed = speed;
	_damage = damage;
	_isDie = false;

	/*_skill[0] = nullptr;
	_skill[1] = nullptr;
	_skill[2] = nullptr;*/
	_hpBar = HPprogressBar(_hp);
	_rgb = rgb;
	_isFirst = isFirst;
	_directionSave = derection;
	for (int i = 0; i < BULLET_MAX;i++) 
	{
		_bullet[i]._direction = derection;
	}
}

BattleGamePlayer::~BattleGamePlayer()
{
}

void BattleGamePlayer::render(HDC hdc)
{

	HBRUSH brush = CreateSolidBrush(_rgb);
	Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);
	FillRect(hdc, &_rc, brush);
	DeleteObject(brush);

	_hpBar.RenderHpbar(hdc);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].isfire)continue;
		Ellipse(hdc, _bullet[i].rc.left,
			_bullet[i].rc.top,
			_bullet[i].rc.right,
			_bullet[i].rc.bottom);
	}

}

void BattleGamePlayer::update()
{
	if (_isFirst)
	{
		if (KEYMANAGER->isStayKeyDown('A') && 0 < _rc.left)
		{
			_rc.left -= _speed;
			_rc.right -= _speed;
		}
		if (KEYMANAGER->isStayKeyDown('W') && 0 < _rc.top)
		{
			_rc.top -= _speed;
			_rc.bottom -= _speed;
		}
		if (KEYMANAGER->isStayKeyDown('D') && WINSIZE_X > _rc.right)
		{
			_rc.left += _speed;
			_rc.right += _speed;
		}
		if (KEYMANAGER->isStayKeyDown('S') && WINSIZE_Y > _rc.bottom)
		{
			_rc.top += _speed;
			_rc.bottom += _speed;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			fire();
		}
		//if (KEYMANAGER->isOnceKeyDown('F'))
		//{
		//	//TriggerSkill(0);
		//}
		//if (KEYMANAGER->isOnceKeyDown('G'))
		//{
		//	//TriggerSkill(1);
		//}
		//if (KEYMANAGER->isOnceKeyDown('H'))
		//{
		//	//TriggerSkill(2);
		//}

	}
	else 
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _rc.left)
		{
			_rc.left -= _speed;
			_rc.right -= _speed;
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP) && 0 < _rc.top)
		{
			_rc.top -= _speed;
			_rc.bottom -= _speed;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _rc.right)
		{
			_rc.left += _speed;
			_rc.right += _speed;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _rc.bottom)
		{
			_rc.top += _speed;
			_rc.bottom += _speed;
		}
		if (KEYMANAGER->isOnceKeyDown('U'))
		{
			fire();
		}
		//if (KEYMANAGER->isOnceKeyDown('I'))
		//{
		//	//TriggerSkill(0);
		//}
		//if (KEYMANAGER->isOnceKeyDown('O'))
		//{
		//	//TriggerSkill(1);
		//}
		//if (KEYMANAGER->isOnceKeyDown('P'))
		//{
		//	//TriggerSkill(2);
		//}
		
	}
	
	_hpBar.UpdateHpBar(&_rc, _hp);

	//그려준 총알 이동
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].isfire)continue;

			_bullet[i].rc.right += 14 * _bullet[i]._direction;
			_bullet[i].rc.left += 14 * _bullet[i]._direction;

		if (_bullet[i].rc.left >WINSIZE_X ||
			_bullet[i].rc.right <0 ||
			_bullet[i].rc.bottom < 0 ||
			_bullet[i].rc.top > WINSIZE_Y 
			) _bullet[i].isfire = false;
	}

}

void BattleGamePlayer::fire(void)
{
	//총알위치
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet[i].isfire)continue;
		_bullet[i].isfire = true;
		if (_isFirst) 
		{
			_bullet[i].rc = RectMakeCenter(
			_rc.right + 20,
			_rc.top + (_rc.bottom - _rc.top)*0.5, 20, 20);
		}
		else 
		{
			_bullet[i].rc = RectMakeCenter(
			_rc.left - 20,
			_rc.top + (_rc.bottom - _rc.top)*0.5, 20, 20);
		}
		break;

		
	}
}

/*

bool BattleGamePlayer::TriggerSkill(int key)
{
	if (_skill[key] == nullptr) return false;
	_skill[key]->SkillTrigger(_rc);
	return true;
}

void BattleGamePlayer::SetSkill(iSkill* skill)
{
	if (skill == nullptr) return;
	for (int i = 0; i < 3; i++) {
		if (_skill[i] == nullptr) 
		{
			_skill[i] = skill;
		}
	}
}
*/
