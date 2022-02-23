#pragma once
#include "SingletonBase.h"

/*
#include <fstream>
FILE* file;
Text	>> 사용은 매우 쉽지만 보안은 굉장히 취약하다
xml		>> 암호화를 하긴하지만 그 수준이 높지않다.
json	>> java로 부터 파생 c++에서 사용가능
ini		>> 자주 변경이 되는 값을 설정할때 들어간다. ex)옵션
*/

#define SAVE_BUFFER 128
#define LOAD_BUFFER 128

class TextDataManager : public SingletonBase<TextDataManager>
{
private:

public:
	HRESULT init(void);
	void release(void);

	void save(const char* fileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	vector<string> load(const char* fileName);
	vector<string> charArraySeparation(char charArray[]);

	vector<string> loadFstream(const char* fileName);

	TextDataManager() {}
	~TextDataManager() {}
};

