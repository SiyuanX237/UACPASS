#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include "D:\C files\myhead.h"
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")//�������д���
using namespace std;
int main(int argc, char* argv[])
{
	if (argc == 1)//�޲������������壬ֱ�ӹص���
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
	setlocale(LC_ALL, "chs");//���õ���Ϊ�й������ģ�
	wstring ������;
	wstring ����;
	CharToWstring(argv[1], &������);
	for (short i = 2; argc != 2; i++)
	{
		wstring temp;
		CharToWstring(argv[i], &temp);
		���� += temp;
		if (i == (argc - 1))
		{
			break;
		}
		���� += L" ";
	}
	FILE *fp;
	wchar_t *temp = new wchar_t[255];
	wchar_t *������·�� = new wchar_t[250];
	CharToWchar(argv[0], temp);
	getfname(temp, NULL, ������·��);
	delete[] temp;
	wstring vbs����;
	vbs���� += ������·��;
	delete[] ������·��;
	vbs���� += L"TEMP.vbs";
	fp = _wfopen(vbs����.c_str(), L"w+");
	fwprintf(fp, L"Set shell = CreateObject(\"Shell.Application\")\nshell.ShellExecute \"\"\"%ls\"\"\",", ������.c_str());
	if (����.length() != 0)
	{
		fwprintf(fp, L"\"\"\"%ls\"\"\"", ����.c_str());
	}
	fwprintf(fp, L",,\"runas\",1\nWScript.Quit");
	fclose(fp);
	wstring �������;
	������� += L"/run /tn \\UACPass\\UACPass\0";
	ShellExecute(NULL, L"open", L"schtasks.exe", �������.c_str(), NULL, SW_HIDE);
	return 0;
}

