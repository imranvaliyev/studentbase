#pragma once
#include"addings.h"

class FileManager_Graphic :public Graphic_Choice {
protected:
	string MyCommand;
	string mask;
	_finddata_t data;
	int searchId;
	int result;
	vector<string>way;
	vector<string>prev_folders;

	virtual void WayBack();
	virtual void WayForward(string a);
	virtual void MakeDir();
	virtual void RemoveDir();
	virtual void RenameDir();

public:

	FileManager_Graphic();
	void DiskSelection();
	void print();
	bool command();
	~FileManager_Graphic();
};
