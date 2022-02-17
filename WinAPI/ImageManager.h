#pragma once
#include "SingletonBase.h"
#include "Image.h"
#include "mGpImage.h"

/*
STL 맵의 핵심
- 키 , 값을 잊지말자
- 첫번째 first -> 키
- 두번째 second ->값
- 추가하는 방법은  insert를 사용하고 키와 밸류 두개를 동시에 추가해야하니
  pair or make_pair를 사용하여 추가한다.

-pair() : 두가지 자료형을 하나로 묶는 구조체 (템플릿 구조체이기에 어떤자료형이 와도 OK)
-make_pair() : 말 그래로 pair를 만들어 주는 함수
	ㄴ p.first = x, p.seconcd= y; 이런 형태를 
	ㄴp = make_pair(x,y): 형태로 
-하나의 키에 여러개의 값을 저장하고 싶으면 <multimap>
- pair 자체를 확장시켜 사용하고 싶으면 <tuple>를 사용하자
*/

class ImageManager : public SingletonBase<ImageManager>
{
	//typeid(_CImage);
private:
	//맵으로 만든 이미지 목록
	typedef map<string, my::Image*> mapImageList;
	//맵으로 만든 이미지 목록의 반복자
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

