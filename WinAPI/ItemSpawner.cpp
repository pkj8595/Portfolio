#include "Stdafx.h"
#include "ItemSpawner.h"
#include "Map.h"

//============================
//   ### ItemObject ###
//============================
HRESULT ItemObject::init(void)
{
	return S_OK;
}

HRESULT ItemObject::init(int x, int y, bool isCollider)
{
	_x = (float)x;
	_y = (float)y;
	_isCollider = isCollider;
	_rc = RectMakeCenter(_x, _y, ITEM_OBJ_SIZE, ITEM_OBJ_SIZE);
	_typeKey = ObservedType::ITEM;
	_itemManager = ItemManager::getSingleton();
	_itemIndex = RND->getInt(_itemManager->getItemSize());
	_increaseY = false;
	_isActive = true;
	_moveOffsetTime =_responseTime = _worldTime = TIMEMANAGER->getWorldTime();
	_map = nullptr;
	
	RECTOBSERVERMANAGER->registerObserved(this);
	return S_OK;
}

void ItemObject::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
}

void ItemObject::update(void)
{
	if (TIMEMANAGER->getWorldTime() > _moveOffsetTime)
	{
		_moveOffsetTime = TIMEMANAGER->getWorldTime() + MOVE_OFFSET_TIME;
		if (_increaseY) { _y --; }
		else { _y ++; }
		_rc = RectMakeCenter(_x, _y, ITEM_OBJ_SIZE, ITEM_OBJ_SIZE+20);

		if (TIMEMANAGER->getWorldTime() > _worldTime + CHANGE_DIRECTION)
		{
			_increaseY = !_increaseY;
			_worldTime = TIMEMANAGER->getWorldTime();
		}
	}
	
}

void ItemObject::render(void)
{
	//RectangleMakeToRECT(getMemDC(), _rc);
	_itemManager->getItemIndexRender(getMemDC(), _itemIndex, _rc.left, _rc.top);
}

STObservedData ItemObject::getRectUpdate()
{
	STObservedData temp;
	temp.typeKey = &_typeKey;
	temp.number = &_itemIndex;
	temp.isActive = &_isCollider;
	temp.rc = &_rc;
	temp.angle = &_responseTime;

	return temp;
}

void ItemObject::collideObject(STObservedData obData)
{
	if (_isCollider)
	{
		if (TIMEMANAGER->getWorldTime() > _responseTime + 1.0f)
		{
			_isActive = false;
		}
	}
}

//============================
//   ### ItemSpawner ###
//============================

ItemSpawner::ItemSpawner()
{
	init();
}

ItemSpawner::~ItemSpawner()
{
	release();
}


HRESULT ItemSpawner::init(void)
{
	_currentMap = nullptr;
	return S_OK;
}

void ItemSpawner::release(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj != _vItemObj.end(); ++_viItemObj)
	{
		(*_viItemObj)->release();
	}
	_vItemObj.clear();
}

void ItemSpawner::update(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj != _vItemObj.end(); ++_viItemObj)
	{
		if (*_currentMap == (*_viItemObj)->getMap())
		{
			(*_viItemObj)->update();
			if (!(*_viItemObj)->getIsActive())
			{
				(*_viItemObj)->release();
				_vItemObj.erase(_viItemObj);
				break;
			}
		}
	}
}

void ItemSpawner::render(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj != _vItemObj.end(); ++_viItemObj)
	{
		if (*_currentMap == (*_viItemObj)->getMap())
		{
			(*_viItemObj)->render();
		}
	}
}

int ItemSpawner::createItem(int x, int y, bool isCollider)
{
	ItemObject* itemObj = new ItemObject;
	itemObj->init(x, y, isCollider);
	itemObj->setMap(*_currentMap);
	_vItemObj.push_back(itemObj);
	return itemObj->getItemIndex();
}

void ItemSpawner::clearItem(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj != _vItemObj.end(); ++_viItemObj)
	{
		(*_viItemObj)->release();
	}
	_vItemObj.clear();
}

int ItemSpawner::createItemMapInit(int x, int y, bool isCollider, Map* map)
{
	ItemObject* itemObj = new ItemObject;
	itemObj->init(x, y, isCollider);
	itemObj->setMap(map);
	_vItemObj.push_back(itemObj);
	return itemObj->getItemIndex();
}

void ItemSpawner::setCurrentMap(Map** cmap)
{
	_currentMap = cmap;
}

