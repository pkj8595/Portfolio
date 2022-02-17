#include "Stdafx.h"
#include "Homework_0113_1.h"

HRESULT Homework_0113_1::init(void)
{
	MainGame::init();
	_puzzleImg = new my::Image;
	_puzzleImg->init("Resource/Images/Homework/slide.bmp", 149*3, 128*3, true, RGB(255, 0, 255));

	_GameStartImg = new my::Image;
	_GameStartImg->init("Resource/Images/Homework/StartButton.bmp", 48 * 3, 13 * 3, true, RGB(255, 0, 255));

	_CheetImg = new my::Image;
	_CheetImg->init("Resource/Images/Homework/CheetButton.bmp", 45 * 3, 13 * 3, true, RGB(255, 0, 255));


	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			_rcPuzzle[i][j].num = (i * 3) + j;
			_rcPuzzle[i][j].index = (i * 3) + j;
			_rcPuzzle[i][j].rc.left = PUZZLE_START_X+(j * 149);
			_rcPuzzle[i][j].rc.top = PUZZLE_START_Y + (i * 128);
			_rcPuzzle[i][j].rc.right = (PUZZLE_START_X + 149) + (j * 149);
			_rcPuzzle[i][j].rc.bottom = (PUZZLE_START_Y + 128) + (i * 128);
			_rcPuzzle[i][j].isEndPz = false;
		}
	}
	

	_rcGameStart = RectMake(300, 100, 48 * 3, 13 * 3);
	_rcCheet = RectMake(500, 100, 45 * 3, 13 * 3);

	return S_OK;
}

void Homework_0113_1::release(void)
{
	MainGame::release();

}

void Homework_0113_1::update(void)
{
	MainGame::update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
	{
		if (PtInRect(&_rcGameStart, _ptMouse)) 
		{
			//RectShuffle(_rcPuzzle, 9, 20);
			int dest;
			int sour;
			RECT temp;
			int indexTemp;
			for (int i = 0; i < 20; i++)
			{
				dest = RND->getInt(9);
				sour = RND->getInt(9);

				temp = _rcPuzzle[0][dest].rc;
				indexTemp = _rcPuzzle[0][dest].index;
				_rcPuzzle[0][dest].rc = _rcPuzzle[0][sour].rc;
				_rcPuzzle[0][dest].index = _rcPuzzle[0][sour].index;
				_rcPuzzle[0][sour].rc = temp;
				_rcPuzzle[0][sour].index = indexTemp;

			}
			for (int i = 0; i < 9; i++)
			{
				if (_rcPuzzle[0][i].index == 8)
					_rcPuzzle[0][i].isEndPz = true;
				else 
					_rcPuzzle[0][i].isEndPz = false;
			}
		}

		if (PtInRect(&_rcCheet, _ptMouse))
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					_rcPuzzle[i][j].num = (i * 3) + j;
					_rcPuzzle[i][j].rc.left = PUZZLE_START_X + (j * 149);
					_rcPuzzle[i][j].rc.top = PUZZLE_START_Y + (i * 128);
					_rcPuzzle[i][j].rc.right = (PUZZLE_START_X + 149) + (j * 149);
					_rcPuzzle[i][j].rc.bottom = (PUZZLE_START_Y + 128) + (i * 128);
				}
			}
		}


	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{

	}

}

void Homework_0113_1::render(HDC hdc)
{
	HDC memDC = this->getBackBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	_puzzleImg->render(memDC, 0, 200);
	//_puzzleImg->render(memDC, PUZZLE_START_X, PUZZLE_START_Y);
	_GameStartImg->render(memDC, _rcGameStart.left, _rcGameStart.top);
	_CheetImg->render(memDC, _rcCheet.left, _rcCheet.top);

	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++) 
		{
			_puzzleImg->render(memDC,
				_rcPuzzle[i][j].rc.left,
				_rcPuzzle[i][j].rc.top,
				(j * 149), (i * 128), 149, 128);
			
			
			if (_rcPuzzle[i][j].isEndPz) 
			{
				RectangleMakeToRECT(memDC, _rcPuzzle[i][j].rc);
			}

		}		 
	}

	if (KEYMANAGER->isToggleKey(VK_F1)) 
	{
		RectangleMakeToRECT(hdc, _rcGameStart);
		RectangleMakeToRECT(hdc, _rcCheet);
		for (int i = 0; i < 9; i++) 
		{
			RectangleMakeToRECT(memDC, _rcPuzzle[0][i].rc);
		}
	}

	this->getBackBuffer()->render(hdc,0,0);
}

void Homework_0113_1::RectShuffle(RECT* rc, int arrSize, int shuffleCount)
{
	int dest;
	int sour;
	RECT temp;

	for (int i = 0; i < shuffleCount; i++)
	{
		dest = RND->getInt(arrSize);
		sour = RND->getInt(arrSize);

		temp = rc[dest];
		rc[dest] = rc[sour];
		rc[sour] = temp;
	}
}
