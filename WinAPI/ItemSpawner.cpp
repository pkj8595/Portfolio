#include "Stdafx.h"
#include "ItemSpawner.h"
#include "Map.h"
#include "ItemManager.h"

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
	_isChest = false;
	_moveOffsetTime =_responseTime = _worldTime = TIMEMANAGER->getWorldTime();
	_map = nullptr;
	_isCurrentMap = false;
	
	RECTOBSERVERMANAGER->registerObserved(this);
	return S_OK;
}

HRESULT ItemObject::init(int x, int y, bool isCollider, int itemIndex)
{
	_x = (float)x;
	_y = (float)y;
	_isCollider = isCollider;
	_rc = RectMakeCenter(_x, _y, ITEM_OBJ_SIZE, ITEM_OBJ_SIZE);
	_typeKey = ObservedType::ITEM;
	_itemManager = ItemManager::getSingleton();
	_itemIndex = itemIndex;
	_increaseY = false;
	_isActive = true;
	_isChest = false;
	_moveOffsetTime = _responseTime = _worldTime = TIMEMANAGER->getWorldTime();
	_map = nullptr;
	_isCurrentMap = false;

	RECTOBSERVERMANAGER->registerObserved(this);
	return S_OK;
}

HRESULT ItemObject::initChest(int x, int y, bool isCollider, int itemIndex)
{
	_x = (float)x;
	_y = (float)y;
	_isCollider = isCollider;
	_rc = RectMakeCenter(_x, _y, BIGITEM_OBJ_SIZE, BIGITEM_OBJ_SIZE);
	_typeKey = ObservedType::ITEM;
	_itemManager = ItemManager::getSingleton();
	_itemIndex = itemIndex;
	_increaseY = false;
	_isActive = true;
	_isChest = true;
	_moveOffsetTime = _responseTime = _worldTime = TIMEMANAGER->getWorldTime();
	_map = nullptr;
	_isCurrentMap = false;

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
		
		if (!_isChest)_rc = RectMakeCenter(_x, _y, ITEM_OBJ_SIZE, ITEM_OBJ_SIZE+20);
		else  RectMakeCenter(_x, _y, BIGITEM_OBJ_SIZE, BIGITEM_OBJ_SIZE + 20);

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
	if(!_isChest)_itemManager->getItemIndexRender(getMemDC(),_itemIndex, _rc.left, _rc.top);
	else _itemManager->getBigItemIndexRender(getMemDC(), _itemIndex, _rc.left, _rc.top);
}

STObservedData ItemObject::getRectUpdate()
{
	STObservedData temp;
	temp.typeKey = &_typeKey;
	temp.number = &_itemIndex;
	temp.isActive = &_isCollider;
	temp.rc = &_rc;
	temp.angle = &_responseTime;
	temp.magic = &_isCurrentMap;

	return temp;
}

void ItemObject::collideObject(STObservedData obData)
{
	if (_isCollider && _isCurrentMap)
	{
		if (TIMEMANAGER->getWorldTime() > _responseTime + 1.0f)
		{
			_isActive = false;
			release();
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
			(*_viItemObj)->setIsCurrentMap(true);
			(*_viItemObj)->update();
			if (!(*_viItemObj)->getIsActive())
			{
				(*_viItemObj)->release();
				_vItemObj.erase(_viItemObj);
				break;
			}
		}
		else
		{
			(*_viItemObj)->setIsCurrentMap(false);
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

void ItemSpawner::clearItem(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj != _vItemObj.end(); ++_viItemObj)
	{
		(*_viItemObj)->release();
	}
	_vItemObj.clear();
}


int ItemSpawner::createItem(int x, int y, bool isCollider)
{
	ItemObject* itemObj = new ItemObject;
	itemObj->init(x, y, isCollider);
	itemObj->setMap(*_currentMap);
	_vItemObj.push_back(itemObj);
	return itemObj->getItemIndex();
}
int ItemSpawner::createItem(int x, int y, bool isCollider, int itemIndex)
{
	ItemObject* itemObj = new ItemObject;
	itemObj->init(x, y, isCollider,itemIndex);
	itemObj->setMap(*_currentMap);
	_vItemObj.push_back(itemObj);
	return itemObj->getItemIndex();
}
int ItemSpawner::createChestItem(int x, int y, bool isCollider)
{
	ItemObject* itemObj = new ItemObject;
	itemObj->initChest(x, y, isCollider, RND->getFromIntTo(14,34));
	itemObj->setMap(*_currentMap);
	_vItemObj.push_back(itemObj);
	return itemObj->getItemIndex();
}

ItemObject* ItemSpawner::createItemMapInit(int x, int y, bool isCollider, Map* map)
{
	ItemObject* itemObj = new ItemObject;
	itemObj->init(x, y, isCollider);
	itemObj->setMap(map);
	_vItemObj.push_back(itemObj);
	return itemObj;
}

ItemObject* ItemSpawner::createItemMapInit(int x, int y, bool isCollider)
{
	ItemObject* itemObj = new ItemObject;
	itemObj->init(x, y, isCollider);
	itemObj->setMap(*_currentMap);
	_vItemObj.push_back(itemObj);
	return itemObj;
}

void ItemSpawner::removeItem(ItemObject * itemObject)
{
}

void ItemSpawner::setCurrentMap(Map** cmap)
{
	_currentMap = cmap;
}

