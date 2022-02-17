#pragma once
#include "MainGame.h"

#define _USE_MATH_DEFINES // 메스 위에 잡아야함
#include "math.h"

//삼각함수


	//point 사용하는게 좋음
struct STAR
{
	float x;
	float y;
};

struct ROTATE_RECT
{
	POINT p11;
	POINT p12;
	POINT p21;
	POINT p22;
};


class rotateRect : public Scene_inter
{


	//프로젝트의 대리자 
	private:
		float _radian;
		float _degree;

		SYSTEMTIME _st;
		//스타
		HPEN	_currentPen;
		STAR _star[5];
		//시계
		POINT _h;
		POINT _m;
		POINT _s;
		POINT _clockText[12];

		POINT _rcPoint;
		RECT _rc;

		POINT _roRcPoint;
		ROTATE_RECT _roRc;
		float _rcDegree;

		POINT directionVector;
		POINT directionVector2;

		float x1;
		float y1;
		float x2;
		float y2;
		float z1;
		float z2;
		float r1;
		float r2;

		RECT _roRect;
		POINT rP;

		int _count;

		bool xDir;
		bool yDir;

		RECT _roRect0111;
		POINT _roPt0111;
		float _angle0111;

	public:
		virtual HRESULT init(void);
		virtual void release(void);
		virtual void update(void);	//삼각함수는 update가 중요	
		virtual void render(HDC hdc);

		void RotateLineMake(POINT point, float radius, float degree);

		rotateRect() {}
		virtual ~rotateRect() {}
};


/*
오망성의 특징 각도가 같고 중점은 가운데있다.
그렇다면 꼭지점과의 거리가 같고
추출 할 수 있다면 편하게 그릴수 있을까?
*/

/*
정의 : 수학에서의 삼각함수는 직각 삼각형의 각을 직각 삼각형 변들의 길이 비로 나타내는 함수 (직각 삼각형일때문 성립)

-게임에서 : 각도를 이용할때 필요하다.
	ㄴ	발사체의 각도나 캐릭터의 대각선 이동 등등...

-사인(sin)
: sin은 제일 긴 빗변과 높이(대변)의 배율을 구해주는 함수

-코사인(cos)
:빗변과 밑변의 비율을 계산해주는 함수

-탄젠트(tan)
:직각 삼각형에서 어떠한 각도를 넣었을 때 밑변과 대변의 비율을 구해준다.

=============================================================

 - API 에서는 윈도우 좌표계를 사용한다. ->일반적으로 사용하는 데카르트 좌표계와는 달리 Y축이 반대로 되어있기 때문에 Y축 좌표를 구할때는 sin앞에 "마이너스"를 붙여야 한다.

 ============================================================

 - 호도법 : 컴퓨터는 각도를 인식할 때 도를 사용할 수 없다.
	ㄴ	각도를 나타내는 표현 방법 중 하나로 호의 길이로 각도를 나타낸다.
	ㄴ	PI를 사용해 180도 각도를 표시하는 것 -> 호도법
	ㄴ	반지름의 길이와 같은 호에 대한 중심각을 1호도(라디안)라고 부른다.

 - Radian : 호도법을 표기할 때 사용하는 단위
	ㄴ	반지름과 호의 길이가 같은 값을 1라디안으로 정의한다.
	ㄴ	1 라디안 = 57.3..도

 - Degree : 일반적으로 사용하는 각의 단위(각도)
	ㄴ	도수법 / 각도 표기라고 불린다.
	ㄴ	한바퀴를 360도로 정의한다.

 - 60분법 : 원의 둘레를 360등분하여 각의 크기를 나타내는 방법

 PI (원주율 : 3.14)
 원의 둘레 : 2* PI * 반지름
 원의 넓이 : 반지름 * 반지름 * PI

 ## PI의 라디안 값은 180도

 180 Degree	=	PI Radian
 1 Degree	=	PI /180 radian
 x Degree	=	x * PI / 180 Radian

 PI Radian	=	180 Degree
 1 Radian	=	180 / PI Degree
 x Radian	=	x * 180 / PI Degree


 ## 부채꼴 모양에서 반지름 , 호 , 중심각 3가지중 2가지를 알면 다른 한가지를 구할 수 있다.

 - 두 점 사아의 거리
 -> 두점을 안다. -> 서로의 거리를 안다. -> 목표지점에서 시작지점을 뺀다.
	ㄴ End -> Start = 두 점 사이의 거리

- 위 공식으로 각점 (X,Y)사이의 변이량을 구한다.
	ㄴ DeltaX, DeltaY

- 대각선 (빗변)의 거리(피타고라스의 정리)
	ㄴ Distance = sqrt (DeltaX * Delta X + DeltaY * DeltaY)
	ㄴ sqrt() : X의 제곱근을 구해주는 함수

- 각을 구한다.
- float angle = acos(DeltaX / Distance); //아크 -> 역삼각함수
	ㄴ 역삼각 함수 : 삼각 함수의 결과 값을 넣어서 각도 계산
		ㄴ a or arc 붙으면 역삼각 함수를 의미한다.
	ㄴ 삼각 함수 : 각도를 넣어서 계산

- 각도에 대한 변이향을 구한다.
	ㄴ float DeltaX = cos(radian) * Distance (이동량(반지름));
	ㄴ float DeltaY = -sin(radian) * Distance (이동량(반지름));

- x 축 좌표 구하기
-> x = cos(각도 * PI / 180) * 속도;

-y 축 좌표 구하기
-> y축 = -sin(각도 * PI / 180) * 속도;



*/

