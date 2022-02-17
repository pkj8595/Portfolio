#include "Stdafx.h"
#include "GDIplusTest.h"

HRESULT GDIplusTest::init(void)
{
	_g = new Gdiplus::Graphics(getMemDC());
	_g->SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeNearestNeighbor);
	_g->SetCompositingQuality(CompositingQuality::CompositingQualityHighSpeed);
	_g->SetPixelOffsetMode(PixelOffsetMode::PixelOffsetModeHighSpeed);
	_g->SetSmoothingMode(SmoothingMode::SmoothingModeHighSpeed);

	TEMPSOUNDMANAGER->addMp3FileWithKey("Ways", "Resource/Sound/Milky-Ways.mp3");
	
	_time = 0;
	_pauseTime = 0;
	_addTime = 0;
	_timeStart = GetTickCount();
	_baseMatrix.SetElements(1,0,0,1,0,0);
	_gameStop = false;

	_mapController.init();

	return S_OK;
}

void GDIplusTest::release(void)
{
	SAFE_DELETE(_g);
}

void GDIplusTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) 
	{
		_gameStop = !_gameStop;
	}
	if (!_gameStop)
	{
		TEMPSOUNDMANAGER->playSoundWithKey("Ways");
	}
	else
	{
		TEMPSOUNDMANAGER->stopMp3WithKey("Ways");
		_pauseTime = GetTickCount() - (_timeStart+ _time);
		return;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2)) 
	{
		_addTime += 2000;
	}

	_time = GetTickCount() - _timeStart - _pauseTime+ _addTime;
	_cplayer.update(_time);
	_mapController.update(_time);



	//player pixel color collider
	if (_time % 3 == 0)
	{
		int py_start = _cplayer.getPoint().y - 10;
		int px_start = _cplayer.getPoint().x - 10;
		int py_end = _cplayer.getPoint().y + 10;
		int px_end = _cplayer.getPoint().x + 10;

		for (int y = py_start; y < py_end; y += 2)
		{
			for (int x = px_start; x < px_end; x += 2)
			{
				COLORREF color = GetPixel(getMemDC(), x, y);
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);
				if (r == 255 && g == 32 && b == 113)
				{
					_cplayer.beAttacked(_time);
				}
			}
		}
	}

	
}

void GDIplusTest::render(HDC hdc)
{
	TCHAR num[255];
	wsprintf(num, "%d",_time);
	TextOut(getMemDC(), 0, 0, num, lstrlen(num));
	_g->SetTransform(&_baseMatrix);

	//player
	_cplayer.render(_g);
	_mapController.render(_g);

}
