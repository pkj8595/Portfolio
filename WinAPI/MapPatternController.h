#pragma once
#include "CBlock.h"

#define BLOCK_SIZE		10
#define WALL_SIZE		50
#define BLOCK2_SIZE		200
#define BLOCK3_SIZE		20

class MapPatternController
{
private:
	Gdiplus::Matrix _mapMatrix;

	CBlock _imgBlock[BLOCK_SIZE];
	CBlock _rectShape[WALL_SIZE];
	CBlock _rectBlockNotRotate2[BLOCK2_SIZE];
	CBlock _rectBlock3[BLOCK3_SIZE];

	
	CBlock _boss;
	CBlock _boss2;
	CBlock _boss3;
	CBlock _bossBigRect;

	CBlock _wallRc;
	

	int _waveCount;
	bool _ColumnBool;
	bool _boolSizePattern;
	bool _boolBossUpdownPattern;
	int _angleCount;
	int _count;

public:
	HRESULT init();
	void update(int time);
	void bigRectPattern(int time, int startTime, int endTime);
	void bigRectPattern2(int time, int startTime, int endTime);
	void bossPattern1(int time, int startTime, int endTime);
	void bossWavePattern2(int time, int startTime, int endTime);
	void shapePattern1(int time, int startTime, int endTime);
	void shapePattern2(int time, int startTime, int endTime);

	void frashPattern2(int time, int startTime, int endTime);
	void shapePatternDrectionColumn(int time, int startTime, int endTime);
	void wavePattern(int time, int startTime, int endTime);

	void bossDrectionPattern(int time, int startTime, int endTime);
	void bossUpDownPattern(int time, int startTime, int endTime);
	void bossRotateRectPattern(int time, int startTime, int endTime);
	void bossFinalPattern(int time, int startTime, int endTime);
	
	void render(Gdiplus::Graphics *g);

	MapPatternController();
	~MapPatternController() {}
};

