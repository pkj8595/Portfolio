#include "Stdafx.h"
#include "PlayerAfterImage.h"

HRESULT PlayerAfterImage::init(void)
{
	_image0 = IMAGEMANAGER->addImage("AfterImage0", "Resource/Images/Lucie/CompleteImg/Player/AfterImage_0.bmp", 100, 100, true, RGB(255, 0, 255));
	_image1 = IMAGEMANAGER->addImage("AfterImage1", "Resource/Images/Lucie/CompleteImg/Player/AfterImage_1.bmp", 100, 100, true, RGB(255, 0, 255));
	_image2 = IMAGEMANAGER->addImage("AfterImage2", "Resource/Images/Lucie/CompleteImg/Player/AfterImage_2.bmp", 100, 100, true, RGB(255, 0, 255));
	_image3 = IMAGEMANAGER->addImage("AfterImage3", "Resource/Images/Lucie/CompleteImg/Player/AfterImage_3.bmp", 100, 100, true, RGB(255, 0, 255));
	_image4 = IMAGEMANAGER->addImage("AfterImage4", "Resource/Images/Lucie/CompleteImg/Player/AfterImage_4.bmp", 100, 100, true, RGB(255, 0, 255));
	_image5 = IMAGEMANAGER->addImage("AfterImage5", "Resource/Images/Lucie/CompleteImg/Player/AfterImage_5.bmp", 100, 100, true, RGB(255, 0, 255));
	return S_OK;
}

void PlayerAfterImage::release(void)
{
}

void PlayerAfterImage::update(void)
{
	_viAfterImage = _vAfterImage.begin();
	for (;_viAfterImage != _vAfterImage.end(); ++_viAfterImage)
	{
		_viAfterImage->alpha-= 32;
		if (_viAfterImage->alpha < 0)
		{
			_vAfterImage.erase(_viAfterImage);
			break;
		}
	}
}

void PlayerAfterImage::render(void)
{
	for (afterImageSet ai : _vAfterImage)
	{
		switch (ai.frame)
		{
		case 0: _image0->alphaRender(getMemDC(),
			ai.x - CAMERAMANAGER->getCameraRect().left,
			ai.y - CAMERAMANAGER->getCameraRect().top, ai.alpha);
			break;
		case 1: _image1->alphaRender(getMemDC(),
			ai.x - CAMERAMANAGER->getCameraRect().left,
			ai.y - CAMERAMANAGER->getCameraRect().top, ai.alpha); 
			break;
		case 2: _image2->alphaRender(getMemDC(),
			ai.x - CAMERAMANAGER->getCameraRect().left,
			ai.y - CAMERAMANAGER->getCameraRect().top, ai.alpha); 
			break;
		case 3: _image3->alphaRender(getMemDC(),
			ai.x - CAMERAMANAGER->getCameraRect().left,
			ai.y - CAMERAMANAGER->getCameraRect().top, ai.alpha); 
			break;
		case 4: _image4->alphaRender(getMemDC(),
			ai.x - CAMERAMANAGER->getCameraRect().left,
			ai.y - CAMERAMANAGER->getCameraRect().top, ai.alpha); 
			break;
		case 5: _image5->alphaRender(getMemDC(),
			ai.x - CAMERAMANAGER->getCameraRect().left,
			ai.y - CAMERAMANAGER->getCameraRect().top, ai.alpha); 
			break;
		}
		
	}
}

void PlayerAfterImage::createAfterImage(float x, float y, int startX)
{
	afterImageSet set;
	set.x = x;
	set.y = y;
	set.frame = startX;
	set.alpha = 255;
	_vAfterImage.push_back(set);
}
