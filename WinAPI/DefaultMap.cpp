#include "Stdafx.h"
#include "DefaultMap.h"

HRESULT DefaultMap::init(POINT location)
{
	_type = Map::MAPTYPE::DEFAULT;
	_leftWallImageFixY = 0;
	_rightWallImageFixY = 0;
	_show = false;
	_clear = false;
	_rndMapNum = RND->getInt(5);
	_location = location;
	_minimapImage = IMAGEMANAGER->addImage("Minimap_On", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cell_on.bmp", 30, 30, true, RGB(255, 0, 255));
	_downWall = IMAGEMANAGER->addImage("DownWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/downWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	
	createRndMapImage();
		
	_pixel = false;
	return S_OK;
}

void DefaultMap::release(void)
{
}

void DefaultMap::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pixel = !_pixel;
	}
}

void DefaultMap::render(void)
{
	_image->render(getMemDC());

	if(!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(), 0 + _leftWallImageFixX, 50 + _leftWallImageFixY);
	if(!_connectedMap[1] || !_clear) _upWall->render(getMemDC(), CENTER_X - 180, -150);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(), 728 + _rightWallImageFixX, 50 + _rightWallImageFixY);
	if(!_connectedMap[3] || !_clear) _downWall->render(getMemDC(), CENTER_X - 170, _image->getHeight() - 240);

	if (_pixel) _pixelCollisionImage->render(getMemDC());
}

void DefaultMap::createRndMapImage()
{
	switch (_rndMapNum)
	{
	case 0:
	{
		_image = IMAGEMANAGER->addImage("DefaultGround1", "Resource/Images/Lucie/CompleteImg/ground/map/Ground217.bmp", 
			1008, 768, false, RGB(255, 0, 255));
		_pixelCollisionImage = IMAGEMANAGER->addImage("PixelGround1", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m217.bmp",
			1008, 768, false, RGB(255, 0, 255));
		_upWall = IMAGEMANAGER->addImage("UpWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall1.bmp", 240, 240, true, RGB(255,0,255));
		_leftWall = IMAGEMANAGER->addImage("LeftWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall1.bmp", 281, 480, true, RGB(255, 0, 255));
		_rightWall = IMAGEMANAGER->addImage("RightWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall2.bmp", 281, 528, true, RGB(255, 0, 255));
		_mapRC = { 200, 50, 700, 600 };
	}break;
	case 1:
	{
		_image = IMAGEMANAGER->addImage("DefaultGround2", "Resource/Images/Lucie/CompleteImg/ground/map/Ground104.bmp",
			1008, 768, false, RGB(255, 0, 255));
		_pixelCollisionImage = IMAGEMANAGER->addImage("PixelGround2", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m104.bmp",
			1008, 768, false, RGB(255, 0, 255));
		_upWall = IMAGEMANAGER->addImage("UpWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall2.bmp", 240, 240, true, RGB(255, 0, 255));
		_leftWall = IMAGEMANAGER->addImage("LeftWall3", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall3.bmp", 281, 540, true, RGB(255, 0, 255));
		_rightWall = IMAGEMANAGER->addImage("RightWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall2.bmp", 281, 528, true, RGB(255, 0, 255));
		_leftWallImageFixY = -2;
		_leftWallImageFixY = 0;
		_mapRC = { 200, 50, 700, 600 };
	}break;
	case 2:
	{
		_image = IMAGEMANAGER->addImage("DefaultGround3", "Resource/Images/Lucie/CompleteImg/ground/map/Ground110.bmp",
			1008, 768, false, RGB(255, 0, 255));
		_pixelCollisionImage = IMAGEMANAGER->addImage("PixelGround3", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m110.bmp",
			1008, 768, false, RGB(255, 0, 255));
		_upWall = IMAGEMANAGER->addImage("UpWall3", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall3.bmp", 240, 240, true, RGB(255, 0, 255));
		_leftWall = IMAGEMANAGER->addImage("LeftWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall1.bmp", 281, 480, true, RGB(255, 0, 255));
		_rightWall = IMAGEMANAGER->addImage("RightWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall2.bmp", 281, 528, true, RGB(255, 0, 255));
		_mapRC = { 200, 50, 700, 600 };
	}break;
	case 3:
	{
		_image = IMAGEMANAGER->addImage("DefaultGround4", "Resource/Images/Lucie/CompleteImg/ground/map/Ground115.bmp",
			1008, 672, false, RGB(255, 0, 255));
		_pixelCollisionImage = IMAGEMANAGER->addImage("PixelGround4", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m115.bmp",
			1008, 672, false, RGB(255, 0, 255));
		_upWall = IMAGEMANAGER->addImage("UpWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall1.bmp", 240, 240, true, RGB(255, 0, 255));
		_leftWall = IMAGEMANAGER->addImage("LeftWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall2.bmp", 288, 480, true, RGB(255, 0, 255));
		_rightWall = IMAGEMANAGER->addImage("RightWall3", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall3.bmp", 240, 480, true, RGB(255, 0, 255));
		_leftWallImageFixY = 100;
		_rightWallImageFixX = 50;
		_rightWallImageFixY = 100;
		_mapRC = { 133, 20, 770, 505 };
	}break;
	case 4:
	{
		_image = IMAGEMANAGER->addImage("DefaultGround5", "Resource/Images/Lucie/CompleteImg/ground/map/ground214.bmp",
			1008, 768, false, RGB(255, 0, 255));
		_pixelCollisionImage = IMAGEMANAGER->addImage("PixelGround5", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m214.bmp",
			1008, 768, false, RGB(255, 0, 255));
		_upWall = IMAGEMANAGER->addImage("UpWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall2.bmp", 240, 240, true, RGB(255, 0, 255));
		_leftWall = IMAGEMANAGER->addImage("LeftWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall1.bmp", 281, 480, true, RGB(255, 0, 255));
		_rightWall = IMAGEMANAGER->addImage("RightWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall1.bmp", 281, 480, true, RGB(255, 0, 255));
		_leftWallImageFixY = -5;
		_mapRC = { 200, 50, 700, 600 };
	}break;
	}
}
