#include"addings.h"
#include"FileManager_NoGraphic.h"

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
WORD wOldColorAttrs;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

void changecolor(string str, short color) {

	SetConsoleTextAttribute(h, color);
	cout << str;
	SetConsoleTextAttribute(h, wOldColorAttrs);
}
int del(const char * csDeleteFolderPath_i)
{
	int nFolderPathLen = strlen(csDeleteFolderPath_i);
	TCHAR *pszFrom = new TCHAR[nFolderPathLen + 2];
	strcpy_s(pszFrom, nFolderPathLen + 1, csDeleteFolderPath_i);
	pszFrom[nFolderPathLen] = 0;
	pszFrom[++nFolderPathLen] = 0;
	SHFILEOPSTRUCT stSHFileOpStruct = { 0 };
	stSHFileOpStruct.wFunc = FO_DELETE;
	stSHFileOpStruct.pFrom = pszFrom;
	stSHFileOpStruct.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR | FOF_SILENT | FOF_FILESONLY;
	stSHFileOpStruct.fAnyOperationsAborted = FALSE;
	int nFileDeleteOprnRet = SHFileOperation(&stSHFileOpStruct);
	delete[]pszFrom;
	if (0 != nFileDeleteOprnRet)
	{
		return 1;
	}
	return 0;
}

void MainProcess() {

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	FileManager_Graphic test;
	FileManager_NoGraphic test1;
	Graphic_Choice *check[2] = { &test1,&test };
	cout << "enter 1 or 0 graphic or without: ";
	int choice = 0;
	cin >> choice;
	system("cls");

	
	check[choice]->DiskSelection();

	/*try
	{
		check[choice]->DiskSelection();

	}
	catch (const std::exception&ex)
	{
		cout << ex.what() << endl;
		cout << "do NOT cin other numbers lol :D\n";
		return;
	}*/
	do
		check[choice]->print();
	while (check[choice]->command());

}
