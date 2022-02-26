#include "Stdafx.h"
#include "CRectObserverManager.h"
#include "EffectManager.h"
#include "PlayScene.h"
#include "DamageEffectManager.h"

HRESULT CRectObserverManager::init()
{
	_effectManager = new EffectManager;
	_effectManager->init();

	_damageManager = new DamageEffectManager;
	_damageManager->init();
	return S_OK;
}

void CRectObserverManager::release(void)
{
	_vRect.clear();
}

void CRectObserverManager::update(void)
{
	_effectManager->update();
	_damageManager->update();
	getRectFromObserved();
}

void CRectObserverManager::render(void)
{
	_effectManager->render();
	_damageManager->render();
}

void CRectObserverManager::registerObserved(IRectObserved* observed)
{
	_vRect.push_back(observed);
}

void CRectObserverManager::removeObserved(IRectObserved* observed)
{
	_viRect = _vRect.begin();
	for (; _viRect != _vRect.end(); ++_viRect) 
	{
		if (*_viRect == observed) 
		{
			_vRect.erase(_viRect);
			break;
		}
	}
}

void CRectObserverManager::getRectFromObserved()
{
	if (_vRect.size() == 0) return;
	_viRect = _vRect.begin();
	for (; _viRect != _vRect.end(); ++_viRect)
	{
		STObservedData obData;
		obData = (*_viRect)->getRectUpdate();

		_viRectCompare = _vRect.begin();
		for (;_viRectCompare != _vRect.end(); ++_viRectCompare)
		{
			STObservedData obDataCompare;
			obDataCompare = (*_viRectCompare)->getRectUpdate();
			if ((*obData.typeKey) == (*obDataCompare.typeKey)) continue;

			//�� �ǰ� (obData : �� �Ѿ�, Compare : ��)
			if (((*obData.typeKey) == ObservedType::ROCKET_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD) &&
				(*obDataCompare.typeKey) == ObservedType::MINION && !(*obDataCompare.isActive))
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					if (*obData.isActive)
					{
						_damageManager->createDamage((int)(*obData.damage), false,
							(*obDataCompare.rc).left + (((*obDataCompare.rc).right - (*obDataCompare.rc).left) / 2),
							(*obDataCompare.rc).top + (((*obDataCompare.rc).bottom - (*obDataCompare.rc).top) / 2));

						_effectManager->createEffect("effect2", (*obDataCompare.rc));

						(*_viRectCompare)->collideObject(obData);			//���� data�� Active�� false�� ��쿡�� ü�� ����
						(*_viRect)->collideObject(obDataCompare);			//Active�� false�� ��ȯ

					}

					break;
				}
			}

			//�÷��̾� �ǰ� (obData : �� �Ѿ�, Compare : �÷��̾�)
			if ((*obData.typeKey) == ObservedType::MINION_MISSILE &&
				(*obDataCompare.typeKey) == ObservedType::ROCKET)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					(*_viRect)->collideObject(obDataCompare);
					(*_viRectCompare)->collideObject(obData);

					break;
				}
			}

			//Sword �ݰ� (obData : 
			if ((*obData.typeKey) == ObservedType::PLAYER_SWORD &&
				(*obDataCompare.typeKey) == ObservedType::MINION_MISSILE)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					//sword���� ���� �߰�
					(*_viRectCompare)->collideObject(obData);	//���� ��ȯ, type ��ȯ

					break;
				}
			}

			//������ �浹 (obData : ������, Compare : �÷��̾�)
			if ((*obData.typeKey) == ObservedType::ITEM &&
				(*obDataCompare.typeKey) == ObservedType::ROCKET)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					(*_viRect)->collideObject(obDataCompare);
					(*_viRectCompare)->collideObject(obData);

					break;
				}
			}

		}

	}

}

