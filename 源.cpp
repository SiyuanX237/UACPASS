#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include "��ͷ.h"
int argc = 0;
LPTSTR* argv;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIntance, LPSTR szCmdline, int iCmdShow)
{
	argv = CommandLineToArgvW(GetCommandLineW(), &argc);//��ȡ�������
	if (argc == 1)//����ģʽ
	{
		if (!IsAdmin())
		{
			SHELLEXECUTEINFOW shellexecinfo = {};
			shellexecinfo.cbSize = sizeof(shellexecinfo);
			shellexecinfo.lpVerb = L"runas";
			shellexecinfo.lpFile = argv[0];
			shellexecinfo.nShow = SW_SHOWNORMAL;
			ShellExecuteEx(&shellexecinfo);
		}
		else
		{
			Config();
		}
	}
	else//����ģʽ
	{
		Execute();
	}
	return 0;
}