#include "Stdafx.h"
#include "CRectObserverManager.h"
#include "EffectManager.h"
#include "PlayScene.h"

HRESULT CRectObserverManager::init()
{
	SCENEMANAGER->addScene("Play", new PlayScene);
	return S_OK;
}

void CRectObserverManager::release(void)
{
	_vRect.clear();
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

//동적으로 할당된 객체만 observer패턴으로 가져올 수 있었음.. 
//정적으로 할당된 객체의 정보는 접근할 수 없었음
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

			if ((*obData.typeKey) == ObservedType::ROCKET_MISSILE &&
				(*obDataCompare.typeKey) == ObservedType::MINION)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					(*_viRect)->collideObject();
					(*_viRectCompare)->collideObject();
					_effectManager->createEffect("effect1", collisionRect);
					break;
				}
			}

			if ((*obData.typeKey) == ObservedType::MINION_MISSILE &&
				(*obDataCompare.typeKey) == ObservedType::ROCKET)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					(*_viRect)->collideObject();
					(*_viRectCompare)->collideObject();
					_effectManager->createEffect("effect2", collisionRect);
					break;
				}
			}

		}

	}

}

