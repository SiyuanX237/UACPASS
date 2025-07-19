#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include "D:\C files\myhead.h"
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")//隐藏运行窗口
using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1)//无参数运行无意义，直接关掉吧
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
	setlocale(LC_ALL, "chs");//设置地区为中国（中文）
	wstring 主程序;
	wstring 参数;
	CharToWstring(argv[1], &主程序);
	for (short i = 2; argc != 2; i++)
	{
		wstring temp;
		CharToWstring(argv[i], &temp);
		参数 += temp;
		if (i == (argc - 1))
		{
			break;
		}
		参数 += L" ";
	}
	FILE *fp;
	wchar_t *temp = new wchar_t[255];
	wchar_t *本程序路径 = new wchar_t[250];
	CharToWchar(argv[0], temp);
	getfname(temp, NULL, 本程序路径);
	delete[] temp;
	wstring vbs所在;
	vbs所在 += 本程序路径;
	delete[] 本程序路径;
	vbs所在 += L"TEMP.vbs";
	fp = _wfopen(vbs所在.c_str(), L"w+");
	fwprintf(fp, L"Set shell = CreateObject(\"Shell.Application\")\nshell.ShellExecute \"\"\"%ls\"\"\",", 主程序.c_str());
	if (参数.length() != 0)
	{
		fwprintf(fp, L"\"\"\"%ls\"\"\"", 参数.c_str());
	}
	fwprintf(fp, L",,\"runas\",1\nWScript.Quit");
	fclose(fp);
	wstring 最后命令;
	最后命令 += L"/run /tn \\UACPass\\UACPass\0";
	ShellExecute(NULL, L"open", L"schtasks.exe", 最后命令.c_str(), NULL, SW_HIDE);
	return 0;
}

