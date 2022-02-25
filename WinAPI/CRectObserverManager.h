#pragma once
#include "ISubject.h"
#include "SingletonBase.h" 
/*
IRectObserved�� ��ӹ޴� Ŭ������ ����Ѵ�.
����� Ŭ���� �����Ѵ�.
���� ���ϴ� ������ IRectObserved ��ӹ��� ��ü�� �Լ��� ȣ���Ų��.

IRectObserved >> �÷��̾� , �ù�, ���̻���, ��
*/
class EffectManager;
class DamageEffectManager;

class CRectObserverManager : public SingletonBase<CRectObserverManager>
{
private:
	//map�� ���°� ����������?
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

