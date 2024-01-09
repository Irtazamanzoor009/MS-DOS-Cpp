#pragma once
#include"DlinkList.h"
#include <string>
#include<ctime>
#include "file.h"
#include<iomanip>
#include <sstream>
using namespace std;
class Folder
{
public:
	string name;
	DoubleLinkedList<Folder*> folders;
	DoubleLinkedList<File*> files;
	Folder* parent;
	string owner;
	string path;
	string timeOfCreation;
	int size;
	bool isHidden;
	bool isReadOnly;

	Folder(string n = "New Folder", string path = "", Folder* parnt = nullptr, DoubleLinkedList<Folder*> folders = DoubleLinkedList<Folder*>(), DoubleLinkedList<File*> files = DoubleLinkedList<File*>())
	{
		name = n;
		owner = "Irtaza Manzoor";
		parent = parnt;
		this->path = path;
		//timeOfCreation = time;
		this->folders = folders;
		this->files = files;
		isHidden = false;
		isReadOnly = true;
		SaveTime();
		size = savesize();
	}

	int savesize()
	{
		return sizeof(*this);
	}

	void SaveTime()
	{
		time_t now = time(0);
		struct tm timeinfo;

		if (localtime_s(&timeinfo, &now) == 0) {
			char dt[25];
			strftime(dt, sizeof(dt), "%m/%d/%Y   %I:%M %p", &timeinfo);
			timeOfCreation = dt;
		}
		else {
			timeOfCreation = "error";
		}
	}

	/*void RemoveFile(string name)
	{
		for (int i = 0; i < files.getsize(); i++)
		{
			if (name == files[i]->name)
			{
				files.removeAtSpecificPosition(files[i]);
			}
		}
	}*/

	int GetFileIndex(string name)
	{
		for (int i = 0; i < files.getsize(); i++)
		{
			if (name == files[i]->name)
			{
				return i;
			}
		}
		return -1;
	}

	int GetFileIndexwithExtension(string name, string extension)
	{
		for (int i = 0; i < files.getsize(); i++)
		{
			if (name == files[i]->name && extension == files[i]->extension)
			{
				return i;
			}
		}
		return -1;
	}

	int GetFolderIndex(string name)
	{
		for (int i = 0; i < folders.getsize(); i++)
		{
			if (name == folders[i]->name)
			{
				return i;
			}
		}
		return -1;
	}
	bool checkfile(string name, string extension)
	{
		if (extension == "") { extension = ".txt"; }
		for (int i = 0; i < files.getsize(); i++)
		{
			if ((name == files[i]->name) && (extension == files[i]->extension))
			{
				return true;
			}
		}
		return false;
	}

	bool checkfile2(string name)
	{
		for (int i = 0; i < files.getsize(); i++)
		{
			if ((name == files[i]->name))
			{
				return true;
			}
		}
		return false;
	}



	void RenameFile(string newfilename, string oldfilename, string oldfileextension)
	{
		for (int i = 0; i < files.getsize(); i++)
		{
			if (files[i]->name == oldfilename && files[i]->extension == oldfileextension)
			{
				files[i]->name = newfilename;
			}
		}
	}

	bool checkfolder(string name)
	{
		for (int i = 0; i < folders.getsize(); i++)
		{
			if (name == folders[i]->name)
			{
				return true;
			}
		}
		return false;
	}

	void ChangeExtension(string prevExtension, string newExtension)
	{
		for (int i = 0; i < files.getsize(); i++)
		{
			if (files[i]->extension == prevExtension)
			{
				files[i]->extension = newExtension;
			}
		}
	}
	void EmptyDir()
	{
		DoubleLinkedList<File*> f = DoubleLinkedList<File*>();
		DoubleLinkedList<Folder*> fol = DoubleLinkedList<Folder*>();
		files = f;
		folders = fol;

	}
	bool RemoveFolder(int index)
	{
		return folders.deleteDataWithIndex(index);
	}

	bool RemoveFile(int index)
	{
		return files.deleteDataWithIndex(index);
	}

