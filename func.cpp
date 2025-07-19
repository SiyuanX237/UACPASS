#define _CRT_SECURE_NO_WARNINGS
#include "标头.h"


//配置模式
void Config()
{
	ShowConsole();
	int opt;
	while (1)
	{
		printf(
			"   __  _____   __________                 \n"
			"  / / / /   | / ____/ __ \\____ ___________\n"
			" / / / / /| |/ /   / /_/ / __ `/ ___/ ___/\n"
			"/ /_/ / ___ / /___/ ____/ /_/ (__  |__  ) \n"
			"\\____/_/  |_\\____/_/    \\__,_/____/____/  \n"
			"请选择UAC白名单模式:\n"
			"1.计划任务模式(以不弹窗的管理员权限运行)\n"
			"2.注册表模式(强制让程序以普通权限运行)\n"
			"3.关于本程序\n"
			"4.退出\n"
			"你的选择:"
		);
		int_read(&opt);
		switch (opt)
		{
		case 1:
			TaskMode();
			break;
		case 2:
			RegMode();
			break;
		case 3:
			About();
			break;
		case 4:
			printf("程序已结束，3秒后退出...");
			Sleep(3000);
			return;
		}
		system("cls");
	}
}

//显示控制台
void ShowConsole()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	cin.clear();
	cout.clear();
}

//int类型读取纯数字
void int_read(int* number)
{
	char buffer[12];
	int i = 0;
	int ch;
	while (1)
	{
		if (i == 12 - 1)
		{
			buffer[i] = '\0';
			while ((ch = getchar()) != '\n' && ch != EOF)
			{
				;
			}
			break;
		}
		ch = getchar();
		if (ch == '\n' || ch == EOF)
		{
			buffer[i] = '\0';
			break;
		}
		buffer[i++] = ch;
	}
	if (sscanf(buffer, "%d", number) != 1)//不正确的值
	{
		*number = -1;
	}
	return;
}

//计划任务模式
void TaskMode()
{
loop:
	printf(
		"请选择功能:\n"
		"1.添加UAC白名单计划任务\n"
		"2.移除UAC白名单计划服务\n"
		"3.打开计划任务\n"
		"4.回到主界面\n"
		"你的选择:"
	);
	int opt;
	int_read(&opt);
	switch (opt)
	{
	case 1:
		AddTask();
		system("cls");
		break;
	case 2:
		RemoveTask();
		system("cls");
		break;
	case 3:
		OpenTask();
		system("cls");
		break;
	case 4:
		break;
	default:
		goto loop;
	}
	return;
}

//添加计划任务
void AddTask()
{
	wstring command;
	command = format(L"/create /tn \\UACPass\\UACPass /tr \"\\\"{}\\\" 1 \" /sc ONCE /sd 1946/02/14 /st 11:45 /rl HIGHEST",argv[0]);
	ShellExecute(NULL, L"open", L"schtasks.exe", command.c_str(), NULL, SW_HIDE);
	printf("添加成功!\n");
	system("pause");
	return;
}

//移除计划任务
void RemoveTask()
{
	ShellExecute(NULL, L"open", L"schtasks.exe", L"/delete /tn \\UACPass\\UACPass /f", NULL, SW_HIDE);
	printf("移除成功!\n");
	system("pause");
	return;
}

//打开计划任务管理器
void OpenTask()
{
	ShellExecute(NULL, L"open", L"taskschd.msc", NULL, NULL, SW_NORMAL);
	return;
}

//注册表模式
void RegMode()
{
loop:
	printf(
		"请选择功能:\n"
		"1.添加UAC白名单注册表\n"
		"2.打开注册表(只能手动删除已添加项)\n"
		"3.回到主界面\n"
		"你的选择:"
	);
	int opt;
	int_read(&opt);
	switch (opt)
	{
	case 1:
		AddReg();
		break;
	case 2:
		OpenReg();
		break;
	case 3:
		break;
	default:
		goto loop;
	}
	return;
}

//添加注册表白名单
void AddReg()
{
	printf("请输入欲添加UAC白名单的程序完整路径(添加后移动程序将会失效)\n路径:");
	wchar_t path[MAX_PATH];
	path_read(path);

	wstring command;
	command = L"add \"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers\" /v ";
	if (path[0] != L'"')
	{
		command += L'"';
		command += path;
		command += L"\" /t REG_SZ /d RunAsInvoker /f";
	}
	else
	{
		command += path;
		command += L" /t REG_SZ /d RunAsInvoker /f";
	}
	ShellExecute(NULL, L"open", L"reg.exe", command.c_str(), NULL, SW_HIDE);
	printf("添加成功!\n");
	system("pause");
	return;
}

