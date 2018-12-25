#include"FileManager_NoGraphic.h"

//class
void FileManager_NoGraphic::WayBack() {

	mask = way[0];
	if (way.size() == 1) {
		system("cls");
		DiskSelection();
		//cout << "Error, Default way\n";
	}
	else {
		way.pop_back();
		for (size_t i = 1; i < way.size(); i++) {

			cout << way[i] << endl;
			mask += way[i];
		}
		mask += "*.*";
	}
}
void FileManager_NoGraphic::WayForward(string a) {

	for (size_t i = 0; i < 3; i++)
		mask.pop_back();
	mask = mask + a + "\\*.*";

	searchId = _findfirst(mask.c_str(), &data);
	result = searchId;
	way.push_back(a + "\\");
}
void FileManager_NoGraphic::MakeDir() {

	string nameofdir;
	string forfun;
	cout << "\nEnter the name of folder: ";
	getline(cin, nameofdir);

	for (size_t i = 0; i < way.size(); i++)
		forfun += way[i];

	forfun += nameofdir;
	_mkdir(forfun.c_str());
	nameofdir.clear();
	forfun.clear();
	cout << "Created successfully!\n";
	Sleep(1000);
}
void FileManager_NoGraphic::RemoveDir() {
	string nameofdir;
	string forfun;
	cout << "\nEnter the name of folder which u want to remove: ";
	getline(cin, nameofdir);

	for (size_t i = 0; i < way.size(); i++)
		forfun += way[i];

	forfun += nameofdir;
	//_rmdir(); folders
	//int result = remove(forfun.c_str()); //files
	if (del(forfun.c_str()) != 0)

		perror("Error deleting file");
	else
		puts("File successfully deleted");

	nameofdir.clear();
	forfun.clear();
	Sleep(2000);
}
void FileManager_NoGraphic::RenameDir() {
	string newname;
	string oldname;
	string mainway;
	cout << "\nEnter the old name of folder: ";
	getline(cin, oldname);
	cout << "\nEnter the new name of folder: ";
	getline(cin, newname);

	for (size_t i = 0; i < way.size(); i++)
		mainway += way[i];

	int result = rename((mainway + oldname).c_str(), (mainway + newname).c_str());
	if (result == 0)
		puts("File successfully renamed");
	else
		perror("Error renaming file");

	newname.clear();
	oldname.clear();
	mainway.clear();
	Sleep(2000);
}
FileManager_NoGraphic::FileManager_NoGraphic() {}
void FileManager_NoGraphic::DiskSelection() {

	while (true) {

		string tmpshka;
		char disk;
		tmpshka.clear();
		way.clear();
		mask.clear();
		cout << "Chose logical drive C/D:\n" << "Enter: ";
		fseek(stdin, 0, SEEK_END);

		cin >> disk;
		if (disk == 'c')
			disk = 'C';
		else if (disk == 'd')
			disk = 'D';
		if (disk == 'C' || disk == 'D') {

			mask.push_back(disk);
			mask += ":\\*.*";

			searchId = _findfirst(mask.c_str(), &data);
			result = searchId;
			tmpshka.push_back(disk);
			tmpshka += ":\\";
			way.push_back(tmpshka);
			break;
		}
		else {
			system("cls");
			cout << "Try again...\n";
		}
	}
}
void FileManager_NoGraphic::print() {
	searchId = _findfirst(mask.c_str(), &data);
	result = searchId;

	system("cls");
	cout << mask << "\b\b\b   \n";
	prev_folders.clear();
	while (result != -1) {

		prev_folders.push_back(data.name);
		cout << data.name << endl;
		result = _findnext(searchId, &data);
	}
}
bool FileManager_NoGraphic::command()
{
	while (true) {

		string a;
		cout << "enter your command: ";
		fseek(stdin, 0, SEEK_END);
		getline(cin, a);
		cin.clear();

		//methods
		if (a == "back") {
			WayBack(); return 1;
		}
		else if (a == "create") {
			MakeDir(); return 1;
		}
		else if (a == "rename") {
			RenameDir(); return 1;
		}
		else if (a == "remove") {
			RemoveDir(); return 1;
		}
		else if (a == "quit")  return 0;

		else
			for (size_t i = 0; i < prev_folders.size(); i++)
				if (a == prev_folders[i]) {
					WayForward(a); return 1;
				}
		cout << "\n\nEror getway...\n";
		system("pause");
		system("cls");
		print();
	}
}
FileManager_NoGraphic::~FileManager_NoGraphic() {
	MyCommand.clear();
	mask.clear();
	way.clear();
	prev_folders.clear();
}



