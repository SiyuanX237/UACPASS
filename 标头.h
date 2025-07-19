#pragma once
#include <iostream>
#include <windows.h>
#include <format>
#include <string>
#include <D:\C files\myfunc.h>
#define MAX_PATH 260
using namespace std;


extern int argc;
extern LPTSTR* argv;

bool IsAdmin();

void Config();

void Execute();

void ShowConsole();

void int_read(int* number);

void TaskMode();

void RegMode();

void About();

void AddTask();

void RemoveTask();

void OpenTask();

void AddReg();

void OpenReg();

void path_read(wchar_t* Destination);
