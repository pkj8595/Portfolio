#include "Stdafx.h"
#include "HomeWork_0104.h"



HRESULT HomeWork_0104::init(void)
{
	temp = 0;
	_startRc[0] = RectMakeCenter(WINSIZE_X / 4, WINSIZE_Y/2, 30, 30);
	_startRc[1] = RectMakeCenter(WINSIZE_X-(WINSIZE_X / 4), WINSIZE_Y/2, 30, 30);

	isGameOver = false;
	_player[0] = BattleGamePlayer(_startRc[0],100,5,10,RGB(0,255,0),true,1);
	_player[1] = BattleGamePlayer(_startRc[1],100,5,10,RGB(0,0,255),false,-1);

	_count = 0;

	skill_Reflection = { false,{0,0,0,0},120,0};
	skill_Shield = { false,{0,0,0,0},120,0};
	skill_timeStop = {false,120,0};
	skill_Tornado = { false,{0,0,0,0},5,10,1000,0,0,0 };


	return S_OK;
}

void HomeWork_0104::release(void)
{

}

void HomeWork_0104::update(void)
{
	if (isGameOver) return;

	_count++;
	//플레이어의 행동을 각각 함수로 나누는게 원하는 기능을 만들때 용이할듯 이런 부분은 상태이상을 만들때 쓸만하다.
	if (!skill_timeStop.isActive)
	{
		_player[0].update();
		_player[1].update();
	}

	
	
	//1p skill
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		skill_Reflection.isActive = true;
		skill_Reflection.rc =
			RECT{ _player[0].getRC().right + 20,
				_player[0].getRC().top - 50,
				_player[0].getRC().right + 30,
				_player[0].getRC().bottom + 50 };
				
	}
	if (KEYMANAGER->isOnceKeyDown('G'))
	{
		skill_timeStop.isActive = true;
	}
	if (KEYMANAGER->isOnceKeyDown('H'))
	{

	}
	//2p skill
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		skill_Shield.isActive = true;

		skill_Shield.rc =
			RECT{ _player[1].getRC().left - 30,
				_player[1].getRC().top - 30,
				_player[1].getRC().right + 30,
				_player[1].getRC().bottom + 30 };
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		skill_Tornado.isActive = true;
		skill_Tornado.rc = RectMakeCenter(
			((_player[1].getRC().left + _player[1].getRC().right) / 2)-100, 
			((_player[1].getRC().top + _player[1].getRC().bottom) / 2),
			100,
			100);
			/*RECT{ _player[1].getRC().left - 130,
				_player[1].getRC().top - 30,
				_player[1].getRC().left -80,
				_player[1].getRC().bottom -70};*/
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{

	}

	
	for (int i = 0; i < 2; i++) 
	{
		temp = (i+1) % 2;
		//총알
		for (int j = 0; j < BULLET_MAX; j++)
		{
			if (!_player[i]._bullet[j].isfire) continue;
			//반사
			if (RectIsCollider(&skill_Reflection.rc, &_player[i]._bullet[j].rc))
			{
				_player[i]._bullet[j]._direction *= -1;
			}
			if (RectIsCollider(&skill_Shield.rc, &_player[i]._bullet[j].rc))
			{
				_player[i]._bullet[j].isfire = false;
			}

			//플레이어가 총에 맞았을 시 
			if (RectIsCollider(&_player[temp].getRC(),
				&_player[i]._bullet[j].rc))
			{
				_player[i]._bullet[j].isfire = false;
				_player[temp].beAttacked(_player[i].getDamage());
				if (_player[temp].getHp() < 0)
				{
					isGameOver = true;
				}
				break;
			}
			
			if (RectIsCollider(&_player[i].getRC(),
				&_player[i]._bullet[j].rc))
			{
				_player[i]._bullet[j].isfire = false;
				_player[i].beAttacked(_player[i].getDamage());
				if (_player[i].getHp() < 0)
				{
					isGameOver = true;
				}
				break;
			}

			
		}
	}


	if (skill_Reflection.isActive)
	{
		skill_Reflection.timeCount++;
		if (skill_Reflection.time - skill_Reflection.timeCount < 0)
		{
			skill_Reflection.rc = RECT{ 0,0,0,0 };
			skill_Reflection.timeCount = 0;
			skill_Reflection.isActive = false;

			for (int i = 0; i < BULLET_MAX;i++) 
			{
				_player[1]._bullet[i]._direction = -1;
			}
		}
	}
	
	if (skill_Shield.isActive)
	{
		skill_Shield.timeCount++;
		if (skill_Shield.time - skill_Shield.timeCount < 0)
		{
			skill_Shield.rc = RECT{ 0,0,0,0 };
			skill_Shield.timeCount = 0;
			skill_Shield.isActive = false;
		}
	}

	if (skill_timeStop.isActive)
	{
		skill_timeStop.timeCount++;
		if (skill_timeStop.time - skill_timeStop.timeCount < 0)
		{
			skill_timeStop.timeCount = 0;
			skill_timeStop.isActive = false;
		}
	}


	if (skill_Tornado.isActive)
	{
		skill_Tornado.timeCount++;
		if (skill_Tornado.time - skill_Tornado.timeCount < 0)
		{
			skill_Tornado.timeCount = 0;
			skill_Tornado.isActive = false;
		}
		else 
		{
			/*skill_Tornado.x = cos(COMPUTE_RADIAN(skill_Tornado.timeCount));
			skill_Tornado.y = sin(COMPUTE_RADIAN(skill_Tornado.timeCount));
			skill_Tornado.rc.left =  
			skill_Tornado.rc.top = 
			skill_Tornado.rc.right = 
			skill_Tornado.rc.bottom =
			*/
		}
	}
	
	
	

}

void HomeWork_0104::render(HDC hdc)
{
	if (isGameOver) return;
	_player[0].render(hdc);
	_player[1].render(hdc);

	if (skill_Reflection.isActive) 
	{
		RectangleMakeToRECT(hdc, skill_Reflection.rc);
	}

	if (skill_Shield.isActive)
	{
		RectangleMakeToRECT(hdc, skill_Shield.rc);
	}

	if (skill_timeStop.isActive)
	{
		char strStop[128];
		wsprintf(strStop, "플레이어 1의 스킬로 인해 게임이 멈춤 %d", skill_timeStop.time - skill_timeStop.timeCount);
		TextOut(hdc, WINSIZE_X / 2 - 130, WINSIZE_Y / 2, strStop, strlen(strStop));
	}

	if (skill_Tornado.isActive) 
	{
		RectangleMakeToRECT(hdc, skill_Tornado.rc);
	}



}

bool HomeWork_0104::RectIsCollider(RECT * rec1, RECT * rec2)
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


