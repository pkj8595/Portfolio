#include "Stdafx.h"
#include "MapPatternController.h"


MapPatternController::MapPatternController() : _ColumnBool(false), _angleCount(0), _count(90)
{
}


HRESULT MapPatternController::init()
{
	_mapMatrix.SetElements(1, 0, 0, 1, 0, 0);
	IMAGEMANAGER->initForGPbitmap("≈È¥œ", L"Resource/Images/Popol/arm2.png", 4);
	IMAGEMANAGER->initForGPbitmap("arm1", L"Resource/Images/Popol/arm1.png", 4);
	IMAGEMANAGER->initForGPbitmap("bim", L"Resource/Images/Popol/bim.png", 4);
	IMAGEMANAGER->initForGPbitmap("boss_smile", L"Resource/Images/Popol/NBbossFace_s.png", 4);
	IMAGEMANAGER->initForGPbitmap("boss_idle", L"Resource/Images/Popol/NBbossFace_b.png", 4);
	IMAGEMANAGER->initForGPbitmap("boss_angry", L"Resource/Images/Popol/bossFace_a.png", 4);
	IMAGEMANAGER->initForGPbitmap("boss_end1", L"Resource/Images/Popol/bossFace_e1.png", 4);
	IMAGEMANAGER->initForGPbitmap("boss_end2", L"Resource/Images/Popol/bossFace_e2.png", 4);
	IMAGEMANAGER->initForGPbitmap("boss_mm", L"Resource/Images/Popol/bossFace_m.png", 4);

	return S_OK;
}


void MapPatternController::update(int time)
{

	//bossRotateRectPattern(time,1000, 13000);
	//==================
	shapePattern1(time, 0, 28000);
	bossPattern1(time, 28000, 38000);
	bigRectPattern(time, 27000, 40000);
	frashPattern2(time, 38000, 58000);
	shapePatternDrectionColumn(time, 58000, 79000);
	bigRectPattern2(time, 58000, 79000);
	bossPattern1(time, 80000, 100000);
	shapePattern2(time, 82000, 100000);
	if (time == 91000) _boss.setImageKey("boss_idle");
	frashPattern2(time, 102000, 110000);
	wavePattern(time, 112000, 132000);
	bossWavePattern2(time, 112000, 133000);
	bossUpDownPattern(time, 133000, 147000);
	bossRotateRectPattern(time, 148000, 160000);
	bossDrectionPattern(time, 161000, 170000);
	bossFinalPattern(time, 170000, 182000);

}

void MapPatternController::bigRectPattern(int time, int startTime, int endTime)
{

	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	if (time == startTime)
	{
		_bossBigRect.ResetPositionRc(RectF(-WINSIZE_X / 2, -WINSIZE_X / 2, WINSIZE_X, WINSIZE_X), WINSIZE_X / 2, WINSIZE_Y / 2, 0, true, 200, time, 0, 10000, 0.01f);
		_bossBigRect.setTimeOffset(0);

	}
	else if (time > startTime && time < startTime + 8000)
	{
		_bossBigRect.setPenWidth(_bossBigRect.getPenWidth() + 3);
	}
	else if (time > startTime + 8000 && time < startTime + 10000)
	{
		_bossBigRect.setPenWidth(_bossBigRect.getPenWidth() - 15);
	}
	_bossBigRect.update(time);

}

void MapPatternController::bigRectPattern2(int time, int startTime, int endTime)
{
	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	if (time == startTime)
	{
		_bossBigRect.ResetPositionRc(RectF(-WINSIZE_X / 2 - 25, -WINSIZE_Y / 2, WINSIZE_X + 50, WINSIZE_Y), WINSIZE_X / 2, WINSIZE_Y / 2, 0, true, 0, time, 0, endTime + 3000, 0);
		_bossBigRect.setTimeOffset(0);
		_bossBigRect.addAngle(0);
		_bossBigRect.setAngle(0);
	}
	else if (time < endTime&&_bossBigRect.getPenWidth() < 100)
	{
		_bossBigRect.setPenWidth(_bossBigRect.getPenWidth() + 3);
	}
	else if (time > endTime)
	{
		_bossBigRect.setPenWidth(_bossBigRect.getPenWidth() - 1);
		if (_bossBigRect.getPenWidth() < 0) _bossBigRect.setIsActive(false);
	}

	_bossBigRect.update(time);

}

