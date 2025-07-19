#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#include "标头.h"
int argc = 0;
LPTSTR* argv;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIntance, LPSTR szCmdline, int iCmdShow)
{
	argv = CommandLineToArgvW(GetCommandLineW(), &argc);//获取程序参数
	if (argc == 1)//配置模式
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
	else//工作模式
	{
		Execute();
	}
	return 0;
}