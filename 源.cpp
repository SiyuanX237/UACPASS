#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include "D:\C files\myhead.h"
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1)//无参数运行无意义
	{
		return 0;
	}
	if (argc == 2)
	{
		if (argv[1][0] == '1')
		{
			ShellExecute(NULL, L"open", L"wscript.exe", L"D:\\programfiles\\uacpass\\temp.vbs", NULL, SW_NORMAL);
			return 0;
		}
	}
	setlocale(LC_ALL, "chs");
	wstring mainPath;
	wstring param;
	CharToWstring(argv[1], &mainPath);
	for (short i = 2; argc != 2; i++)
	{
		wstring temp;
		CharToWstring(argv[i], &temp);
		param += temp;
		if (i == (argc - 1))
		{
			break;
		}
		param += L" ";
	}
	FILE *fp;
	wchar_t *temp = new wchar_t[255];
	wchar_t *mainPath2 = new wchar_t[250];
	CharToWchar(argv[0], temp);
	getfname(temp, NULL, mainPath2);
	delete[] temp;
	wstring vbs;
	vbs += mainPath2;
	delete[] mainPath2;
	vbs += L"TEMP.vbs";
	fp = _wfopen(vbs.c_str(), L"w+");
	fwprintf(fp, L"Set shell = CreateObject(\"Shell.Application\")\nshell.ShellExecute \"\"\"%ls\"\"\",", mainPath.c_str());
	if (param.length() != 0)
	{
		fwprintf(fp, L"\"\"\"%ls\"\"\"", param.c_str());
	}
	fwprintf(fp, L",,\"runas\",1\nWScript.Quit");
	fclose(fp);
	wstring command;
	command += L"/run /tn \\UACPass\\UACPass\0";
	ShellExecute(NULL, L"open", L"schtasks.exe", command.c_str(), NULL, SW_HIDE);
	return 0;
}