void MapPatternController::bossPattern1(int time, int startTime, int endTime)
{
	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	if (time == startTime)
	{
		_boss.setIsActive(true);
		_boss.setTime(time);
		_boss.setActiveTime(endTime - startTime + 10000);
		_boss.setTimeOffset(0);
		_boss.setPosition(WINSIZE_X / 2, -400);
		_boss.setImageKey("boss_smile");
		_boss.setSize(1);
		_boss.setAngle(0);
		_boss.setIsReadyPosition(false);
	}
	else if (time > startTime && time < endTime)
	{

		if (_boss.getPosition().Y < 300)
		{
			_boss.setPosition(WINSIZE_X / 2, _boss.getPosition().Y + 10);
		}
		else if (!_boss.getIsReadyPosition())
		{
			_boss.setAddAngle(0.005f);
			_boss.setIsReadyPosition(true);
		}
		else if (_boss.getAngle() < -0.2f)
		{
			_boss.setAddAngle(0.005f);
		}
		else if (_boss.getAngle() > 0.2f)
		{
			_boss.setAddAngle(-0.005f);
		}

	}
	else if (time == endTime)
	{
		_boss.setAddAngle(0);
		_boss.setAngle(0);
		_boss.setIsReadyPosition(false);
	}
	else if (time > endTime)
	{
		if (_boss.getPosition().Y > -300)
		{
			_boss.setPosition(WINSIZE_X / 2, _boss.getPosition().Y - 10);
			_boss.setIsActive(false);
		}
	}

	_boss.update(time);

}


void MapPatternController::shapePattern1(int time, int startTime, int endTime)
{
	if (!(time > startTime - 1000 && time < endTime + 10000)) return;


	for (int i = 0; i < 10; i++)
	{
		_rectShape[i].update(time);

		if (time > startTime && time < endTime)
		{

			if (!_rectShape[i].getIsActive())
			{
				if (time >= _rectShape[i].getTime())
				{
					if (time > startTime + 16000)
					{
						_rectShape[i].setResetRc(RectF(-50, -50, 100, 100), 20, true, 10, 1000, static_cast<blockDrection>(RND->getInt(4)));
					}
					else
					{
						_rectShape[i].setResetRc(RectF(-50, -50, 100, 100), 20, true, 10, 3000, LEFT);

					}
					_rectShape[i].setAddAngle(-0.1f);
				}
			}
		}
	}

}

void MapPatternController::shapePattern2(int time, int startTime, int endTime)
{
	if (!(time > startTime - 1000 && time < endTime + 10000)) return;


	for (int i = 0; i < 10; i++)
	{
		_rectShape[i].update(time);

		if (time > startTime && time < endTime)
		{

			if (!_rectShape[i].getIsActive())
			{
				if (time >= _rectShape[i].getTime())
				{
					if (time > startTime + 9000)
					{
						_rectShape[i].setResetRc(RectF(-50, -50, 100, 100), 20, true, 10, 1000, static_cast<blockDrection>(RND->getInt(4)));
					}
					else
					{
						_rectShape[i].setResetRc(RectF(-50, -50, 100, 100), 20, true, 10, 3000, LEFT);

					}
					_rectShape[i].setIsFrash(true);
					_rectShape[i].setAddAngle(-0.1f);
				}
			}
		}
	}
}

void MapPatternController::shapePatternDrectionColumn(int time, int startTime, int endTime)
{
	if (!(time > startTime - 1000 && time < endTime + 10000)) return;


	for (int i = 0; i < 8; i++)
	{
		_rectBlockNotRotate2[i].update(time);

		if (time > startTime && time < endTime)
		{
			if (!_rectBlockNotRotate2[i].getIsActive() && time % 1000 == 0)
			{
				if (time >= _rectBlockNotRotate2[i].getTime())
				{
					int temp = RND->getInt(4);

					if (temp % 2 == 1)
						_rectBlockNotRotate2[i].setResetRc(RectF(-WINSIZE_X / 2, -10, WINSIZE_X, 30), 8, false, 10, 4000, static_cast<blockDrection>(temp));
					else
						_rectBlockNotRotate2[i].setResetRc(RectF(-10, -WINSIZE_Y / 2, 30, WINSIZE_Y), 8, false, 10, 4000, static_cast<blockDrection>(temp));

					switch (temp)
					{
					case LEFT:
						_rectBlockNotRotate2[i].setPosition(WINSIZE_X + 200, WINSIZE_Y / 2);
						break;
					case TOP:
						_rectBlockNotRotate2[i].setPosition(WINSIZE_X / 2, WINSIZE_Y + 200);
						break;
					case RIGHT:
						_rectBlockNotRotate2[i].setPosition(-200, WINSIZE_Y / 2);
						break;
					case BOTTOM:
						_rectBlockNotRotate2[i].setPosition(WINSIZE_X / 2, -200);
						break;
					case POSITION:
						break;
					default:
						break;
					}
					break;
				}
			}
		}
	}
}



