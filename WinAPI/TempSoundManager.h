#pragma once
#include "SingletonBase.h"


class TempSoundManager :public SingletonBase<TempSoundManager>
{
public :
	HRESULT init();
	void addMp3FileWithKey(string key, string fileName);
	void addWaveFileWithKey(string key, string fileName);
	void playEffectSoundWave(char* fileName);
	void playSoundWithKey(string key);
	void stopMp3WithKey(string key);
	void closeMp3WithKey(string key);
	void resumeMp3WithKey(string key);
	void undoMp3WithKey(string key);

	TempSoundManager() {}
	~TempSoundManager() {}
};