	void FormatDirectory()
	{
		files = DoubleLinkedList<File*>();
		folders = DoubleLinkedList<Folder*>();
	}

	void InsertNewFile(File* f)
	{
		files.InsertAtTail(f);
	}

	void InsertNewFolder(Folder* f)
	{
		folders.InsertAtTail(f);
	}

	Folder* FindFolder(string name)
	{
		for (int i = 0; i < folders.getsize(); i++)
		{
			if (name == folders[i]->name)
			{
				return folders[i];
			}
		}
		return nullptr;
	}

	Folder* FindFolder2(string name)
	{
		if (this->name == name)
		{
			return this;
		}
		for (int i = 0; i < folders.getsize(); i++)
		{
			if (name == folders[i]->name)
			{
				return folders[i];
			}
		}
		return nullptr;
	}

	File* FindFile(string name)
	{
		for (int i = 0; i < files.getsize(); i++)
		{
			if (name == files[i]->name)
			{
				return files[i];
			}
		}
		return nullptr;
	}

	File* FindFilewithextension(string name, string extension)
	{
		for (int i = 0; i < files.getsize(); i++)
		{
			if (name == files[i]->name && extension == files[i]->extension)
			{
				return files[i];
			}
		}
		return nullptr;
	}


	void PrintDirectories()
	{
		cout << "  Directory of " << path << "\\>" << endl << endl;
		int foldersize = 0;
		int filesize = 0;
		for (int i = 0; i < folders.getsize(); i++)
		{
			cout << folders[i]->timeOfCreation << "\t <DIR> \t\t" << folders[i]->name << endl;
			foldersize = foldersize + folders[i]->size;
		}

		for (int i = 0; i < files.getsize(); i++)
		{
			cout << files[i]->timeofcreation << "\t\t\t" << files[i]->name << files[i]->extension << endl;
			filesize = filesize + files[i]->size;
		}

		cout << "\t\t" << folders.getsize() << " Dir(s)" << "\t\t" << foldersize << " bytes" << endl;
		cout << "\t\t" << files.getsize() << " File(s)" << "\t\t" << filesize << " bytes" << endl;
	}

	void PrintFiles()
	{
		cout << "  Directory of " << path << "\\>" << endl << endl;
		int filesize = 0;

		for (int i = 0; i < files.getsize(); i++)
		{
			cout << files[i]->timeofcreation << "\t\t\t" << files[i]->name << files[i]->extension << endl;
			filesize = filesize + files[i]->size;
		}
		cout << "\t\t" << files.getsize() << " File(s)" << "\t\t" << filesize << " bytes" << endl;
	}

	bool FindDataInFile(File* fileattrib, string data)
	{
		int index = -1;
		index = fileattrib->data.find(data);
		if (index != -1) return true;
		return false;
	}

	void findString(string data)
	{
		for (int i = 0;i < files.getsize();i++)
		{
			bool isPresent = FindDataInFile(files[i], data);
			cout << "---------- " << files[i]->name << files[i]->extension << endl;
			if (isPresent)
			{
				cout << files[i]->data << endl;
			}
			cout << endl;
		}
	}

	void printDirectoryTree(Folder* currentFolder, int level = 0, bool last = true)
	{
		if (currentFolder == nullptr)
		{
			return;
		}
		if (level != 1)
		{
			cout << "|" << string(level * 4, ' ');
		}
		if (currentFolder->parent == nullptr)
		{
			cout << "I:\n";
		}
		else
		{
			cout << ("|________") << currentFolder->name << endl;
		}
		for (int i = 0;i < folders.getsize();i++)
		{
			bool isLast = (i == currentFolder->folders.getsize() - 1);
			printDirectoryTree(currentFolder->folders[i], level + 1, isLast);
		}

	}

	void PrintFile(int level = 0)
	{
		if (files.isEmpty())
		{
			return;
		}
		for (int i = 0;i < files.getsize();i++)
		{
			cout << string(level * 4, ' ') << "   " << files[i]->name << files[i]->extension << endl;
		}
	}


};