void MapPatternController::bossFinalPattern(int time, int startTime, int endTime)
{

	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	if (time == startTime)
	{
		_boss3.setIsActive(true);
		_boss3.setTime(time);
		_boss3.setActiveTime(endTime - startTime + 9000);
		_boss3.setTimeOffset(0);
		_boss3.setPosition(WINSIZE_X / 2, -400);
		_boss3.setImageKey("boss_angry");
		_boss3.setSize(1);
		_boss3.setAngle(0);
		_boss3.setIsReadyPosition(false);
	}
	else if (time > startTime && time < endTime)
	{

		if (!_boss3.getIsReadyPosition())
		{
			_boss3.setPosition(WINSIZE_X / 2, _boss3.getPosition().Y + 10);
			if (_boss3.getPosition().Y > WINSIZE_Y / 2)
			{
				_boss3.setAddAngle(0.03f);
				_boss3.setIsReadyPosition(true);
			}
		}
		else if (time > endTime - 3000)
		{
			_boss3.setImageKey("boss_end1");
		}
	}
	else if (time == endTime)
	{
		_boss3.setAddAngle(0);
		_boss3.setAngle(0);
		_boss3.setIsReadyPosition(false);


	}
	else if (time > endTime)
	{
		_boss3.setImageKey("boss_end2");

	}

	_boss3.update(time);


	if (time > startTime && time < endTime)
	{
		if (_boss3.getIsReadyPosition())
		{
			for (int i = 0; i < BLOCK2_SIZE; i++)
			{
				if (!_rectBlockNotRotate2[i].getIsActive() && time < endTime)
				{
					_rectBlockNotRotate2[i].ResetPositionRc(GPRectFMakeCenter(50, 50), WINSIZE_X / 2, WINSIZE_Y / 2, 0, true, 5, time, endTime, endTime, 0);
					_rectBlockNotRotate2[i].setLocalAngle(_boss3.getAngle());
					_rectBlockNotRotate2[i].setSpeed(10);
					_rectBlockNotRotate2[i].setAddAngle(-0.2f);
					_rectBlockNotRotate2[i].setIsFrash(true);
					break;
				}
			}
		}

	}
	for (int i = 0; i < BLOCK2_SIZE; i++)
	{
		if (_rectBlockNotRotate2[i].getIsActive())
		{
			_rectBlockNotRotate2[i].setPosition(
				cosf(_rectBlockNotRotate2[i].getLocalAngle()* (180 / PI)) * _rectBlockNotRotate2[i].getSpeed() + _rectBlockNotRotate2[i].getPosition().X,
				sinf(_rectBlockNotRotate2[i].getLocalAngle()* (180 / PI)) * _rectBlockNotRotate2[i].getSpeed() + _rectBlockNotRotate2[i].getPosition().Y);
		}
		_rectBlockNotRotate2[i].update(time);
	}
}


void MapPatternController::bossDrectionPattern(int time, int startTime, int endTime)
{
	if (!(time > startTime - 1000 && time < endTime + 10000)) return;


	for (int i = 0; i < 5; i++)
	{
		_imgBlock[i].update(time);

		if (time > startTime && time < endTime)
		{
			if (!_imgBlock[i].getIsActive())
			{
				if (time >= _imgBlock[i].getTime())
				{
					INT tempInt = RND->getInt(4);
					_imgBlock[i].setResetImg("", 1, 15, 3000, static_cast<blockDrection>(tempInt));
					_imgBlock[i].setAddAngle(-0.1f);
					_imgBlock[i].setSize(1);
					_imgBlock[i].setIsRandomTime(true);
					switch (tempInt)
					{
					case 0:
						_imgBlock[i].setImageKey("boss_idle");
						break;
					case 1:
						_imgBlock[i].setImageKey("boss_angry");
						break;
					case 2:
						_imgBlock[i].setImageKey("boss_mm");
						break;
					case 3:
						_imgBlock[i].setImageKey("boss_end1");
						break;
					default:
						break;
					}

				}
			}
		}
	}
}

