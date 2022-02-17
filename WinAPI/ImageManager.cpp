#include "Stdafx.h"
#include "ImageManager.h"



	HRESULT ImageManager::init(void)
	{
		return S_OK;
	}

	void ImageManager::release(void)
	{
		this->deleteAll();
	}

	my::Image* ImageManager::addImage(string strKey, int width, int height)
	{
		//추가하려는 이미지가 존재하는지 키값으로 확인
		my::Image* img = findImage(strKey);

		if (img) return img;

		img = new my::Image;
		if (FAILED(img->init(width, height)))
		{
			SAFE_DELETE(img);
			return NULL;
		}

		//_mImageList.insert(pair<string, mycustom::Image*>(strKey, img));
		_mImageList.insert(make_pair(strKey, img));


		return img;
	}

	my::Image* ImageManager::addImage(string strKey, const char * fileName, int width, int height, BOOL isTrans, COLORREF transColor)
	{
		//추가하려는 이미지가 존재하는지 키값으로 확인
		my::Image* img = findImage(strKey);

		if (img) return img;

		img = new my::Image;
		if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
		{
			SAFE_DELETE(img);
			return NULL;
		}

		//_mImageList.insert(pair<string, mycustom::Image*>(strKey, img));
		_mImageList.insert(make_pair(strKey, img));

		return img;
	}

	my::Image* ImageManager::addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
	{
		my::Image* img = findImage(strKey);

		if (img) return img;

		img = new my::Image;
		if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
		{
			SAFE_DELETE(img);
			return NULL;
		}

		//_mImageList.insert(pair<string, mycustom::Image*>(strKey, img));
		_mImageList.insert(make_pair(strKey, img));

		return img;
	}

	my::Image* ImageManager::addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
	{
		my::Image* img = findImage(strKey);

		if (img) return img;

		img = new my::Image;
		if (FAILED(img->init(fileName, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
		{
			SAFE_DELETE(img);
			return NULL;
		}

		//_mImageList.insert(pair<string, mycustom::Image*>(strKey, img));
		_mImageList.insert(make_pair(strKey, img));

		return img;
	}

	my::Image* ImageManager::addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
	{
		my::Image* img = findImage(strKey);

		if (img) return img;

		img = new my::Image;
		if (FAILED(img->init(fileName, x, y, width, height, maxFrameX, maxFrameY, isTrans, transColor)))
		{
			SAFE_DELETE(img);
			return NULL;
		}

		//_mImageList.insert(pair<string, mycustom::Image*>(strKey, img));
		_mImageList.insert(make_pair(strKey, img));

		return img;
	}

	my::Image* ImageManager::findImage(string strKey)
	{
		auto key = _mImageList.find(strKey);

		//검색한키로 이미지를 찾았다면
		if (key != _mImageList.end())
		{
			return key->second;
		}

		//검색한키로 이미지를 못찾았다면
		return nullptr;
	}

	bool ImageManager::deleteImage(string strKey)
	{
		auto key = _mImageList.find(strKey);

		if (key != _mImageList.end())
		{
			key->second->release();
			SAFE_DELETE(key->second);
			_mImageList.erase(key);
			return true;
		}

		return false;
	}

	bool ImageManager::deleteAll()
	{
		auto iter = _mImageList.begin();

		for (; iter != _mImageList.end();)
		{
			if (iter->second != NULL)
			{
				iter->second->release();
				SAFE_DELETE(iter->second);
				iter = _mImageList.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		_mImageList.clear();

		return true;
	}

	//===============
	// ## 일반렌더 ##
	//===============
	void ImageManager::render(string strKey, HDC hdc)
	{
		my::Image *img = findImage(strKey);
		if (img) img->render(hdc);
	}

	void ImageManager::render(string strKey, HDC hdc, int destX, int destY)
	{
		my::Image *img = findImage(strKey);
		if (img) img->render(hdc, destX, destY);
	}

	void ImageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
	{
		my::Image *img = findImage(strKey);
		if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
	}
	//===============
	// ## 알파렌더 ##
	//===============
	void ImageManager::alphaRender(string strKey, HDC hdc, BYTE alpha)
	{
		my::Image *img = findImage(strKey);
		if (img) img->alphaRender(hdc, alpha);
	}

	void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
	{
		my::Image *img = findImage(strKey);
		if (img) img->alphaRender(hdc, destX, destY, alpha);
	}

	void ImageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
	{
		my::Image *img = findImage(strKey);
		if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
	}
	//==============
	//# 프레임 렌더 #
	//==============
	void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
	{
		my::Image *img = findImage(strKey);
		if (img) img->frameRender(hdc, destX, destY);
	}

	void ImageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
	{
		my::Image *img = findImage(strKey);
		if (img) img->frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
	}

	void ImageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
	{
		my::Image *img = findImage(strKey);
		if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
	}

	void ImageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
	{
		my::Image *img = findImage(strKey);
		if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
	}



	//=====================
	//# mgpbitmap #
	//=====================
	mGpImage* ImageManager::initForGPbitmap(string strKey, WCHAR* fileName,  INT size, BOOL useEmbeddedColorManagement)
	{
		//추가하려는 이미지가 존재하는지 키값으로 확인
		mGpImage* img = findGPbitmap(strKey);

		if (img) return img;

		img = new mGpImage;
		if (FAILED(img->init(fileName, size, useEmbeddedColorManagement)))
		{
			SAFE_DELETE(img);
			return NULL;
		}

		_mGpBitmapList.insert(make_pair(strKey, img));

		return img;
	}



	void ImageManager::renderForGPbitmap(string strKey, Graphics* g, INT size)
	{
		mGpImage *img = findGPbitmap(strKey);
		if (img) img->render(g, size);
	}

	void ImageManager::renderForGPbitmap(string strKey, Graphics * g, REAL x, REAL y, REAL w, REAL h)
	{
		mGpImage *img = findGPbitmap(strKey);
		if (img) img->render(g, x,y,w,h);
	}

	mGpImage* ImageManager::findGPbitmap(string strKey)
	{
		auto key = _mGpBitmapList.find(strKey);

		//검색한키로 이미지를 찾았다면
		if (key != _mGpBitmapList.end())
		{
			return key->second;
		}

		//검색한키로 이미지를 못찾았다면
		return nullptr;
	}

