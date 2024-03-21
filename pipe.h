#pragma once

#ifdef GPNAMEDPIPE_EXPORTS
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)//导入
#endif

#include<string>
#include<vector>
#include<Windows.h>

const char 方向_发送 = 1;
const char 方向_接收 = 2;
const char 方向_双向 = 3;

class DLL pipe
{
protected:
	HANDLE pip;
	//std::vector<char> buffer;
public:
	pipe(std::string 名字, int 缓冲区大小 = 4096, char 方向 = 方向_双向);
	~pipe();
	bool connect();

	bool send(std::vector<float>& 数据);

	bool receive(std::vector<float>& 数据);
};