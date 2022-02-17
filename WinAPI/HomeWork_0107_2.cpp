#include "Stdafx.h"
#include "HomeWork_0107_2.h"

HRESULT HomeWork_0107_2::init(void)
{
	_cannon.angle = 90;		
	_cannon.length = 80;
	_cannon.radius = 50;
	_cannon.center.x = WINSIZE_X / 2;
	_cannon.center.y = WINSIZE_Y;

	for (int i = 0; i < 30;i++) 
	{
		_bullet[i].isFire = false;
	}

	return S_OK;
}

void HomeWork_0107_2::release(void)
{
}

void HomeWork_0107_2::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) 
		_cannon.angle -= 3;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) 
		_cannon.angle += 3;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) 
	{
		Fire();
	}

	//포신 끝점의 xy좌표
	_cannon.cannonEnd.x = cosf(_cannon.angle*(M_PI/180))*_cannon.length + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle*(M_PI / 180))*_cannon.length + _cannon.center.y;


	//충돌로직
	for (int i = 0; i < 30; i++)
	{
		if (!_bullet[i].isFire) continue;

		//y가 윈도우창과 붙이쳤을때
		if (_bullet[i].rc.bottom >= WINSIZE_Y ||
			_bullet[i].rc.top <= 0)
		{
			_bullet[i].yDir++;
		}

		//x가 윈도우창과 붙이쳤을때
		if (_bullet[i].rc.right >= WINSIZE_X ||
			_bullet[i].rc.left <= 0)
		{
			_bullet[i].xDir++;
		}

		float aX =0;
		float aY =0;
		float bX =0;
		float bY =0;
		float distance =0;
		for (int j = 0; j < 30; j++)
		{
			if (!_bullet[j].isFire || i == j) continue;
			//중심점 계산
			aX = (_bullet[i].rc.left + _bullet[i].rc.right) / 2;
			aY = (_bullet[i].rc.top + _bullet[i].rc.bottom) / 2;
			bX = (_bullet[j].rc.left + _bullet[j].rc.right) / 2;
			bY = (_bullet[j].rc.top + _bullet[j].rc.bottom) / 2;
			distance = sqrt(((aX - bX) *(aX - bX)) + ((aY - bY) *(aY - bY)));
			//원끼리의 충돌시
			if ((BULLET_RADIUS + BULLET_RADIUS) >= distance)
			{
				float intersectionDistance = (BULLET_RADIUS + BULLET_RADIUS) - distance;
				if (intersectionDistance >0)
				{
					_bullet[i].rc.left -= cosf( ((_bullet[i].xDir * M_PI) + (_bullet[i].angle)*(PI / 180)) ) * intersectionDistance/2;
					_bullet[i].rc.top -= -sinf(((_bullet[i].yDir * M_PI) + (_bullet[i].angle)*(PI / 180))) * intersectionDistance/2;
					_bullet[i].rc.right -= cosf(((_bullet[i].xDir * M_PI) + (_bullet[i].angle)*(PI / 180))) * intersectionDistance/2;
					_bullet[i].rc.bottom -= -sinf(((_bullet[i].yDir * M_PI) + (_bullet[i].angle)*(PI / 180))) * intersectionDistance/2;
				}

				//공의 반사각 입사각 계산
				ReflectionCircle( i, aY, bY, aX, bX);

				//각도 초기화
				_bullet[i].xDir = 0;
				_bullet[i].yDir = 0;
			}
		}
	}

	//총알 이동로직
	for (int i = 0; i < 30; i++)
	{
		if (!_bullet[i].isFire) continue;
		/*
		_bullet[i].rc.left += 10 * cosf(_bullet[i].angle);
		_bullet[i].rc.top += 10 * -sinf(_bullet[i].angle);
		_bullet[i].rc.right += 10 * cosf(_bullet[i].angle);
		_bullet[i].rc.bottom += 10 * -sinf(_bullet[i].angle);
		*/

		/*
		//원이 계속 작아진다. 벽에 붙이칠때마다 x와 y의 각도가 차이가 나서 그런듯하다. 
		>>회전행렬의 덧셈 공식이 이래서 필요한가 싶다.
		>>혹시나 싶어서 각도를 통일하고 쏘아봤는데 계속 찌그러 진다.
		>> 파이가 무리수이기때문에 소수점 아래가 많이 잘려나가서 그런걸까? 
		>>angle 값을 0 ~ 360 사이의 값으로 만들어주면 찌그러짐이 사라지지 않을까? -> 실패 어차피 앵글값은 늘든 줄든 1~-1사이의 값이다.
		>>ANGLE 값이 같든말든 벽에 붙이쳤을때 찌그러진다. ??왜 찌그러지지?
			ㄴ RECT의 멤버가 LONG 정수형이라서 소수점 단위가 버려지고 계산됨.
			ㄴ FLOAT RECT 타입을 만들어서 계산하니 찌그러짐은 사라짐
		*/

		//모듈러 연산은 정수형에서만 가능하다. 
		//_bullet[i].angle %= (M_PI * 2);


		_bullet[i].rc.left += BULLET_SPEED * cosf( ((_bullet[i].xDir * M_PI) + (_bullet[i].angle)*(PI/180)) );
		_bullet[i].rc.top += BULLET_SPEED * -sinf( ((_bullet[i].yDir * M_PI) + (_bullet[i].angle)*(PI / 180)) );
		_bullet[i].rc.right += BULLET_SPEED * cosf( ((_bullet[i].xDir * M_PI) + (_bullet[i].angle)*(PI / 180)) );
		_bullet[i].rc.bottom += BULLET_SPEED * -sinf( ((_bullet[i].yDir * M_PI) + (_bullet[i].angle)*(PI / 180)) );
	}
	
}



