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
class Player;

class CRectObserverManager : public SingletonBase<CRectObserverManager>
{
private:
	typedef vector<IRectObserved*> vRcObserved;
	typedef vector<IRectObserved*>::iterator viRcObserved;

	typedef vector<IEventObservered*> vEventObserved;
	typedef vector<IEventObservered*>::iterator viEventObserved;

private:
	vRcObserved  _vRect;
	viRcObserved _viRect;
	viRcObserved _viRectCompare;

	Player* _player;
	vEventObserved _vEvent;
	viEventObserved _viEvent;

	EffectManager* _effectManager;
	DamageEffectManager* _damageManager;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void registerObserved(IRectObserved* observed);
	virtual void removeObserved(IRectObserved* observed);

	virtual void registerPlayer(Player* player);
	virtual void registerEventObserved(IEventObservered* observed);
	virtual void removeEventObserved(IEventObservered* observed);

	virtual void getEventFormObserved();
	virtual void getRectFromObserved();

	void registerEffectManagerAddress(EffectManager* ef) {
		_effectManager = ef;
	}

	CRectObserverManager() {}
	~CRectObserverManager() {}
};

