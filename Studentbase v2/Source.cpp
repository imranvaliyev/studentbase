#include"Header.h"

time_t t = time(0);
tm* now = new tm();

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
WORD wOldColorAttrs;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


int main() {

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	//студенты

	Student* imran = new Student  { new char[20]{ "s" },      new char[20]{ "s" },   new char  [20]{ "Imran" },new char[20]{ "Veliyev" },new char[12]{ "0507190012" },21,10,{1,8,2018} };
	Student* noname1 = new Student{ new char[20]{ "noname1" },new char[20]{ "noname123" },new char  [20]{ "No" },new char[20]{ "Name1" },new char[12]{ "000111222" },18,50,{ 1,10,2018 } };
	Student* noname2 = new Student{ new char[20]{ "noname2" },new char[20]{ "noname1234" },new char [20]{ "No" },new char[20]{ "Name2" },new char[12]{ "111333" },15,40,{ 19,7,2018 } };
	Student* noname3 = new Student{ new char[20]{ "noname3" },new char[20]{ "noname12345" },new char[20]{ "No" },new char[20]{ "Name3" },new char[12]{ "00001333" },50,20 ,{ 1,1,2019 } };
	//массив студентов
	short rsize = 2, asize = 2;
	Student **rstud = new Student*[rsize] { imran, noname1 };
	Student **astud = new Student*[asize] { noname2, noname3 };
	//группы
	Group *rus = new Group{ new char[10]{ "russian" },rsize,rstud };
	Group *aze = new Group{ new char[15]{ "azerbaijan" },asize,astud };

	Group** groups = new Group*[2]{};
	groups[0] = aze;
	groups[1] = rus;
	*/


	Group** groups = read();

	// part of time
	localtime_s(now, &t);

	// студент на которым идет работа
	Student*  usingacc = nullptr;
	short menunum = 0;
	short smthng = 719;
	short tmp_group = 0;

	bool  tmp_admin = false;
	PlaySound(TEXT("pirates.wav"), NULL, SND_ASYNC);

	//цикл всей игры
	while (true) {

		usingacc = nullptr;
		menunum = 0;
		smthng = 719;
		tmp_group = 0;
		tmp_admin = false;

		system("cls");

		menunum = menu();
		//сохранение всех изменений
		if (menunum == 2) { save(groups, 2); return 0; }

		smthng = login_pass(selection(menunum, groups), usingacc);

		// на случай, если предыдущий ввод завершился с ошибкой
		cin.clear();
		//в случае не правильного логина и пароля
		if (smthng == 0) { inccorect_pass(); }
		//админ и редактирование
		else if (smthng == 1) {
			while (true) {
				tmp_admin = true;
				usingacc = admin_panel(groups, tmp_group);

				if (usingacc == nullptr)  break;
				else {
					switch (admin_editor()) {
					case 0: {
						short i = 0;
						while (i < groups[tmp_group]->quantity) {
							if (usingacc == groups[tmp_group]->students[i])	break;
							i++;
						}

						i += 1;
						delete_stud(groups[tmp_group], i);
						changecolor(new char[15]{ "\n\n Deleted\n" }, 2);
						Sleep(1000);
						break;
					}
					case 1: {edit_info(groups, usingacc, tmp_admin, tmp_group); break; }
					}
				}
			}

			tmp_admin = false;
		}
		//верный пароль
		else {
			while (true) {
				menunum = account(usingacc);
				//если нажал back
				if (menunum == 75)
					break;
				//если edit info
				else edit_info(groups, usingacc, tmp_admin, menunum);
			}
		}
	}

	return 0;
}

