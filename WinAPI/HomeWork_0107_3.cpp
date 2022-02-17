#include "Stdafx.h"
#include "HomeWork_0107_3.h"


HRESULT HomeWork_0107_3::init(void)
{
	_cannon.angle = PI / 2;		// 3.14 /2      1.78 라디안 = 90디그리 
	_cannon.length = 80;
	_cannon.radius = 50;
	_cannon.center.x = WINSIZE_X / 2;
	_cannon.center.y = WINSIZE_Y;
	_cannon.cannonAngleStart = 30 * (PI / 180);
	_cannon.cannonAngleEnd = 150 * (PI / 180);

	return S_OK; 
}

void HomeWork_0107_3::release(void)
{
}

void HomeWork_0107_3::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _cannon.angle -= 0.04f;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _cannon.angle += 0.04f;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fire();
	};
	GetSystemTime(&_st);


	//자동포탑
	_count++;
	_cannon.angle += (_cannon.dir ? 0.05f : -0.05f);
	if (_count % 5 == 0)
	{
		//fire();

		if (_cannon.angle < _cannon.cannonAngleStart || _cannon.angle > _cannon.cannonAngleEnd)
		{
			_cannon.dir = (_cannon.dir ? false : true);
		}
	}

	//포신 끝점의 xy좌표
	_cannon.cannonEnd.x = cosf(_cannon.angle)*_cannon.length + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle)*_cannon.length + _cannon.center.y;



	for (int i = 0; i < 30; i++)
	{
		if (!_bullet[i].isFire) continue;

		//사이드 벽 팅기기
		if (_bullet[i].pt.x - _bullet[i].radius < 0 ||
			_bullet[i].pt.x + _bullet[i].radius > WINSIZE_X)
		{
			_bullet[i].xDir++;
		}

		if (_bullet[i].pt.y + _bullet[i].radius >= WINSIZE_Y)
		{
			//공중체류시간 초기화
			_bullet[i].airResidenceTime = 0;
			_bullet[i].isAirResidence = false;
			_bullet[i].pt.y = WINSIZE_Y - _bullet[i].radius;
		}
		

		//프레임?당
		_bullet[i].airResidenceTime++;

		//공중에 체류 중이라면
		//좀더 자연스럽게 떨어지면 좋겠는데... x는 마찰로..
		if(_bullet[i].isAirResidence)
		{
			_bullet[i].pt.x += 8 * cosf((_bullet[i].xDir * M_PI) + _bullet[i].angle);
			_bullet[i].pt.y += 8 * -sinf((_bullet[i].yDir * M_PI) + _bullet[i].angle);

			_bullet[i].pt.y += (0.098 * _bullet[i].airResidenceTime);
		}
	}

	

}

void HomeWork_0107_3::render(HDC hdc)
{
	//포신 그리기 
	LineMake(hdc, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	EllipseMakeCenter(hdc, _cannon.center.x, _cannon.center.y, _cannon.radius, _cannon.radius);

	for (int i = 0; i < 30; i++)
	{
		if (!_bullet[i].isFire) continue;
		Ellipse(hdc, _bullet[i].pt.x-_bullet[i].radius,
			_bullet[i].pt.y - _bullet[i].radius,
			_bullet[i].pt.x + _bullet[i].radius,
			_bullet[i].pt.y + _bullet[i].radius);
	}

	char testTimestr[124];
	wsprintf(testTimestr, "time : %d", _st.wMilliseconds);
	TextOut(hdc, 0, 0, testTimestr, strlen(testTimestr));
}
void HomeWork_0107_3::fire(void)
{
	for (int i = 0; i < 30; i++)
	{
		if (_bullet[i].isFire) continue; 
		_bullet[i].isFire = true;
		_bullet[i].angle = _cannon.angle;
		_bullet[i].radius = 20;
		_bullet[i].pt = FLOAT_POINT1{ static_cast<float>(_cannon.cannonEnd.x) , static_cast<float>(_cannon.cannonEnd.y) };
		_bullet[i].yDir = 0;
		_bullet[i].xDir = 0;
		_bullet[i].isAirResidence = true;		//공중체류 중?
		_bullet[i].airResidenceTime = 0;		//공중체류 중?
		break;
	}
}