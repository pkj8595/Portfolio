#pragma once
#include "ISubject.h"
#include "SingletonBase.h" 
/*
IRectObserved를 상속받는 클래스를 등록한다.
등록한 클래스 삭제한다.
내가 원하는 시점에 IRectObserved 상속받은 객체의 함수를 호출시킨다.

IRectObserved >> 플레이어 , 플미, 적미사일, 적
*/
class EffectManager;
class DamageEffectManager;

class CRectObserverManager : public SingletonBase<CRectObserverManager>
{
private:
	//map를 쓰는게 좋지않을까?
	typedef vector<IRectObserved*> vRcObserved;
	typedef vector<IRectObserved*>::iterator viRcObserved;

private:
	vRcObserved  _vRect;
	viRcObserved _viRect;
	viRcObserved _viRectCompare;

	EffectManager* _effectManager;
	DamageEffectManager* _damageManager;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void registerObserved(IRectObserved* observed);
	virtual void removeObserved(IRectObserved* observed);
	virtual void getRectFromObserved();

	void registerEffectManagerAddress(EffectManager* ef) {
		_effectManager = ef;
	}

	CRectObserverManager() {}
	~CRectObserverManager() {}
};

