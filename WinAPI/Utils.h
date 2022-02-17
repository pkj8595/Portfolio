#pragma once
//===================================
//# Utils # (간소화 시키고 싶은 로직,수학적 기능들을 모아둔 곳)
//===================================

//반올림(6자리까지밖에 안됨)에 오차가 생길수 있음. 
#define DEG_TO_RAD		0.017453f
#define PI				3.141592653f
#define PI_2			6.283185308f

//공학과 수학의 구세주
#define FLOAT_EPSILON	0.001f
//실수를 정수형으로 반환
#define FLOAT_TO_INT	static_cast<int>(f1+FLOAT_EPSILON)
//두 실수가 같은지 비교
//ㄴ fabs는 소수점 차의 절대값 반환 (abs->int)
#define FLOAT_EQUAL(f1,f2) (fabs(f1-f2)<= FLOAT_EPSILON)

/*
부동소수점 -> 부동소수점은 실수를 정확하게 표현할 수 없다.
 why -> 실수는 수학적으로 무한하다. -> 무한한 실수를 유한한 비트로 표현하려다 보니까
ㄴ 컴퓨터는 어쩔수없이 근사값으로 표현한다.
2d 에선 사람이 크게 인식을 못하지만 3d좌표계에선 전혀 다른 결과가 발생한다.
ㄴ 근사값에 주 오류 원인 - Rounding Error 
반올림 오차 0.0009만큼 움직이면 좋겠다. 
컴퓨터는 근사값으로 표현해서 0.001이 된다. 
근사값을 방지하고자 쓰는게 앱실론를 쓴다.

쿼터니언 
오일러 앵글

*/

namespace MY_UTIL 
{
	float getDistance(float startX,float startY, float endX,float endY);
	float getAngle(float startX, float startY, float endX, float endY);
}
