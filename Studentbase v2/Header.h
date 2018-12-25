#pragma once
#include<iostream>
#include<Windows.h>
#include <cstring>
#include <stdio.h>
#include<conio.h>
#include<ctime>
#include<mmsystem.h>
#pragma comment (lib,"winmm.lib")

using namespace std;

extern time_t t;
extern tm* now;
extern HANDLE h;
extern WORD wOldColorAttrs;
extern CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

struct Admin {

	char* login;
	char* pass;

	void InitializeAdmin(const char * login, const char* pass) {
		this->login = new char[strlen(login) + 1];
		this->pass = new char[strlen(pass) + 1];
		strcpy_s(this->login, strlen(login) + 1, login);
		strcpy_s(this->pass, strlen(pass) + 1, pass);
	}
};
struct Date {
	short day;
	short month;
	short year;
};
struct Student {

	char*login;
	char*pass;
	char*name;
	char*surname;
	char* mobile;
	short age;
	short sale;
	Date dld;
};
struct Group {

	char*name;
	short quantity;
	Student**students;
};

bool mobilecheck(char* str);
void gotoxy(int x, int y);
double deadline(tm*now, Student*name);
void inccorect_pass();
void print_stud(Student*name);
void print_group(Group* name);
Student* creation();
void aze_rus(char*str, short x);
void changecolor(char*str, short color);
void save(Group**groups, short count);
Group** read();
void add_stud(Group* group, Student*student);
void delete_stud(Group* group, size_t index);
bool move_stud(Group**groups, short tmp_group, Student*name);
Group* selection(short index, Group**groups);
short login_pass(Group *group, Student*&usingacc);
short account(Student* name);
short menu();
void edit_info(Group** groups, Student* name, bool admin, short tmp_group);
Student* admin_panel(Group**groups, short &tmp_group);
short admin_editor();