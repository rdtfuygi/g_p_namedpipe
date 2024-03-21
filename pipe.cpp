#include"pipe.h"
#include <codecvt>
#include <locale>
#include <ctime>

pipe::pipe(std::string ����, int ��������С, char ����)// :buffer(��������С)
{
	std::string �ܵ����� = "\\\\.\\pipe\\" + ���� + "_pipe";
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> ת����;
	std::wstring �ܵ�����_Unicode = ת����.from_bytes(�ܵ�����);
	int ����ģʽ;
	switch (����)
	{
	case ����_����:
		����ģʽ = PIPE_ACCESS_INBOUND;
		break;
	case ����_����:
		����ģʽ = PIPE_ACCESS_OUTBOUND;
		break;
	case ����_˫��:
		����ģʽ = PIPE_ACCESS_DUPLEX;
		break;
	default:
		����ģʽ = PIPE_ACCESS_DUPLEX;
		break;
	}
	pip = CreateNamedPipeW(
		�ܵ�����_Unicode.c_str(),
		����ģʽ,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		��������С,
		��������С,
		NMPWAIT_WAIT_FOREVER,
		NULL);
}

pipe::~pipe()
{
	CloseHandle(pip);
}

bool pipe::connect()
{
	return ConnectNamedPipe(pip, NULL);
}


bool pipe::send(std::vector<float>& ����)
{
	DWORD ������ = 1;
	while (������ != 0)
	{
		PeekNamedPipe(pip, NULL, NULL, NULL, &������, NULL);
		//Sleep(1000);
	}
	����.push_back(����.size());
	bool ��� = WriteFile(pip, ����.data(), sizeof(float) * ����.size(), &������, NULL);
	if (��� && (������ == sizeof(float) * ����.size()))
	{
		return true;
	}
	return false;
}


bool pipe::receive(std::vector<float>& ����)
{
	DWORD ������ = 0;
	while (������ == 0)
	{
		PeekNamedPipe(pip, NULL, NULL, NULL, &������, NULL);
	}
	���� = std::vector<float>(������ / sizeof(float));
	bool ��� = ReadFile(pip, ����.data(), sizeof(float) * ����.size(), &������, NULL);
	float �ߴ� = ����[����.size() - 1];
	����.erase(����.end() - 1);
	if (��� && (����.size() == �ߴ�))
	{
		return true;
	}	
	return false;
}
