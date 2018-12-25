#include"Header.h"

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void changecolor(char*str, short color) {

	SetConsoleTextAttribute(h, color);
	cout << str;
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

double deadline(tm*now, Student*name) {

	struct tm a = { 0,0,0,now->tm_mday,now->tm_mon,now->tm_year }; //меньший год now date
	struct tm b = { 0,0,0,name->dld.day,name->dld.month - 1, name->dld.year - 1900 };  //больший год dead line
	time_t x = mktime(&a);
	time_t y = mktime(&b);

	return difftime(y, x) / (60 * 60 * 24);
}

void inccorect_pass() {

	SetConsoleTextAttribute(h, wOldColorAttrs);
	gotoxy(25, 16);
	changecolor(new char[30]{ "Login/Password is incorrect!" }, 4);
	gotoxy(25, 17);
	changecolor(new char[18]{ "Please try again." }, 4);
	SetConsoleTextAttribute(h, wOldColorAttrs);
	gotoxy(0, 20);
	Sleep(2000);
	system("cls");
}

void print_stud(Student*name) {

	cout << "Login: " << name->login;
	for (size_t i = 20; i > strlen(name->login) + 1; i--) { cout << " "; }
	cout << "Password: " << name->pass << endl << endl;

	cout << "Name: " << name->name;
	for (size_t i = 20; i > strlen(name->name); i--) { cout << " "; }
	cout << "Surname: " << name->surname << endl << endl;

	cout << "Age: " << name->age;
	for (size_t i = 20; i > 1; i--) { cout << " "; }
	cout << "Contact number: " << name->mobile << endl << endl;
	cout << "Percent of sale: " << name->sale << "%";

	for (size_t i = 20; i > 14; i--) { cout << " "; }

	cout << "Deadline in days: " << deadline(now, name) << endl;
}

void print_group(Group* name) {

	system("cls");
	cout << "\nGroup name: " << name->name << endl << endl;
	cout << "Students: \n\n";
	for (size_t i = 0; i < name->quantity; i++)
	{
		cout << i + 1 << ": " << name->students[i]->name << " " << name->students[i]->surname << endl;
	}
	cout << "\n";
}

Student* creation() {
	system("cls");

	Student* student = new Student{};
	char * tmp = new char[30]{ '\0' };

	cout << "\n New student\n\n";
	cout << "Enter your login: ";
	cin.ignore();
	cin.getline(tmp, 30);
	int le = (strlen(tmp) + 1);
	student->login = new char[le] {'\0'};
	strcpy_s(student->login, le, tmp);

	cout << "Enter your pass: ";
	cin.getline(tmp, 30);
	le = (strlen(tmp) + 1);
	student->pass = new char[le] {'\0'};
	strcpy_s(student->pass, le, tmp);

	cout << "Enter your Name: ";
	cin.getline(tmp, 30);
	le = (strlen(tmp) + 1);
	student->name = new char[le] {'\0'};
	strcpy_s(student->name, le, tmp);

	cout << "Enter your Surname: ";
	cin.getline(tmp, 30);
	le = (strlen(tmp) + 1);

	student->surname = new char[le] {'\0'};
	strcpy_s(student->surname, le, tmp);

	cout << "Enter your mobile: ";
	cin.getline(tmp, 30);
	le = (strlen(tmp) + 1);
	student->mobile = new char[le] {'\0'};
	strcpy_s(student->mobile, le, tmp);

	cout << "enter your age: ";
	cin >> student->age;

	cout << "enter %of sale: ";
	cin >> student->sale;

	delete tmp;
	return student;
}

void aze_rus(char*str, short x) {
	short a = 12;
	if (strlen(str) < 4) {
		gotoxy(x, a++);
		cout << char(201) << char(205) << char(205) << char(205) << char(187);
		gotoxy(x, a++);
		cout << char(186) << str << char(186);
		gotoxy(x, a);
		cout << char(200) << char(205) << char(205) << char(205) << char(188);

	}
	else {
		a = 12;
		gotoxy(x, a++);
		cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(187);
		gotoxy(x, a++);
		cout << char(186) << str << char(186);
		gotoxy(x, a);
		cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(188);
	}

}

void save(Group**groups, short count) {

	FILE* file = nullptr;
	fopen_s(&file, "studentbase.719", "wb");
	if (file) {
		fwrite(&count, sizeof(short), 1, file);

		for (size_t i = 0; i < count; i++)
		{
			short nameLength = strlen(groups[i]->name);

			fwrite(&nameLength, sizeof(short), 1, file);
			fwrite(groups[i]->name, sizeof(char), nameLength, file);
			fwrite(&groups[i]->quantity, sizeof(groups[i]->quantity), 1, file);

			for (size_t j = 0; j < groups[i]->quantity; j++)
			{
				int tmplength = strlen(groups[i]->students[j]->login);
				fwrite(&tmplength, sizeof(short), 1, file);
				fwrite(groups[i]->students[j]->login, sizeof(char), tmplength, file);

				tmplength = strlen(groups[i]->students[j]->pass);
				fwrite(&tmplength, sizeof(short), 1, file);
				fwrite(groups[i]->students[j]->pass, sizeof(char), tmplength, file);

				tmplength = strlen(groups[i]->students[j]->name);
				fwrite(&tmplength, sizeof(short), 1, file);
				fwrite(groups[i]->students[j]->name, sizeof(char), tmplength, file);

				tmplength = strlen(groups[i]->students[j]->surname);
				fwrite(&tmplength, sizeof(short), 1, file);
				fwrite(groups[i]->students[j]->surname, sizeof(char), tmplength, file);

				tmplength = strlen(groups[i]->students[j]->mobile);
				fwrite(&tmplength, sizeof(short), 1, file);
				fwrite(groups[i]->students[j]->mobile, sizeof(char), tmplength, file);

				fwrite(&groups[i]->students[j]->age, sizeof(groups[i]->students[j]->age), 1, file);
				fwrite(&groups[i]->students[j]->sale, sizeof(groups[i]->students[j]->sale), 1, file);

				fwrite(&groups[i]->students[j]->dld.day, sizeof(groups[i]->students[j]->dld.day), 1, file);
				fwrite(&groups[i]->students[j]->dld.month, sizeof(groups[i]->students[j]->dld.month), 1, file);
				fwrite(&groups[i]->students[j]->dld.year, sizeof(groups[i]->students[j]->dld.year), 1, file);
			}
		}
		fclose(file);
	}
}

Group** read() {
	FILE* file = nullptr;
	fopen_s(&file, "studentbase.719", "rb");
	if (file) {
		short groupCount = 0;
		fread_s(&groupCount, sizeof(short), sizeof(short), 1, file);
		Group** groups = new Group*[groupCount];

		for (size_t i = 0; i < groupCount; i++)
		{
			Group * gr = new Group;
			short nameLength = 0;
			fread_s(&nameLength, sizeof(short), sizeof(short), 1, file);
			gr->name = new char[nameLength + 1]{};
			fread_s(gr->name, nameLength + 1, sizeof(char), nameLength, file);
			fread_s(&gr->quantity, sizeof(short), sizeof(short), 1, file);

			gr->students = new Student*[gr->quantity]{};

			for (int j = 0; j < gr->quantity; j++) {

				Student* stud = new Student;
				short tmplength = 0;

				fread_s(&tmplength, sizeof(short), sizeof(short), 1, file);
				stud->login = new char[tmplength + 1]{};
				fread_s(stud->login, tmplength + 1, sizeof(char), tmplength, file);

				fread_s(&tmplength, sizeof(short), sizeof(short), 1, file);
				stud->pass = new char[tmplength + 1]{};
				fread_s(stud->pass, tmplength + 1, sizeof(char), tmplength, file);

				fread_s(&tmplength, sizeof(short), sizeof(short), 1, file);
				stud->name = new char[tmplength + 1]{};
				fread_s(stud->name, tmplength + 1, sizeof(char), tmplength, file);

				fread_s(&tmplength, sizeof(short), sizeof(short), 1, file);
				stud->surname = new char[tmplength + 1]{};
				fread_s(stud->surname, tmplength + 1, sizeof(char), tmplength, file);

				fread_s(&tmplength, sizeof(short), sizeof(short), 1, file);
				stud->mobile = new char[tmplength + 1]{};
				fread_s(stud->mobile, tmplength + 1, sizeof(char), tmplength, file);

				fread_s(&stud->age, sizeof(short), sizeof(short), 1, file);
				fread_s(&stud->sale, sizeof(short), sizeof(short), 1, file);

				fread_s(&stud->dld.day, sizeof(short), sizeof(short), 1, file);
				fread_s(&stud->dld.month, sizeof(short), sizeof(short), 1, file);
				fread_s(&stud->dld.year, sizeof(short), sizeof(short), 1, file);

				gr->students[j] = stud;
			}

			groups[i] = gr;
		}

		fclose(file);
		return groups;
	}
	return nullptr;
}

void add_stud(Group* group, Student*student) {

	Student**tmp = new Student*[group->quantity + 1]{};
	Student**tmp1 = group->students;

	for (size_t i = 0; i < group->quantity; i++)
	{
		tmp[i] = group->students[i];
	}
	tmp[group->quantity] = student;

	group->students = tmp;
	group->quantity += 1;
	delete[] tmp1;
}

void delete_stud(Group* group, size_t index) {

	Student**tmp = new Student*[group->quantity - 1]{};
	Student**tmp1 = group->students;
	short x = 0;
	for (size_t i = 0; i < group->quantity; i++)
	{
		if (i + 1 != index)
			tmp[x++] = group->students[i];
	}
	group->students = tmp;
	group->quantity -= 1;
	delete[] tmp1;
}

bool move_stud(Group**groups, short tmp_group, Student*name) {

	//кол во групп
	int sizeofgroups = 2;
	short y = 0, key = 0;
	while (true) {

		system("cls");
		cout << "choose group for moving student:\n\n";
		for (size_t i = 0; i < sizeofgroups; i++)
		{
			if (i == y) {
				SetConsoleTextAttribute(h, FOREGROUND_BLUE);
				cout << groups[i]->name << endl;
				SetConsoleTextAttribute(h, wOldColorAttrs);
			}
			else { cout << groups[i]->name << endl; }
		}

		key = _getch();
		if (key == 224) { key = _getch(); }
		else if (key == 13) { break; }

		switch (key) {
		case 72: { if (y - 1 > -1) { y -= 1; } break; }
		case 80: { if (y + 1 < sizeofgroups) { y += 1; } break; }
				 break;
		}
	}

	short counter = 0;
	int index = 0;

	while (counter < groups[tmp_group]->quantity) {

		if (name == groups[tmp_group]->students[index]) { break; }
		index++;
		counter++;
	}

	index += 1;
	for (size_t i = 0; i < groups[y]->quantity; i++) {
		if (name == groups[y]->students[i]) return false;
	}

	add_stud(groups[y], groups[tmp_group]->students[index - 1]);
	delete_stud(groups[tmp_group], index);
	return true;
}

Group* selection(short index, Group**groups) {

	if (index == 0) return groups[0];
	else if (index == 1) return groups[1];
	else return nullptr;
}

short login_pass(Group *group, Student*&usingacc) {

	char login_check[10]{};
	char pass_check[13]{};
	Admin admin;
	admin.InitializeAdmin("admin", "admin");

	short counter = 0;
	short count = 0;
	char sym = 0;

	gotoxy(26, 5);
	cout << "Login: ";
	cin.clear();
	fflush(stdin);
	fseek(stdin, 0, SEEK_END);

	cin.getline(login_check, 10);

	gotoxy(26, 8);
	cout << "Pass: ";

	while (true) {
		//возможно на некоторых компах будет требоать лишь 1 гетч
		//_getch();
		sym = _getch();

		if (sym == 13) break;
		else if (sym == 8 && counter > 0 && count < 13) {
			_putch('\b');
			_putch(' ');
			_putch('\b');
		}
		else if (count < 13) {
			_putch('*');
		}

		if (sym == 8 && counter > 0) {

			pass_check[counter - 1] = '\0';
			--counter;
			--count;
		}
		else {
			pass_check[counter++] = sym;
			count++;
		}

	}
	cout << endl;
	//проверка на администратора
	if (strcmp(pass_check, admin.pass) == 0 && strcmp(login_check, admin.login) == 0) {

		SetConsoleTextAttribute(h, FOREGROUND_GREEN);
		gotoxy(41, 10);
		cout << "\\(^o^)/";
		Sleep(650);

		//here
		SetConsoleTextAttribute(h, wOldColorAttrs);
		return 1;
	}

	short x = 0;
	while (x < group->quantity) {

		if (strcmp(group->students[x]->login, login_check) == 0) {
			break;
		}
		++x;
	}
	//проверка нет студента или не прав пароль
	if (x == group->quantity) { return 0; }

	if (strcmp(pass_check, group->students[x]->pass) == 0 && strcmp(login_check, group->students[x]->login) == 0) {

		SetConsoleTextAttribute(h, FOREGROUND_GREEN);
		gotoxy(41, 10);
		cout << "\\(^o^)/";
		Sleep(650);
		//here

		SetConsoleTextAttribute(h, wOldColorAttrs);
		//правельный студент
		usingacc = group->students[x];
		return 2;
	}
	//не прав студент лог пароль 
	else return 0;
}

short account(Student* name) {

	if (name == nullptr)
		return 0;

	system("cls");
	cout << endl << "welcome to your profile " << name->name << " " << name->surname << " !\n\n\n";
	print_stud(name);
	cout << "\n\n Log out" << "                    " << "Edit profile" << endl;

	char c = 75;
	char tmp = c;

	while (true) {

		if (c == 75) {


			while (!_kbhit()) {
				SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
				gotoxy(1, 13);
				cout << " Log out\n";
				Sleep(350);
				SetConsoleTextAttribute(h, wOldColorAttrs);
				gotoxy(1, 13);
				cout << " Log out\n";
				Sleep(350);
			}
			c = _getch();
			if (c == 13)return short(tmp);
			else if (c == 224)
				c = _getch();
			if (c == 75 || c == 77)
				tmp = c;
		}

		else if (c == 77) {

			while (!_kbhit()) {
				SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);
				gotoxy(28, 13);
				cout << "Edit profile\n";
				Sleep(350);
				SetConsoleTextAttribute(h, wOldColorAttrs);
				gotoxy(28, 13);
				cout << "Edit profile\n";
				Sleep(350);
			}
			c = _getch();
			if (c == 13)return short(tmp);
			else if (c == 224)
				c = _getch();
			if (c == 77 || c == 75)
				tmp = c;
		}
		else {

			c = tmp;
		}
	}
}

