#include "Stdafx.h"
#include "TempSoundTest.h"

HRESULT TempSoundTest::init(void)
{
	TEMPSOUNDMANAGER->addMp3FileWithKey("찬란", "Resource/Sound/Got Me.mp3");
	TEMPSOUNDMANAGER->addWaveFileWithKey("문체부", "Resource/Sound/paper_slide.wav");

	return S_OK;
}

void TempSoundTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) 
	{
		cout << "input : P" << endl;
		TEMPSOUNDMANAGER->playSoundWithKey("찬란");
	}
	if (KEYMANAGER->isOnceKeyDown('A')) 
	{
		//TEMPSOUNDMANAGER->playSoundWithKey("문체부");
		//cout<<"input : A" <<endl;
		TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/paper_slide.wav");
	}


}
