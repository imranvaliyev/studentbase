#pragma once
#include <iostream> 
#include <direct.h>
#include<vector>
#include<string>
#include <io.h>     
#include<windows.h> 


using namespace std;

extern HANDLE h;
extern WORD wOldColorAttrs;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

void changecolor(string str, short color);
int del(const char * csDeleteFolderPath_i);

class Graphic_Choice {
public:
	virtual void DiskSelection() = 0;
	virtual void print() = 0;
	virtual bool command() = 0;
};

void MainProcess();
