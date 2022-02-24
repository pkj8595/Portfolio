#include "Stdafx.h"
#include "CRectObserverManager.h"
#include "EffectManager.h"
#include "PlayScene.h"

HRESULT CRectObserverManager::init()
{
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

					break;
				}
			}

			//Sword 반격
			if ((*obData.typeKey) == ObservedType::ROCKET_MISSILE &&
				(*obDataCompare.typeKey) == ObservedType::MINION_MISSILE)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					(*_viRectCompare)->collideObject();	//각도, type를 바꿔주는 다른 방법(or 함수) 필요.

					break;
				}
			}

		}

	}

}