void HomeWork_0107_2::render(HDC hdc)
{
	//포신 그리기 
	LineMake(hdc, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	EllipseMakeCenter(hdc, _cannon.center.x, _cannon.center.y, _cannon.radius, _cannon.radius);

	for (int i = 0; i < 30; i++)
	{
		if (!_bullet[i].isFire) continue;
		Ellipse(hdc, _bullet[i].rc.left,
			_bullet[i].rc.top,
			_bullet[i].rc.right,
			_bullet[i].rc.bottom);

		//debug
		_stprintf_s(_bullet[i].teststr, "degree : %.0f x : %d y : %d" , _bullet[i].angle, _bullet[i].xDir%2 , _bullet[i].yDir % 2);
		TextOut(hdc, _bullet[i].rc.left-20, _bullet[i].rc.top + 20, _bullet[i].teststr, strlen(_bullet[i].teststr));

	}
}

void HomeWork_0107_2::ReflectionCircle(int index, float aY, float bY, float aX, float bX)
{
	float currentAngle;
	float seta;

	//현재 움직이는 각도 구하기
	currentAngle = atan2f(
		sinf(((_bullet[index].yDir * M_PI) + (_bullet[index].angle))),
		cosf(((_bullet[index].xDir * M_PI) + (_bullet[index].angle)))
	);

	currentAngle *= (180 / M_PI);	//디그리변환
	seta = atan2f((aY - bY), (aX - bX))* (180 / M_PI);//디그리변환
	
	//입사각과 반사각의 합계를 현재 각도에서 빼주기
	_bullet[index].angle = currentAngle - (2 * (90 - ( seta- currentAngle )));
	
}

void HomeWork_0107_2::Fire(void)
{
	for (int i = 0; i < 30; i++)
	{
		if (_bullet[i].isFire) continue; 
		_bullet[i].isFire = true;
		_bullet[i].yDir = 0;
		_bullet[i].xDir = 0;
		_bullet[i].angle = _cannon.angle;
		_bullet[i].rc = FLOAT_RECT{ 
							_cannon.cannonEnd.x - BULLET_RADIUS,
							_cannon.cannonEnd.y - BULLET_RADIUS,
							_cannon.cannonEnd.x + BULLET_RADIUS,
							_cannon.cannonEnd.y + BULLET_RADIUS 
							};
		break;
	}
}

