#include "Stdafx.h"
#include "GameClass_0104.h"



HRESULT GameClass_0104::init(void)
{
	//1. 플레이어 셋팅
	_player.rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 200, 40, 40);
	_player.hp = 100;
	//2. 적 셋팅
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		_enemy[i].rc = RectMakeCenter(RND->getFromIntTo(20, WINSIZE_X - 20), -(RND->getFromIntTo(80, WINSIZE_Y * 2)), 20, 20);
		_enemy[i].speed = RND->getInt(5);
		_enemy[i].die = false;
		_enemy[i].damage = RND->getInt(10);
	}
	isGameOver = false;
	_bar = HPprogressBar(_player.hp);

	return S_OK;
}

void GameClass_0104::release(void)
{
}

void GameClass_0104::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _player.rc.left)
	{
		_player.rc.left -= PLAYER_SPEED;
		_player.rc.right -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && 0 < _player.rc.top)
	{
		_player.rc.top -= PLAYER_SPEED;
		_player.rc.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _player.rc.right)
	{
		_player.rc.left += PLAYER_SPEED;
		_player.rc.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _player.rc.bottom)
	{
		_player.rc.top += PLAYER_SPEED;
		_player.rc.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fire();
	}
	_bar.UpdateHpBar(&_player.rc, _player.hp);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].isfire)continue;
		_bullet[i].rc.top -= 14;
		_bullet[i].rc.bottom -= 14;
		if (_bullet[i].rc.bottom < 0) _bullet[i].isfire = false;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die)continue;
		_enemy[i].rc.top += _enemy[i].speed;
		_enemy[i].rc.bottom += _enemy[i].speed;

		if (_enemy[i].rc.top > WINSIZE_Y)
		{
			_enemy[i].rc = RectMakeCenter(RND->getFromIntTo(20, WINSIZE_X - 20), -(RND->getFromIntTo(80, WINSIZE_Y * 2)), 20, 20);
		}
	}

	//충돌처리
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!_enemy[i].die)
		{	//플레이어와 충돌
			if (RectIsCollider(&_player.rc, &_enemy[i].rc))
			{
				_player.hp -= _enemy[i].damage;
				_enemy[i].die = true;
				if (_player.hp < 0)
				{
					isGameOver = true;
				}
			}

			//총알과 충돌
			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (!_bullet[j].isfire) continue;
				if (RectIsCollider(&_enemy[i].rc, &_bullet[j].rc))
				{
					_enemy[i].die = true;
					_bullet[j].isfire = false;
					break;

				}
			}
		}
	}



}

void GameClass_0104::render(HDC hdc)
{
	if (isGameOver) return;

	HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
	Rectangle(hdc, _player.rc.left, _player.rc.top, _player.rc.right, _player.rc.bottom);
	FillRect(hdc, &_player.rc, brush);
	DeleteObject(brush);

	_bar.RenderHpbar(hdc);


	//char playerHpStr[120];
	//wsprintf(playerHpStr, " HP    %d", _player.hp);
	//TextOut(hdc, 0, WINSIZE_Y - 20, playerHpStr, strlen(playerHpStr));


	HBRUSH brush1 = CreateSolidBrush(RGB(255, 0, 0));
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die)continue;
		Rectangle(hdc, _enemy[i].rc.left, _enemy[i].rc.top, _enemy[i].rc.right, _enemy[i].rc.bottom);

		FillRect(hdc, &_enemy[i].rc, brush1);
	}
	DeleteObject(brush1);

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].isfire)continue;
		Ellipse(hdc, _bullet[i].rc.left,
			_bullet[i].rc.top,
			_bullet[i].rc.right,
			_bullet[i].rc.bottom);
	}

}


void GameClass_0104::fire(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet[i].isfire)continue;
		_bullet[i].isfire = true;
		_bullet[i].rc = RectMakeCenter(_player.rc.left + (_player.rc.right - _player.rc.left) / 2, _player.rc.top, 20, 20);

		break;
	}
}

bool GameClass_0104::RectIsCollider(RECT * rec1, RECT * rec2)
{
	if (rec1->left < rec2->right &&
		rec1->top < rec2->bottom &&
		rec1->right > rec2->left &&
		rec1->bottom > rec2->top)
	{
		return true;
	}
	return false;
}