void MapPatternController::bossUpDownPattern(int time, int startTime, int endTime)
{

	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	if (time == startTime)
	{
		_boss2.setIsActive(true);
		_boss2.setTime(time);
		_boss2.setActiveTime(endTime - startTime + 9000);
		_boss2.setTimeOffset(0);
		_boss2.setPosition(WINSIZE_X / 2, -200);
		_boss2.setImageKey("boss_smile");
		_boss2.setSize(1);
		_boss2.setAngle(0);
		_boss2.setIsReadyPosition(false);
		_boss2.setAddAngle(0);
	}
	else if (time > startTime && time < endTime)
	{
		if (!_boss2.getIsReadyPosition())
		{
			_boss2.setPosition(WINSIZE_X / 2, _boss2.getPosition().Y + 10);
			if (_boss2.getPosition().Y > WINSIZE_Y / 2 - 10)
			{
				_boss2.setIsReadyPosition(true);
			}
		}
		else
		{
			if (_boss2.getPosition().Y < WINSIZE_Y / 2)
			{
				_boolBossUpdownPattern = false;
			}
			else if (_boss2.getPosition().Y > WINSIZE_Y - 200)
			{
				_boolBossUpdownPattern = true;
			}
			REAL ty = _boss2.getPosition().Y + (_boolBossUpdownPattern ? -5 : +25);
			_boss2.setPosition(WINSIZE_X / 2, ty);
		}
	}
	else if (time == endTime)
	{
		_boss2.setAddAngle(0);
		_boss2.setAngle(0);
		_boss2.setIsReadyPosition(false);
	}
	else if (time > endTime)
	{
		if (_boss2.getPosition().Y > -300)
		{
			_boss2.setPosition(_boss2.getPosition().X, _boss2.getPosition().Y - 10);
		}
	}

	_boss2.update(time);

	//»∞º∫»≠∞° æ»µ∆¥¬µ• ≥™ø» 
	if (time > startTime && time < endTime)
	{
		if (_boss2.getIsReadyPosition())
		{
			if (_boss2.getPosition().Y > WINSIZE_Y - 200)
			{
				int tempCount = 0;
				for (int i = 0; i < 8; i++)
				{
					if (!_rectShape[i].getIsActive() && time < endTime)
					{
						if (tempCount > 1) break;
						_rectShape[i].ResetPositionRc(GPRectFMakeCenter(100, 100), _boss2.getPosition().X, _boss2.getPosition().Y, 0, false, 5, time, 5000, endTime, 0);
						_rectShape[i].setImageKey("≈È¥œ");
						_rectShape[i].setLocalAngle(tempCount * 90 + 45);
						_rectShape[i].setSpeed(10);
						_rectShape[i].setSize(1);
						_rectShape[i].setAddAngle(0.3f);
						tempCount++;
					}
				}
			}
		}


	}
	for (int i = 0; i < 15; i++)
	{
		if (_rectShape[i].getIsActive())
		{
			if (_boss2.getIsReadyPosition())
			{
				if (_rectShape[i].getPosition().X - 140 < 0 || _rectShape[i].getPosition().X + 140 > WINSIZE_X)
				{
					_rectShape[i].addDirectionX();
				}
				if (_rectShape[i].getPosition().Y - 140 < 0 || _rectShape[i].getPosition().Y + 140 > WINSIZE_Y)
				{
					_rectShape[i].addDirectionY();
				}
			}

			_rectShape[i].setPosition(
				cosf(_rectShape[i].getLocalAngle()* (PI / 180) + (_rectShape[i].getDirection().xDir * PI)) * _rectShape[i].getSpeed() + _rectShape[i].getPosition().X,
				-sinf(_rectShape[i].getLocalAngle()* (PI / 180) + (_rectShape[i].getDirection().yDir * PI)) * _rectShape[i].getSpeed() + _rectShape[i].getPosition().Y);
		}
		_rectShape[i].update(time);
	}

}