short menu() {

	gotoxy(25, 1);
	short x = 4;
	cout << "Beta Program prototype!" << endl;
	for (size_t i = 1; i < 3; i++)
	{
		gotoxy(25, x++);
		cout << char(201);
		for (size_t i = 0; i < 21; i++)  cout << char(205);

		cout << char(187);

		gotoxy(25, x); cout << char(186);

		gotoxy(47, x++); cout << char(186);

		gotoxy(25, x); cout << char(200);

		for (size_t i = 0; i < 21; i++)	cout << char(205);

		cout << char(188);
		x++;
	}

	gotoxy(25, 11);
	cout << "Choose group:";

	short c = 0;
	short arrow = 0;

	while (true) {

		SetConsoleTextAttribute(h, arrow == 0 ? FOREGROUND_BLUE : wOldColorAttrs);
		aze_rus(new char[4]{ "Aze" }, 25);
		SetConsoleTextAttribute(h, wOldColorAttrs);
		SetConsoleTextAttribute(h, arrow == 1 ? FOREGROUND_BLUE : wOldColorAttrs);
		aze_rus(new char[4]{ "Rus" }, 31);
		SetConsoleTextAttribute(h, wOldColorAttrs);
		SetConsoleTextAttribute(h, arrow == 2 ? FOREGROUND_BLUE : wOldColorAttrs);
		aze_rus(new char[5]{ "Quit" }, 42);
		SetConsoleTextAttribute(h, wOldColorAttrs);

		c = _getch();
		if (c == 13) return arrow;
		else if (c == 224) c = _getch();

		switch (c) {
		case 75: {if (arrow - 1 > -1)arrow -= 1; break; }
		case 77: {if (arrow + 1 < 3)arrow += 1; break; }
				 break;
		}

	}
}

