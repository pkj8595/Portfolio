#pragma once
#include "SingletonBase.h"
#include "Image.h"
#include "mGpImage.h"


class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef map<string, my::Image*> mapImageList;
	typedef map<string, my::Image*>::iterator mapImageIter;

	typedef map<string, mGpImage*> mapGPBitmapList;
	typedef map<string, mGpImage*>::iterator mapGPBitmapIter;

private:
	mapImageList _mImageList;
	mapGPBitmapList _mGpBitmapList;

public:
	HRESULT init(void);
	void release(void);


	my::Image* addImage(string strKey, int width, int height);
	my::Image* addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	my::Image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	my::Image* addFrameImage(string strKey, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));		 
	my::Image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	my::Image* findImage(string strKey);
	bool deleteImage(string strKey);
	bool deleteAll();

	void render(string strKey,HDC hdc);
	void render(string strKey,HDC hdc, int destX, int destY);
	void render(string strKey,HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//=====================
	//# mgpbitmap #
	//=====================
	mGpImage* initForGPbitmap(string strKey,WCHAR *fileName, INT size =4,BOOL useEmbeddedColorManagement = PixelFormat16bppARGB1555);
	void renderForGPbitmap(string strKey, Gdiplus::Graphics* g,INT size);
	void renderForGPbitmap(string strKey, Gdiplus::Graphics* g, REAL x, REAL y, REAL w, REAL h);
	mGpImage* findGPbitmap(string strKey);


	ImageManager() {}
	~ImageManager() {}
};