void MapPatternController::bossRotateRectPattern(int time, int startTime, int endTime)
{
	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	if (time == startTime)
	{
		_boss.setIsActive(true);
		_boss.setTime(time);
		_boss.setActiveTime(endTime - startTime + 10000);
		_boss.setPosition(WINSIZE_X / 2, -300);
		_boss.setImageKey("boss_smile");
		_boss.setSize(1);
		_boss.setTimeOffset(0);
		_boss.setAngle(0);
		_boss.setIsReadyPosition(false);
	}
	else if (time > startTime && time < endTime)
	{

		if (!_boss.getIsReadyPosition())
		{
			_boss.setPosition(WINSIZE_X / 2, _boss.getPosition().Y + 10);
			if (_boss.getPosition().Y > WINSIZE_Y / 2)
			{
				_boss.setAddAngle(0.03f);
				_boss.setIsReadyPosition(true);
			}
		}
		else if (_boss.getAngle() < -0.2f)
		{
			_boss.setAddAngle(0.005f);
		}
		else if (_boss.getAngle() > 0.2f)
		{
			_boss.setAddAngle(-0.005f);
		}

	}
	else if (time == endTime)
	{
		_boss.setAddAngle(0);
		_boss.setAngle(0);
		_boss.setIsReadyPosition(false);

	}
	else if (time > endTime)
	{
		_boss.setIsReadyPosition(false);
		if (_boss.getPosition().Y < WINSIZE_Y + 300)
			_boss.setPosition(_boss.getPosition().X, _boss.getPosition().Y + 10);

	}

	_boss.update(time);


	if (time > startTime && time < endTime)
	{
		if (_boss.getIsReadyPosition())
		{
			if (time % 5 == 0)
			{
				for (int i = 0; i < BLOCK2_SIZE; i++)
				{
					if (!_rectBlockNotRotate2[i].getIsActive())
					{
						_rectBlockNotRotate2[i].ResetPositionRc(GPRectFMakeCenter(100, 100), _boss.getPosition().X, -400, 0, true, 5, time, endTime, endTime, 0);
						_rectBlockNotRotate2[i].setLocalAngle(PI / 2);
						_rectBlockNotRotate2[i].setAddAngle(0.2f);
						_rectBlockNotRotate2[i].setSpeed(20);
						_rectBlockNotRotate2[i].setIsFrash(true);
						break;
					}
				}
			}
		}


	}
	for (int i = 0; i < BLOCK2_SIZE; i++)
	{
		if (_rectBlockNotRotate2[i].getIsActive())
		{
			if (_boss.getIsReadyPosition())
			{
				if (!_rectBlockNotRotate2[i].getIsReadyPosition())
				{
					_rectBlockNotRotate2[i].setPosition(_rectBlockNotRotate2[i].getPosition().X, _rectBlockNotRotate2[i].getPosition().Y + 10);

					if (_rectBlockNotRotate2[i].getPosition().Y > WINSIZE_Y / 2 - 400)
					{
						_rectBlockNotRotate2[i].setIsReadyPosition(true);
					}
				}
				else if (time < endTime)
				{
					_rectBlockNotRotate2[i].setLocalAngle(_rectBlockNotRotate2[i].getLocalAngle() + 0.02f);
					_rectBlockNotRotate2[i].setPosition(
						cosf(_rectBlockNotRotate2[i].getLocalAngle()) * 400 + WINSIZE_X / 2,
						-sinf(_rectBlockNotRotate2[i].getLocalAngle()) * 400 + WINSIZE_Y / 2);
				}

			}
			else if (time > endTime)
			{
				_rectBlockNotRotate2[i].setLocalAngle(_rectBlockNotRotate2[i].getLocalAngle() + 0.02f);
				_rectBlockNotRotate2[i].setPosition(
					_rectBlockNotRotate2[i].getPosition().X + cosf(_rectBlockNotRotate2[i].getLocalAngle()) * 20,
					_rectBlockNotRotate2[i].getPosition().Y + -sinf(_rectBlockNotRotate2[i].getLocalAngle()) * 20);
			}

		}
		_rectBlockNotRotate2[i].update(time);
	}
}

