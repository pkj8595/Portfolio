#include "Stdafx.h"
#include "TextDataManager.h"

HRESULT TextDataManager::init(void)
{

	return S_OK;
}

void TextDataManager::release(void)
{
	//! Do Notting
}

// 한줄짜리 데이터를 담아둘것
// 모든 데이터를 한줄 단위로 짤라서 지정
void TextDataManager::save(const char* fileName, vector<string> vStr)
{
	HANDLE file;
	char str[SAVE_BUFFER];
	DWORD write;

	/*
	strcpy : 문자열 복사
	strncpy
	strcpy_s :
	strncpy_s : 복사할 크기를 인자로 잡아준다.(길이)
				끝에 자동으로 NULL 문자 삽입
	*/
	strncpy_s(str, SAVE_BUFFER, vectorArrayCombine(vStr), SAVE_BUFFER - 1);
	/*
	CreateFile() : 파일 입출력 장치를 만들거나 읽어온다.
	ㄴ 반환값은 사용할 수 있는 Handle
	CreateFile
	(
		생성하거나 열 파일의 이름, 
		파일 접근 타입, 
		파일 공유여부(0은 공유X), 
		자식에게 상속 여부, 
		파일 생성 모드 셋팅
	)
	CREATE_ALWAYS : 새로운 파일 생성, 동일한 파일 존재시 덮어쓰기
	FILE_ATTRIBUTE_NORMAL : 다른 속성값을 가지지 않겠다.

	*/
	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	/*
	WriteFile():
	1. CreateFile()에서 할당된 핸들
	2. 파일에 쓰고 싶은 스트링 값
	3. 얼마나 읽고 쓸것인지에 대한 크기 
	4. 얼마나 읽고 쓸것인지에 대한 결과값이 저장된다.(주소)
	*/
	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);

}
//현재 사용할 데이터
//한줄짜리 데이터를 쉽표단위로 띄어서 저장하는 것이 가능하고 그것이 입출력을 할때 편하다
char* TextDataManager::vectorArrayCombine(vector<string> vArray)
{
	char str[SAVE_BUFFER];
	ZeroMemory(str, sizeof(str));

	
	for (int i = 0; i < vArray.size(); i++)
	{
		//문자열 합치기
		// c_str() : 타입 캐스팅
		//string 자료형을 char* 형으로 변환
		strncat_s((str), SAVE_BUFFER, vArray[i].c_str(), SAVE_BUFFER - 1);
		if (i + 1 < vArray.size()) strcat_s(str, ",");
		
	}

	return str;
}

vector<string> TextDataManager::load(const char* fileName)
{
	//1. 플레이어 스테이터스 
	//2. 맵에 대한 정보
	HANDLE file;
	char str[LOAD_BUFFER];
	DWORD read;

	memset(str, 0, LOAD_BUFFER);

	// OPEN_EXISTING : 존재하면 연다.
	file = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, LOAD_BUFFER, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> TextDataManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* temp;
	char* separator = ",";
	char* tokenA;
	char* tokenB;
	/*
		strtok() : 문자열을 토큰으로 분리한다. 
		strtok
		(
			문자열을 토큰으로 분리하고 싶은 배열의 메모리 주소,
			분리 사용될 분리문자,
			잘내낸후 남은 문자열의 메모리 주소
		);
	*/

	tokenA = strtok_s(charArray, separator, &tokenB);
	vArray.push_back(tokenA);

	while (NULL != (tokenA = strtok_s(NULL,separator,&tokenB)))
	{
		vArray.push_back(tokenA);
	}

	return vArray;
}


vector<string> TextDataManager::loadFstream(const char* fileName)
{
	std::ifstream in(fileName, ios::in);
	string str;
	string token;
	int size;

	if (in.is_open())
	{
		/*char line[256] = { 0 };
		while (in.getline(line, 256))
		{
			cout << line << endl;
		}
		in.close();*/
		//위치 지정자를 파일 끝으로 옮긴다.
		in.seekg(0, ios::end);
		//파일 끝 위치를 읽는다.
		size = in.tellg();
		//그 크기의 문자열을 할당한다.
		str.resize(size);
		//위치 지정자를 다시 파일 맨 앞으로 옳긴다.
		in.seekg(0, ios::beg);
		//파일 전체 내용을 읽어서 문자열에 저장한다.
		in.read(&str[0], size);
	}
	else
	{
		cout << "파일 로드 실패" << endl;
	}
	//str.erase(remove(str.begin(), str.end(), '\n'), str.end());

	char* cstr = new char[size + 1];
	copy(str.begin(), str.end(), cstr);

	vector<string> vArray;
	char* separator = ",";
	char* separator2 = "\n";
	char* tokenA;
	char* tokenB;

	tokenA = strtok_s(cstr, separator, &tokenB);
	vArray.push_back(tokenA);

	while (NULL != (tokenA = strtok_s(NULL, separator, &tokenB)))
	{
		vArray.push_back(tokenA);
	}

	delete[] cstr;

	return vArray;
}
