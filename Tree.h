#pragma once
#include<iostream>
#include"folder.h"
using namespace std;

class Tree
{
public:
	Folder* root;
	Folder* CF;
	bool isprompt = true;

	Tree()
	{
		//CF = new Folder("");
		root = new Folder("I:", "I:");
		CF = root;

	}

	void MakeNewFolder(Folder* f)
	{
		CF->folders.InsertAtTail(f);
	}

	void SetPath(Folder* f)
	{
		string path = CF->name;
		Folder* parent = new Folder();
		while (parent != nullptr)
		{
			path = parent->name + "\\" + path;
			parent = parent->parent;
		}
		f->path = path;
	}

	void Print()
	{
		/*if (CF->name == "I")
		{
			cout << "I:" << prompt;
		}
		else
		{
			cout << "I:" << CF->path.substr(2, CF->path.length()) << CF->name << prompt;
		}*/
		cout << CF->path << prompt();
	}

	string prompt()
	{
		if (isprompt)
		{
			return "\\>";
		}
		else
		{
			return "$";
		}
	}

	bool FolderExists(string name)
	{
		for (int i = 0; i < CF->folders.getsize(); i++)
		{
			if (CF->folders[i]->name == name)
			{
				return true;
			}
		}
			return false;
	}

	File* Findfile(string name)
	{
		for (int i = 0; i < CF->files.getsize(); i++)
		{
			if (name == CF->files[i]->name)
			{
				return CF->files[i];
			}
		}
		return nullptr;
	}
	
	File* Findfilewithextension(string name, string extenison)
	{
		for (int i = 0; i < CF->files.getsize(); i++)
		{
			if (name == CF->files[i]->name && extenison == CF->files[i]->extension)
			{
				return CF->files[i];
			}
		}
		return nullptr;
	}

	Folder* FindFolder(string name)
	{
		for (int i = 0; i < CF->folders.getsize(); i++)
		{
			if (name == CF->folders[i]->name)
			{
				return CF->folders[i];
			}
		}
		return nullptr;
	}

};