bool mobilecheck(char* str) {

	for (size_t i = 0; i < strlen(str); i++) {
		if (str[i] < '0' || str[i] > '9') return false;
	}
	return true;

}

void edit_info(Group** groups, Student* name, bool admin, short tmp_group) {

	short x = 0, y = 0;
	short counter = 0;
	short key = 0;
	system("cls");
	while (true) {

		cout << "\nWelcome to Editor!\n\n\n";

		if (x == 0 && y == 0) {

			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Login: " << name->login;
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Login: " << name->login;

		for (size_t i = 20; i > strlen(name->login) + 1; i--) 	cout << " ";

		if (x == 1 && y == 0) {

			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Password: " << name->pass << "\n\n";
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Password: " << name->pass << "\n\n";

		if (x == 0 && y == 1) {

			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Name: " << name->name;
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Name: " << name->name;

		for (size_t i = 20; i > strlen(name->name); i--) cout << " ";

		if (x == 1 && y == 1) {

			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Surname: " << name->surname << "\n\n";
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Surname: " << name->surname << "\n\n";

		if (x == 0 && y == 2) {

			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Age: " << name->age;
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Age: " << name->age;

		for (size_t i = 20; i > 1; i--) cout << " ";

		if (x == 1 && y == 2) {

			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Contact number: " << name->mobile << "\n\n";
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Contact number: " << name->mobile << "\n\n";

		if (x == 0 && y == 3) {

			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Percent of sale: " << name->sale << "%";
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Percent of sale: " << name->sale << "%";

		for (size_t i = 20; i > 14; i--) cout << " ";

		if (x == 1 && y == 3) {

			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Dedline in days: " << deadline(now, name) << "\n\n";
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Dedline in days: " << deadline(now, name) << "\n\n";

		if (x == 0 && y == 4) {
			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << " Back";
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << " Back";

		for (size_t i = 21; i > 0; i--) cout << " ";

		if (x == 1 && y == 4) {
			SetConsoleTextAttribute(h, FOREGROUND_BLUE);
			cout << "Move student \n\n";
			SetConsoleTextAttribute(h, wOldColorAttrs);
		}
		else cout << "Move student \n\n";

		key = _getch();
		if (key == 224) { key = _getch(); }

		if (key == 13) {

			cout << "\n\n";

			if (x == 0 && y == 0) {

				cout << "Enter new login: ";
				cin.getline(name->login, 17);
				cin.clear();
				//	cin.ignore();
				fflush(stdin);
				fseek(stdin, 0, SEEK_END);
			}
			else if (x == 1 && y == 0) {
				counter = 0;
				cout << "Enter new Password: ";
				cin.getline(name->pass, 17);
				cin.clear();
				//	cin.ignore();
				fflush(stdin);
				fseek(stdin, 0, SEEK_END);
			}
			else if (x == 0 && y == 1) {
				counter = 0;
				do {
					cout << "Enter new Name: ";
					cin.getline(name->name, 17);
					cin.clear();
					//	cin.ignore();
					fflush(stdin);
					fseek(stdin, 0, SEEK_END);
					if (mobilecheck(name->name) == true) {
						changecolor(new char[24]{ "\nIncorrect information\n" }, 4);
						Sleep(1000);
					}
				} while (mobilecheck(name->name) == true);
			}
			else if (x == 1 && y == 1) {
				counter = 0;
				do {
					cout << "Enter new Surname: ";
					cin.getline(name->surname, 17);
					cin.clear();
					//	cin.ignore();
					fflush(stdin);
					fseek(stdin, 0, SEEK_END);
					if (mobilecheck(name->surname) == true) {
						changecolor(new char[24]{ "\nIncorrect information\n" }, 4);
						Sleep(1000);
					}
				} while (mobilecheck(name->surname) == true);
			}
			else if (x == 0 && y == 2) {
				cout << "Enter new Age: ";
				cin >> name->age;
			}
			else if (x == 1 && y == 2) {
				do {
					cout << "Enter new Mobile: ";
					cin.getline(name->mobile, 12);
					cin.clear();
					//cin.ignore();
					fflush(stdin);
					fseek(stdin, 0, SEEK_END);
					if (mobilecheck(name->mobile) == false) {
						changecolor(new char[24]{ "\nIncorrect information\n" }, 4);
						Sleep(1000);
					}
				} while (mobilecheck(name->mobile) == false);

			}
			else if (x == 0 && y == 3) {

				do {
					cout << "Enter new sale: ";
					cin >> name->sale;
					if (name->sale > 50) {
						changecolor(new char[30]{ "\nNo more than 50%.Try again\n" }, 4);
						Sleep(1000);
					}
				} while (name->sale > 50);
			}
			else if (x == 1 && y == 3) {
				cout << "Enter new Deadline ex(31 12 9999): ";
				cin >> name->dld.day;
				cin >> name->dld.month;
				cin >> name->dld.year;
			}
			else if (x == 1 && y == 4) {
				bool checkstudentingroup = false;
				do {
					checkstudentingroup = move_stud(groups, tmp_group, name);
					if (checkstudentingroup == false) {
						cout << "\nThere is already this student, choose another group\n";
						Sleep(3000);
					}
				} while (checkstudentingroup == false);
			}
			else if (x == 0 && y == 4) {
	
				return;
			}

			changecolor(new char[18]{ "\nChanges Saved\n" }, 2);
			Sleep(1000);
		}


		switch (key)
		{
		case 72: {
			if (admin == true && y == 4) {

				if (y - 1 > -1)y -= 1;
			}
			else if (admin == false && y == 4) {

				if (y - 1 > -1)y -= 2;
			}
			else {

				if (y - 1 > -1)y -= 1;
			}

			break;
		}
		case 80: {
			if (admin == true && y == 2) {

				if (y + 1 <= 4)y += 1;
			}
			else if (admin == false && y == 2) {
				if (x == 1)x = 0;
				if (y + 1 <= 4)y += 2;
			}
			else {
				if (y + 1 <= 4)y += 1;
			}

			break;
		}
		case 75: {
			if (x - 1 > -1)x -= 1; break; }
		case 77: {
			if (admin == false) {

				if (x + 1 < 2 && y != 4)x += 1; break;
			}
			else { if (x + 1 < 2)x += 1; break; }
		}
				 break;
		}
		system("cls");
	}
}

Student* admin_panel(Group**groups, short &tmp_group) {
	while (true) {

		system("cls");

		cout << "\nWelcome to Admin panel! \n\n\n";
		cout << "Choose group:\n\n";

		short key = 75;

		while (true) {
			gotoxy(0, 6);

			if (tmp_group == 0) changecolor(new char[16]{ "1: Azerbaijan\n" }, 1);
			else cout << "1: Azerbaijan\n";

			if (tmp_group == 1) changecolor(new char[13]{ "2: Russian\n" }, 1);
			else cout << "2: Russian\n";

			if (tmp_group == 2) changecolor(new char[13]{ "\n\n  Log out" }, 1);
			else cout << "\n\n  Log out";

			cout << "                    " << "Edit\n";

			key = _getch();
			if (key == 13) {

				if (tmp_group != 2) {

					gotoxy(29, 10);
					changecolor(new char[7]{ "Edit\n" }, 2);
					Sleep(300);
					break;
				}
				else if (tmp_group == 2)
					return nullptr;
			}
			else if (key == 224)
				key = _getch();
			switch (key)
			{
			case 80: { if (tmp_group + 1 < 3)tmp_group += 1;    break; }
			case 72: {if (tmp_group - 1 > -1)  tmp_group -= 1;   break; }
					 break;
			}
		}

		short tmp = 0;

		while (true) {

			system("cls");

			cout << "\nGroup name: " << selection(tmp_group, groups)->name << "\n\n";
			if (tmp == 0) changecolor(new char[15]{ "Add Student\n\n" }, 1);
			else cout << "Add Student\n\n";

			cout << "Students: \n\n";

			for (size_t i = 0; i < selection(tmp_group, groups)->quantity; i++)
			{
				if (tmp == i + 1) {

					SetConsoleTextAttribute(h, FOREGROUND_BLUE);
					cout << i + 1 << ": " << selection(tmp_group, groups)->students[i]->name << " " << selection(tmp_group, groups)->students[i]->surname << endl;
					SetConsoleTextAttribute(h, wOldColorAttrs);
				}
				else
					cout << i + 1 << ": " << selection(tmp_group, groups)->students[i]->name << " " << selection(tmp_group, groups)->students[i]->surname << endl;
			}
			cout << "\n";

			if (tmp - 1 == selection(tmp_group, groups)->quantity) changecolor(new char[9]{ "\n\n  Back" }, 1);
			else cout << "\n\n  Back";

			cout << "                       " << "Edit" << endl;

			key = _getch();
			if (key == 13) {
				if (tmp == selection(tmp_group, groups)->quantity + 1) { break; }
				else if (tmp == 0) { add_stud(groups[tmp_group], creation()); }
				else if (tmp > 0 && tmp <= selection(tmp_group, groups)->quantity) {

					gotoxy(29, 10 + groups[tmp_group]->quantity);
					changecolor(new char[7]{ "Edit\n" }, 2);
					Sleep(300);
					return selection(tmp_group, groups)->students[tmp - 1];
				}
				else return nullptr;
			}
			else if (key == 224)key = _getch();

			switch (key)
			{
			case 80: { if (tmp < selection(tmp_group, groups)->quantity + 1)tmp += 1; break; }
			case 72: {if (tmp - 1 > -1)  tmp -= 1; break; }
					 break;
			}
		}
	}
}

short admin_editor() {

	short key = 0;
	short y = 0;
	system("cls");
	while (true) {

		gotoxy(0, 0);
		cout << "\nAdmin editor, choose what to do: \n\n";

		changecolor(new char[19]{ "1.Delete Student\n" }, y == 0 ? 1 : 7);
		changecolor(new char[17]{ "2.Edit Student\n" }, y == 1 ? 1 : 7);
		changecolor(new char[10]{ "\n\n Back\n" }, y == 2 ? 1 : 7);

		key = _getch();
		if (key == 224) { key = _getch(); }
		else if (key == 13) { return y; }

		switch (key) {
		case 72: { if (y - 1 > -1) { y -= 1; } break; }
		case 80: { if (y + 1 < 3) { y += 1; } break; }
				 break;
		}
	}

}