//路径读取
void path_read(wchar_t* Destination)
{
	int i = 0;
	wint_t wch;
	while (1)
	{
		if (i == MAX_PATH - 1)
		{
			Destination[i] = L'\0';
			while ((wch = getwchar()) != L'\n' && wch != WEOF)
			{
				;
			}
			break;
		}
		wch = getwchar();
		if (wch == L'\n' || wch == WEOF)
		{
			Destination[i] = L'\0';
			break;
		}
		if (wch == '"')
		{
			continue;
		}
		Destination[i++] = wch;
	}
}

//打开对应注册表位置
void OpenReg()
{
	wchar_t path[] = L"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers";
	oreg(path);
	return;
}

//关于
void About()
{
	printf(
		"UACPass是一款UAC弹窗白名单工具，可以在UAC开启的情况下指定一些程序免弹\n"
		"关注作者：Bilibili(゜-゜)つロ 个人隐思\n"
	);
	system("pause");
	return;
}

//工作模式
void Execute()
{
	if (!IsAdmin())//先看看有没有权限
	{
		//没有的话用计划任务提权
		//写入参数数据到临时文件
		FILE* fp;
		wchar_t path[MAX_PATH];
		wchar_t name[5] = L"TEMP";
		int path_length;
		getfname(argv[0], NULL, path, NULL, &path_length);
		
		for (int i = 0; i < 4 && path_length < MAX_PATH - 1;)
		{
			path[path_length++] = name[i++];
		}
		path[path_length] = L'\0';
		fp = _wfopen(path, L"w");
		if (fp == nullptr)
		{
			return;
		}
		for (int i = 1; i < argc; ++i)
		{
			fwprintf(fp, L"%ws\n", argv[i]);
		}
		fclose(fp);
		//再用计划任务提权
		ShellExecute(NULL, L"open", L"schtasks.exe", L"/run /tn \\UACPass\\UACPass", NULL, SW_HIDE);
		return;
	}
	//有特权就直接运行
	if (argc == 2 && argv[1][0] == L'1')//如果是就绪状态，需要从文件读取数据
	{
		//从临时文件读取参数数据
		FILE* fp;
		wchar_t path[MAX_PATH];
		wchar_t name[5] = L"TEMP";
		int path_length;
		getfname(argv[0], NULL, path, NULL, &path_length);
		
		for (int i = 0; i < 4 && path_length < MAX_PATH - 1;)
		{
			path[path_length++] = name[i++];
		}
		path[path_length] = L'\0';
		fp = _wfopen(path, L"r");
		if (fp == nullptr)
		{
			return;
		}
		wchar_t line[1024];
		wstring command = L"-NoProfile -WindowStyle Hidden -Command \"Start-Process '";
		//目标程序名
		fgetws(line, 1024, fp);
		path_length = lstrlenW(line) - 1;//复用变量
		line[path_length] = L'\0';
		command += line;//写入目标程序路径
		command += L"' ";
		if (fgetws(line, 1024, fp))//如果有参数
		{
			//首个参数特殊处理
			command += L" -ArgumentList ";
			path_length = lstrlenW(line) - 1;//复用变量
			line[path_length] = L'\0';
			command += L'\'';
			command += line;
			command += L"'";
			//读入剩余参数
			while (fgetws(line, 1024, fp))
			{
				path_length = lstrlenW(line) - 1;//复用变量
				line[path_length] = L'\0';
				command += L",'";
				command += line;
				command += L'\'';
			}
		}
		//完善命令并执行
		command += L" -Verb RunAs\"";
		ShellExecute(NULL, L"open", L"powershell.exe", command.c_str(), NULL, SW_HIDE);
		return;
	}
	//否则就是有管理员权限的状态，不用从文件读取，直接运行
	wstring command = L"-NoProfile -WindowStyle Hidden -Command \"Start-Process '";
	command += argv[1];//写入目标程序路径
	command += L"'";
	//如果有参数
	if (argc > 2)
	{
		//首个参数特殊处理
		command += L" -ArgumentList ";
		command += L'\'';
		command += argv[2];
		command += L"'";
		//读入剩余参数
		for (int i = 3; i < argc; ++i)
		{
			command += L",'";
			command += argv[i];
			command += L'\'';
		}
	}
	//完善命令并执行
	command += L" -Verb RunAs\"";
	ShellExecute(NULL, L"open", L"powershell.exe", command.c_str(), NULL, SW_HIDE);
	return;
}

bool IsAdmin()
{
	BOOL isAdmin = FALSE;
	PSID adminGroup = NULL;

	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (AllocateAndInitializeSid(&NtAuthority, 2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup))
	{

		CheckTokenMembership(NULL, adminGroup, &isAdmin);
		FreeSid(adminGroup);
	}

	return isAdmin;
}
