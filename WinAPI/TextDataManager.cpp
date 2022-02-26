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

// ����¥�� �����͸� ��ƵѰ�
// ��� �����͸� ���� ������ ©�� ����
void TextDataManager::save(const char* fileName, vector<string> vStr)
{
	HANDLE file;
	char str[SAVE_BUFFER];
	DWORD write;

	/*
	strcpy : ���ڿ� ����
	strncpy
	strcpy_s :
	strncpy_s : ������ ũ�⸦ ���ڷ� ����ش�.(����)
				���� �ڵ����� NULL ���� ����
	*/
	strncpy_s(str, SAVE_BUFFER, vectorArrayCombine(vStr), SAVE_BUFFER - 1);
	/*
	CreateFile() : ���� ����� ��ġ�� ����ų� �о�´�.
	�� ��ȯ���� ����� �� �ִ� Handle
	CreateFile
	(
		�����ϰų� �� ������ �̸�, 
		���� ���� Ÿ��, 
		���� ��������(0�� ����X), 
		�ڽĿ��� ��� ����, 
		���� ���� ��� ����
	)
	CREATE_ALWAYS : ���ο� ���� ����, ������ ���� ����� �����
	FILE_ATTRIBUTE_NORMAL : �ٸ� �Ӽ����� ������ �ʰڴ�.

	*/
	file = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	/*
	WriteFile():
	1. CreateFile()���� �Ҵ�� �ڵ�
	2. ���Ͽ� ���� ���� ��Ʈ�� ��
	3. �󸶳� �а� ���������� ���� ũ�� 
	4. �󸶳� �а� ���������� ���� ������� ����ȴ�.(�ּ�)
	*/
	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);

}
//���� ����� ������
//����¥�� �����͸� ��ǥ������ �� �����ϴ� ���� �����ϰ� �װ��� ������� �Ҷ� ���ϴ�
char* TextDataManager::vectorArrayCombine(vector<string> vArray)
{
	char str[SAVE_BUFFER];
	ZeroMemory(str, sizeof(str));

	
	for (int i = 0; i < vArray.size(); i++)
	{
		//���ڿ� ��ġ��
		// c_str() : Ÿ�� ĳ����
		//string �ڷ����� char* ������ ��ȯ
		strncat_s((str), SAVE_BUFFER, vArray[i].c_str(), SAVE_BUFFER - 1);
		if (i + 1 < vArray.size()) strcat_s(str, ",");
		
	}

	return str;
}

vector<string> TextDataManager::load(const char* fileName)
{
	//1. �÷��̾� �������ͽ� 
	//2. �ʿ� ���� ����
	HANDLE file;
	char str[LOAD_BUFFER];
	DWORD read;

	memset(str, 0, LOAD_BUFFER);

	// OPEN_EXISTING : �����ϸ� ����.
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
		strtok() : ���ڿ��� ��ū���� �и��Ѵ�. 
		strtok
		(
			���ڿ��� ��ū���� �и��ϰ� ���� �迭�� �޸� �ּ�,
			�и� ���� �и�����,
			�߳����� ���� ���ڿ��� �޸� �ּ�
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
		//��ġ �����ڸ� ���� ������ �ű��.
		in.seekg(0, ios::end);
		//���� �� ��ġ�� �д´�.
		size = in.tellg();
		//�� ũ���� ���ڿ��� �Ҵ��Ѵ�.
		str.resize(size);
		//��ġ �����ڸ� �ٽ� ���� �� ������ �Ǳ��.
		in.seekg(0, ios::beg);
		//���� ��ü ������ �о ���ڿ��� �����Ѵ�.
		in.read(&str[0], size);
	}
	else
	{
		cout << "���� �ε� ����" << endl;
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
