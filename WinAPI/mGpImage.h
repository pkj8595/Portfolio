#pragma once

class mGpImage
{
private:

	typedef struct tagMgpBitmap 
	{
		HDC			hMemDc;
		HBITMAP		hBit;
		HBITMAP		hOBit;
		HBITMAP		bitmapCopy;
		INT			center_x;
		INT			center_y;
		INT			center_width;
		INT			center_height;
		INT			size;

		tagMgpBitmap()
		{
			hMemDc =NULL;
			hBit = NULL;
			hOBit = NULL; 
			bitmapCopy =NULL;
			center_x = 0;
			center_y = 0;
			center_width = 0;
			center_height = 0;
			size = 0;
		}
	}mGPBITMAP_INFO, *mLPGPBITMAP_INFO;

	Gdiplus::Bitmap* _bitmap;
	mLPGPBITMAP_INFO _bitmapInfo;
	WCHAR* _fileName;

public:
	mGpImage();
	~mGpImage() {};

	HRESULT init(WCHAR *fileName,INT size = 1,BOOL useEmbeddedColorManagement = PixelFormat16bppARGB1555);
	void render(Gdiplus::Graphics* g, int size);
	void render(Gdiplus::Graphics* g, REAL X, REAL Y, REAL Width, REAL Height);
	void release(void);

};