void MapPatternController::wavePattern(int time, int startTime, int endTime)
{

	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	_waveCount++;
	if (time > startTime && time < endTime)
	{

		if (time % 2 == 0)
		{
			for (int i = 0; i < BLOCK2_SIZE; i++)
			{
				if (!_rectBlockNotRotate2[i].getIsActive() && time < endTime)
				{
					int tempWH = WINSIZE_Y / 2;
					REAL tx = WINSIZE_X - 200;
					REAL ty = sinf((_waveCount * 3) * (PI / 180)) * tempWH + tempWH;
					_rectBlockNotRotate2[i].ResetPositionRc(RectF(-10, -150, 10, tempWH*0.5), tx, ty, 0, true, 5, static_cast<DWORD>(time), endTime, endTime, 0);
					break;
				}
			}
		}
	}

	for (int i = 0; i < BLOCK2_SIZE; i++)
	{
		if (_rectBlockNotRotate2[i].getIsActive())
		{
			_rectBlockNotRotate2[i].setPosition(
				_rectBlockNotRotate2[i].getPosition().X - 10,
				_rectBlockNotRotate2[i].getPosition().Y);
		}
		_rectBlockNotRotate2[i].update(time);
	}

}

void MapPatternController::bossWavePattern2(int time, int startTime, int endTime)
{

	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	if (time == startTime)
	{
		_boss.setIsActive(true);
		_boss.setTime(time);
		_boss.setActiveTime(endTime - startTime + 10000);
		_boss.setTimeOffset(0);
		_boss.setPosition(WINSIZE_X / 2, -400);
		_boss.setImageKey("boss_angry");
		_boss.setSize(1);
		_boss.setAngle(0);
		_boss.setIsReadyPosition(false);
	}
	else if (time > startTime && time < endTime)
	{
		int tempWH = WINSIZE_Y / 2;
		REAL tx = WINSIZE_X - 200;
		REAL ty = sinf((_waveCount * 3) * (PI / 180)) * tempWH + tempWH;
		_boss.setPosition(tx, ty);

	}
	else if (time == endTime)
	{
		_boss.setAddAngle(0);
		_boss.setAngle(0);
		_boss.setIsReadyPosition(false);
	}
	else if (time > endTime)
	{
		if (_boss.getPosition().Y > -300)
		{
			_boss.setPosition(WINSIZE_X - 200, _boss.getPosition().Y - 10);
		}
	}

	_boss.update(time);

}


void MapPatternController::frashPattern2(int time, int startTime, int endTime)
{
	if (!(time > startTime - 1000 && time < endTime + 10000)) return;

	for (int i = 0; i < WALL_SIZE; i++)
	{
		_rectShape[i].update(time);

		if (time > startTime && time < endTime)
		{
			if (_rectShape[i].getIsActive())
			{
				_rectShape[i].addAngle(0);
			}
			else
			{
				if (time >= _rectShape[i].getTime())
				{
					INT tx = RND->getInt(static_cast<int>(WINSIZE_X / 150) + 1) * 150 + 75;
					INT ty = RND->getInt(static_cast<int>(WINSIZE_Y / 150) + 1) * 150 + 75;
					_rectShape[i].ResetPositionRc(RectF(-75, -75, 150, 150), tx, ty, 600, false, 0, time, 300, endTime, 0);
					_rectShape[i].setMatrix(1, 0, 0, 1, 0, 0);
					_rectShape[i].setIsFrash(true);
				}
			}
		}
	}

}


void MapPatternController::render(Gdiplus::Graphics* g)
{
	g->SetTransform(&_mapMatrix);

	_boss.render(g);
	_boss2.render(g);
	_boss3.render(g);
	_bossBigRect.render(g);

	//block
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		_imgBlock[i].render(g);
	}

	for (int i = 0; i < WALL_SIZE; i++)
	{
		_rectShape[i].render(g);
	}
	for (int i = 0; i < BLOCK2_SIZE; i++)
	{
		_rectBlockNotRotate2[i].render(g);
	}
	for (int i = 0; i < BLOCK3_SIZE; i++)
	{
		_rectBlock3[i].render(g);
	}


}
