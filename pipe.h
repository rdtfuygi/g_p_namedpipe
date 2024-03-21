#pragma once

#ifdef GPNAMEDPIPE_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)//����
#endif

#include<string>
#include<vector>
#include<Windows.h>

const char ����_���� = 1;
const char ����_���� = 2;
const char ����_˫�� = 3;

class DLL pipe
{
protected:
	HANDLE pip;
	//std::vector<char> buffer;
public:
	pipe(std::string ����, int ��������С = 4096, char ���� = ����_˫��);
	~pipe();
	bool connect();

	bool send(std::vector<float>& ����);

	bool receive(std::vector<float>& ����);
};