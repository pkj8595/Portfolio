#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init()
{
	return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type mpegvideo alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();
	//mciSendString() : 현재 장치에 명령어를 전송하여 필요한 장치를 구동시키는 함수
	//문자열 명령어, 반환값 문자열, 반환될 길이, 핸들 콜백
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type waveaudio alias ";
	string finalQuery = first + fileName + end + key;

	const char* str = finalQuery.c_str();
	
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
	//SND_NODEFAULT : 사운드 가 없을때  경고음을 듣지 않겠다.
	//파일이름.wave,핸들(NULL ->파일명을 사용한다.),sound : 옵션|옵션|옵션
	//루프를 하고 있으니 반복이 발생 ->SND_ASYNC를 할당하지 않으면 뒤의 코드가 실행되지 않음.
	//SND_ASYNC : 재생하면서 다음 코드 실행(비동기적으로 작동하라는 플래그)
	//무거움
	//PlaySound(fileName, NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	PlaySound(fileName, NULL, SND_ASYNC);

}

void TempSoundManager::playSoundWithKey(string key)
{
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::stopMp3WithKey(string key)
{
	string first = "stop ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::closeMp3WithKey(string key)
{
	string first = "close ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::resumeMp3WithKey(string key)
{
	string first = "resume ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::undoMp3WithKey(string key)
{
	string first = "undo ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}
