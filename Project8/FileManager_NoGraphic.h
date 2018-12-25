#pragma once
#include"FileManager_Graphic.h"

class FileManager_NoGraphic final :public FileManager_Graphic {
protected:
	void WayBack()override;
	void WayForward(string a)override;
	void MakeDir()override;
	void RemoveDir()override;
	void RenameDir()override;
	
public:
	FileManager_NoGraphic();
	void DiskSelection()override;
	void print()override;
	bool command()override;
	~FileManager_NoGraphic();
};
