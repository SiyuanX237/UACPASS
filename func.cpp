#define _CRT_SECURE_NO_WARNINGS
#include "��ͷ.h"


//����ģʽ
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
			"��ѡ��UAC������ģʽ:\n"
			"1.�ƻ�����ģʽ(�Բ������Ĺ���ԱȨ������)\n"
			"2.ע���ģʽ(ǿ���ó�������ͨȨ������)\n"
			"3.���ڱ�����\n"
			"4.�˳�\n"
			"���ѡ��:"
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
			printf("�����ѽ�����3����˳�...");
			Sleep(3000);
			return;
		}
		system("cls");
	}
}

//��ʾ����̨
void ShowConsole()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	cin.clear();
	cout.clear();
}

//int���Ͷ�ȡ������
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
	if (sscanf(buffer, "%d", number) != 1)//����ȷ��ֵ
	{
		*number = -1;
	}
	return;
}

//�ƻ�����ģʽ
void TaskMode()
{
loop:
	printf(
		"��ѡ����:\n"
		"1.���UAC�������ƻ�����\n"
		"2.�Ƴ�UAC�������ƻ�����\n"
		"3.�򿪼ƻ�����\n"
		"4.�ص�������\n"
		"���ѡ��:"
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

//��Ӽƻ�����
void AddTask()
{
	wstring command;
	command = format(L"/create /tn \\UACPass\\UACPass /tr \"\\\"{}\\\" 1 \" /sc ONCE /sd 1946/02/14 /st 11:45 /rl HIGHEST",argv[0]);
	ShellExecute(NULL, L"open", L"schtasks.exe", command.c_str(), NULL, SW_HIDE);
	printf("��ӳɹ�!\n");
	system("pause");
	return;
}

//�Ƴ��ƻ�����
void RemoveTask()
{
	ShellExecute(NULL, L"open", L"schtasks.exe", L"/delete /tn \\UACPass\\UACPass /f", NULL, SW_HIDE);
	printf("�Ƴ��ɹ�!\n");
	system("pause");
	return;
}

//�򿪼ƻ����������
void OpenTask()
{
	ShellExecute(NULL, L"open", L"taskschd.msc", NULL, NULL, SW_NORMAL);
	return;
}

//ע���ģʽ
void RegMode()
{
loop:
	printf(
		"��ѡ����:\n"
		"1.���UAC������ע���\n"
		"2.��ע���(ֻ���ֶ�ɾ���������)\n"
		"3.�ص�������\n"
		"���ѡ��:"
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

//���ע��������
void AddReg()
{
	printf("�����������UAC�������ĳ�������·��(��Ӻ��ƶ����򽫻�ʧЧ)\n·��:");
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
	printf("��ӳɹ�!\n");
	system("pause");
	return;
}

//·����ȡ
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

//�򿪶�Ӧע���λ��
void OpenReg()
{
	wchar_t path[] = L"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows NT\\CurrentVersion\\AppCompatFlags\\Layers";
	oreg(path);
	return;
}

//����
void About()
{
	printf(
		"UACPass��һ��UAC�������������ߣ�������UAC�����������ָ��һЩ�����ⵯ\n"
		"��ע���ߣ�Bilibili(�b-�b)�ĥ� ������˼\n"
	);
	system("pause");
	return;
}

//����ģʽ
void Execute()
{
	if (!IsAdmin())//�ȿ�����û��Ȩ��
	{
		//û�еĻ��üƻ�������Ȩ
		//д��������ݵ���ʱ�ļ�
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
		//���üƻ�������Ȩ
		ShellExecute(NULL, L"open", L"schtasks.exe", L"/run /tn \\UACPass\\UACPass", NULL, SW_HIDE);
		return;
	}
	//����Ȩ��ֱ������
	if (argc == 2 && argv[1][0] == L'1')//����Ǿ���״̬����Ҫ���ļ���ȡ����
	{
		//����ʱ�ļ���ȡ��������
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
		//Ŀ�������
		fgetws(line, 1024, fp);
		path_length = lstrlenW(line) - 1;//���ñ���
		line[path_length] = L'\0';
		command += line;//д��Ŀ�����·��
		command += L"' ";
		if (fgetws(line, 1024, fp))//����в���
		{
			//�׸��������⴦��
			command += L" -ArgumentList ";
			path_length = lstrlenW(line) - 1;//���ñ���
			line[path_length] = L'\0';
			command += L'\'';
			command += line;
			command += L"'";
			//����ʣ�����
			while (fgetws(line, 1024, fp))
			{
				path_length = lstrlenW(line) - 1;//���ñ���
				line[path_length] = L'\0';
				command += L",'";
				command += line;
				command += L'\'';
			}
		}
		//�������ִ��
		command += L" -Verb RunAs\"";
		ShellExecute(NULL, L"open", L"powershell.exe", command.c_str(), NULL, SW_HIDE);
		return;
	}
	//��������й���ԱȨ�޵�״̬�����ô��ļ���ȡ��ֱ������
	wstring command = L"-NoProfile -WindowStyle Hidden -Command \"Start-Process '";
	command += argv[1];//д��Ŀ�����·��
	command += L"'";
	//����в���
	if (argc > 2)
	{
		//�׸��������⴦��
		command += L" -ArgumentList ";
		command += L'\'';
		command += argv[2];
		command += L"'";
		//����ʣ�����
		for (int i = 3; i < argc; ++i)
		{
			command += L",'";
			command += argv[i];
			command += L'\'';
		}
	}
	//�������ִ��
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
