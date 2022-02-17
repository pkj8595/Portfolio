#include "Stdafx.h"
#include "Tilemap.h"

Tilemap::Tilemap():_isActive(false)
{
}

HRESULT Tilemap::init(int tileMapSize)
{
	if (tileMapSize <= 0) return S_FALSE;
	if (tileMapSize > TILE_MAP_MAX) _tileMapSize = TILE_MAP_MAX;
	else _tileMapSize = tileMapSize;

	IMAGEMANAGER->addImage("dino1", "Resource/Images/TileMap/dino1.bmp", 150, 150, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dino2", "Resource/Images/TileMap/dino2.bmp", 150, 150, false, RGB(255, 0, 255));

	int tempSqr = (int)sqrt(_tileMapSize);

	for (int i =0; i < _tileMapSize; i++)
	{
		int tempY = (int)i / tempSqr;
		int tempX = (int)i % tempSqr;

		TileMapObject tileMapObject;
		ZeroMemory(&tileMapObject, sizeof(TileMapObject));
		tileMapObject.init("", RectMake(tempX*TILE_MAP_RECT_SIZE,
								tempY*TILE_MAP_RECT_SIZE,
								TILE_MAP_RECT_SIZE,
								TILE_MAP_RECT_SIZE), i);
		_vMap.push_back(tileMapObject);
	}

	_vMap.at(RND->getInt(_tileMapSize)).setImgStr("dino1");
	_vMap.at(RND->getInt(_tileMapSize)).setImgStr("dino2");

	_isClicked = false;

	return S_OK;
}

void Tilemap::release(void)
{
	for (_viMap = _vMap.begin(); _viMap != _vMap.end(); ++_viMap)
	{
		_viMap->release();
	}
	_vMap.clear();
}

void Tilemap::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
	{
		_isClicked = true;
		for (_viMap = _vMap.begin(); _viMap != _vMap.end(); ++_viMap)
		{
			if (PtInRect(&_viMap->getLPRc(), _ptMouse) && _isClicked)
			{
				_index = _viMap->getIndex();
				_viMap->setIsClicked(true);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		for (_viMap = _vMap.begin(); _viMap != _vMap.end(); ++_viMap)
		{
			if (PtInRect(&_viMap->getLPRc(), _ptMouse))
			{
				_viMap->setImgStr(_vMap.at(_index).getImgStr());
				_vMap.at(_index).setImgStr("");
				_vMap.at(_index).setPoint(POINT{ 0,0 });
				_viMap->setIsClicked(false);
			}
		}
	}

	for (_viMap = _vMap.begin(); _viMap != _vMap.end(); ++_viMap) 
	{
		_viMap->update(_ptMouse);
	}
}

void Tilemap::render(void)
{
	for (_viMap = _vMap.begin(); _viMap != _vMap.end(); ++_viMap) 
	{
		RectangleMakeToRECT(getMemDC(), _viMap->getLPRc());
	}

	for (_viMap = _vMap.begin(); _viMap != _vMap.end(); ++_viMap)
	{
		_viMap->ImgRender(getMemDC());
	}

}
