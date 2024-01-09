#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include"DLinkList.h"
#include<vector>
#include"Tree.h"
#include<list>
#include<queue>
#include"notepad.h"
using namespace std;
struct Fileattrib
{
	string filename;
	int filesize;

	Fileattrib(const string& n, int a) : filename(n), filesize(a) {}

	// Custom comparator for sorting by age in descending order
	bool operator<(const Fileattrib& other) const {
		return filesize < other.filesize;
	}
};
class DOs
{
public:

	list<string> PrintQueue;
	priority_queue<Fileattrib> PriorityQueue;
	Tree t;
	bool prompt = false;
	string user = "Irtaza Manzoor | 2022-CS-189";
	DOs()
	{

	}

	void PrintHeader()
	{
		cout << "Irtaza Manzoor [2022 - CS - 189] \nSubmitted to: Sir Faraz"<< endl << endl;
		//t.Print();
	}

	void run()
	{
		PrintHeader();
		t.Print();
		bool exit = false;
		while (!exit)
		{
			exit = input();
		}
	}

	string RemoveSpaces(string str)
	{
		string name = "";
		for (char c : str)
		{
			if (c != ' ')
			{
				name += c;
			}
		}
		return name;
	}

	bool checkextensions(string ext)
	{
		vector<string> extensions = { ".txt",".text",".cpp" };
		for (int i = 0; i < extensions.size(); i++)
		{
			if (ext == extensions[i])
			{
				return true;
			}
		}
		return false;
	}

	string Lower(string s)
	{
		for (int i = 0; i < s.length(); i++)
		{
			s[i] = tolower(s[i]);
		}
		return s;
	}

	int FindCharacterPosition(char s, string ss)
	{
		for (int i = 0; i < ss.length(); i++)
		{
			if (s == ss[i])
			{
				return i;
			}
		}
		return -1;
	}

	bool input()
	{
		string command;
		getline(cin, command);
		string opr = command.substr(0, command.find(' '));
		opr = Lower(opr);
		if (opr == "mkdir")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
				t.Print();
				return false;
			}
			else
			{
				string foldername = command.substr(6, command.length());
				if (!(t.CF->checkfolder(foldername)))
				{
					Folder* f = new Folder(foldername, t.CF->path + "\\" + command.substr(6, command.length()), t.CF);
					t.CF->InsertNewFolder(f);
					t.CF->size += f->size;
					cout << "\t New Folder named " << "'" << command.substr(6, command.length()) << "'" << " made successfully..." << endl;
				}
				else
				{
					cout << "\tFolder already exists" << endl;
				}
			}
		}
		else if (opr == "dir")
		{
			t.CF->PrintDirectories();
		}
		else if (opr == "cd.")
		{
			cout << "Current Working Directory: " << "\t" << t.CF->path << endl;
		}
		else if (opr == "create")
		{
			int s = FindCharacterPosition(' ', command);
			string command1 = command.substr(s + 1, command.length());

			int s2 = FindCharacterPosition(' ', command1);
			string filename = command1.substr(0, s2);
			//filename = RemoveSpaces(filename);

			int dot = FindCharacterPosition('.', filename);
			if (dot == -1) { dot = filename.length();}
			string extension = filename.substr(dot, filename.length());
			//extension = RemoveSpaces(extension);
			if (checkextensions(extension) || extension == "")
			{
				string data, originalData;
				int s3 = FindCharacterPosition(' ', command1);
				if (s3 == -1)
				{
					data = "";
					originalData = data;
				}
				else
				{
					data = command1.substr(s3 + 1, command1.length() - 1);
					originalData = data.substr(1, data.length() - 1);
				}
				string file = command.substr(7, dot);
				if (!(t.CF->checkfile(file, extension)))
				{
					if (originalData.length() == 0)
					{
						originalData = "";
					}
					File* f = new File(file, extension, t.CF->name + ":\\" + t.CF->path, originalData);
					t.CF->InsertNewFile(f);
					t.CF->size += f->size;
					cout << "\t New File named " << "'" << filename << "'" << " made successfully..." << endl;
				}
				else
				{
					cout << "\tFile already exists..." << endl;
				}
			}
			else
			{
				cout << "\tInput extensions is not correct" << endl;
			}
		}
		else if (opr == "rmdir")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string name = command.substr(6, command.length());
				int index = t.CF->GetFolderIndex(name);
				if (index != -1)
				{
					Folder* f = t.FindFolder(name);
					bool check = t.CF->RemoveFolder(index);
					if (check)
					{
						t.CF->size -= f->size;
						cout << "\tFolder named " << "'" << name << "'" << " has been deleted..." << endl;
					}
					else
					{
						cout << "Error! Folder not found..." << endl;
					}
				}
				else
				{
					cout << "Error! Folder not found..." << endl;
				}
			}
		}
		else if (opr == "format") // bytes mai msla ata hy
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string name = command.substr(7, command.length());
				int index = t.CF->GetFolderIndex(name);
				if (index != -1)
				{
					Folder* f = t.CF->FindFolder(name);
					f->EmptyDir();
					t.CF->size -= f->size; // yahan pr

					cout << "\tFolder named " << "'" << name << "'" << " has been formated..." << endl;
				}
				else
				{
					cout << "Error! Folder not found..." << endl;
				}
			}
		}
		else if (opr == "del")
		{
			int index = t.CF->GetFileIndex(command.substr(4, command.length()));
			if (index != -1)
			{

				bool check = t.CF->RemoveFile(index);
				if (check)
				{
					cout << "\tFile named " << "'" << command.substr(4, command.length()) << "'" << " has been deleted..." << endl;
				}
				else
				{
					cout << "ERROR! File not found..." << endl;
				}
			}
			else
			{
				cout << "File not found..." << endl;

			}
		}
		else if (opr == "cd")
		{
			string folder = command.substr(3, command.length());
			if (t.FolderExists(folder))
			{
				t.CF = t.FindFolder(folder);
				//t.SetPath(t.CF);
			}
			else
			{
				cout << " No such directory exists!" << endl;
			}
		}
		else if (opr == "cd\\")
		{
			if (t.CF->parent != nullptr)
			{
				t.CF = t.root;
			}
		}
		else if (opr == "cd .." || opr == "cd..")
		{
			if (opr.length() == command.length())
			{
				if (t.CF->parent != nullptr)
				{
					t.CF = t.CF->parent;
				}
			}
			else
			{
				cout << " The system cannot find the path specified." << endl;
			}
		}
		else if (opr == "attrib") // iss mai extenison bi sath check krni hy show kraty huy
		{
			if (opr.length() == command.length())
			{
				t.CF->PrintFiles();
			}
			else
			{
				string filename = command.substr(7, command.length());
				int dotindex = FindCharacterPosition('.', filename);
				if (dotindex != -1)
				{
					string originalName = filename.substr(0, filename.find('.'));
					string extension = filename.substr(dotindex);
					int index = t.CF->GetFileIndexwithExtension(originalName, extension);
					if (index == -1)
					{
						cout << " No such file exists" << endl;
					}
					else
					{
						File* f = t.Findfilewithextension(originalName, extension);
						cout << "\t" << f->timeofcreation << "\t" << f->name << f->extension << "\t" << f->size << " bytes " << f->data << endl;
					}

				}
				else
				{
					cout << "\tInput valid extension" << endl;
				}
			}
		}
		else if (opr == "find")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				int index = t.CF->GetFileIndex(command.substr(5, command.length()));
				if (index == -1)
				{
					cout << " No such directory exists" << endl;
				}
				else
				{
					File* f = t.Findfile(command.substr(5, command.length()));
					cout << "\t" << f->timeofcreation << "\t" << f->name << f->extension << "\t" << f->size << " bytes  " << '"' << f->data << '"' << endl;
				}
			}
		}
		else if (opr == "ver")
		{
			cout << "Microsoft Windows [Version 1.0.0]\n(c)Microsoft Corporation. All rights reserved." << endl;
		}
		else if (opr == "pwd")
		{
			cout << "\t" << t.CF->path << endl;
		}
		else if (opr == "help")
		{
			vector<string> content = { "MKDIR\tCreates a directory\tMKDIR [name]", "DIR\tDisplay the contents of directory", "CREATE\tCreate New file in directory\tCREATE file.txt", "RMDIR\tRemove the selected directory\tRMDIE [filename]", "FORMAT\tFormats the selected directory\tFORMAT [filename]", "DEL\tDelete the selected file frpm directory\tDEL [filename]", "CD\tMove to the input directory\tCD [move_to]", "CD\\\\\tMove to the root folder","CD ..\tMove to the previous directory means parent directory","ATTRIB\tDisplays the attributes of input file\tATTRIB [filename.txt]", "FIND\tFind the file in folder\tFIND [filename.txt]","VER\tDisplays the version of your MS-DOS", "PWD\t Displays the path of current directory", "HELP\t Displays helps related to specific command\tHELP [command]" };
			if (opr.length() == command.length())
			{
				for (int i = 0; i < content.size(); i++)
				{
					cout << content[i] << endl;
				}
			}
			else
			{
				string s = command.substr(5, command.length());
				if (s == "mkdir")
				{
					cout << content[0] << endl;
				}
				else if (s == "dir")
				{
					cout << content[1] << endl;
				}
				else if (s == "create")
				{
					cout << content[2] << endl;
				}
				else if (s == "rmdir")
				{
					cout << content[3] << endl;
				}
				else if (s == "format")
				{
					cout << content[4] << endl;
				}
				else if (s == "del")
				{
					cout << content[5] << endl;
				}
				else if (s == "cd")
				{
					cout << content[6] << endl;
				}
				else if (s == "cd\\")
				{
					cout << content[7] << endl;
				}
				else if (s == "cd..")
				{
					cout << content[8] << endl;
				}
				else if (s == "attrib")
				{
					cout << content[9] << endl;
				}
				else if (s == "find")
				{
					cout << content[10] << endl;
				}
				else if (s == "ver")
				{
					cout << content[11] << endl;
				}
				else if (s == "pwd")
				{
					cout << content[12] << endl;
				}
				else if (s == "help")
				{
					cout << content[13] << endl;
				}
				else
				{
					cout << "Command not found" << endl;
				}
			}
		}
		else if (opr == "cls")
		{
			system("cls");
			PrintHeader();
		}
		else if (opr == "exit")
		{
			return true;
		}
		else if (opr == "convert")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				int s = FindCharacterPosition(' ', command);
				string coo = command.substr(s + 1, command.length());
				int s2 = FindCharacterPosition(' ', coo);
				string previousextension = coo.substr(0, s2);
				if (checkextensions(previousextension))
				{
					int s3 = FindCharacterPosition(' ', coo);
					string changeextension = coo.substr(s3 + 1, coo.length());
					if (checkextensions(changeextension))
					{
						t.CF->ChangeExtension(previousextension, changeextension);
						cout << "\t All " << previousextension << " extensions changed to " << changeextension << endl;
					}
					else
					{
						cout << "\tSyntax of new extension is not correct" << endl;
					}
				}
				else
				{
					cout << "\tSyntax of previous extension is not correct" << endl;
				}
			}
		}
		else if (opr == "rename")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string command1 = command.substr(7, command.length());

				int firstdot = FindCharacterPosition('.', command1);
				int firstspace = FindCharacterPosition(' ', command1);

				string oldfilename = command1.substr(0, firstdot);				
				string oldfileextension = command1.substr(firstdot, firstspace-1);
				if (t.CF->checkfile(oldfilename,oldfileextension))
				{
					string command2 = command1.substr(firstspace, command1.length());

					int seconddot = FindCharacterPosition('.', command2);

					string newfilename = command2.substr(1, seconddot-1); // yahan change kia hy abi
					string Newfileextension = command2.substr(seconddot);
					if (!(t.CF->checkfile(newfilename, Newfileextension)))
					{
						if (Newfileextension == oldfileextension)
						{
							t.CF->RenameFile(newfilename, oldfilename, oldfileextension);
							cout << "\tFile name has been changed succesfully..." << endl;
						}
						else
						{
							cout << "\tERROR: You cannot change the extensions in rename" << endl;
						}
					}
					else
					{
						cout << "\tFile already present..." << endl;
					}
				}
				else
				{
					cout << "\t File Not found..." << endl;
				}
			}
		}
		else if (opr == "prompt")
		{
			t.isprompt = !t.isprompt;
		}
		else if (opr == "copy") // ye sai nai hy
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string command1 = command.substr(8);
				string copyfrom = command1.substr(0, command1.find(' '));
				string copyto = command.substr((opr.length() + copyfrom.length() + 8), command.length());
				string copiedto = copyto;
				File* copy;
				int indexofdot = FindCharacterPosition('.', copyfrom);
				if (indexofdot == -1)
				{
					cout << "Error! Please input extension of input file" << endl;
				}
				else
				{
					string firstslash = copyfrom.substr(copyfrom.find('\\') + 1);
					int idx = FindCharacterPosition('.', firstslash);
					string extension2 = "";
					if (firstslash == "")
					{
						idx = FindCharacterPosition('.', copyfrom);
						string extension = copyfrom.substr(idx, copyfrom.length());
						extension2 = extension.substr(0, extension.length() - 1);
					}
					else
					{
						string extensionOfsourcefile = firstslash.substr(idx, idx + firstslash.find('\\'));
						extension2 = extensionOfsourcefile.substr(0, extensionOfsourcefile.length() - 1);
					}
					bool check = checkextensions(extension2);
					if (check)
					{
						//finding file in path folder
						Folder* temp = t.root;
						string f;
						while (copyfrom.length() > 0)
						{
							f = copyfrom.substr(0, copyfrom.find('\\'));
							copyfrom = copyfrom.substr(f.length() + 1, copyfrom.length());
							if (copyfrom.length() != 0)
							{
								temp = temp->FindFolder(f);
							}
							if (temp == nullptr)
							{
								cout << "\tPath does not exists..." << endl;
								return true;
							}
						}
						string filename = f.substr(0, f.find('.'));

						copy = temp->FindFilewithextension(filename, extension2);
						if (copy != nullptr)
						{
							temp = t.root;
							while (copyto.length() > 0)
							{
								f = copyto.substr(0, copyto.find('\\'));
								copyto = copyto.substr(f.length() + 1, copyto.length());
								temp = temp->FindFolder2(f);
								if (temp == nullptr)
								{
									cout << "\t Error! Path does not exists..." << endl;
									return true;
								}
							}
							bool check = temp->checkfile(copy->name, copy->extension);
							if (check == false)
							{
								copy->path = temp->path + "\\" + copy->name;
								temp->InsertNewFile(copy);
								cout << "\t File named " << "'" << copy->name << copy->extension << "'" << " has been copied successfully to path " << "I:\\" << copiedto << endl;
							}
							else
							{
								cout << "\tError! File already present in destination..." << endl;
							}
						}
						else
						{
							cout << "\t Error! Source file is not found" << endl;
						}

					}
					else
					{
						cout << "Error! Input extension is not valid" << endl;
					}
				}
			}
		}
		else if (opr == "move")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string command1 = command.substr(8);
				string movefrom = command1.substr(0, command1.find(' '));
				string moveto = command.substr((opr.length() + movefrom.length() + 8), command.length());
				string copiedto = moveto;
				File* move;
				int indexofdot = FindCharacterPosition('.', movefrom);
				if (indexofdot == -1)
				{
					cout << "Error! Please input extension of input file" << endl;
				}
				else
				{
					string firstslash = movefrom.substr(movefrom.find('\\') + 1);
					int idx = FindCharacterPosition('.', firstslash);
					string extension2 = "";
					if (firstslash == "")
					{
						idx = FindCharacterPosition('.', movefrom);
						string extension = movefrom.substr(idx, movefrom.length());
						extension2 = extension.substr(0, extension.length() - 1);
					}
					else
					{
						string extensionOfsourcefile = firstslash.substr(idx, idx + firstslash.find('\\'));
						extension2 = extensionOfsourcefile.substr(0, extensionOfsourcefile.length() - 1);
					}
					bool check = checkextensions(extension2);
					if (check)
					{
						//finding file in path folder
						Folder* temp = t.root;
						string f;
						while (movefrom.length() > 0)
						{
							f = movefrom.substr(0, movefrom.find('\\'));
							movefrom = movefrom.substr(f.length() + 1, movefrom.length());
							if (movefrom.length() != 0)
							{
								temp = temp->FindFolder(f);
							}
							if (temp == nullptr)
							{
								cout << "\tPath does not exists..." << endl;
								return true;
							}
						}
						string filename = f.substr(0, f.find('.'));

						move = temp->FindFilewithextension(filename, extension2);
						if (move != nullptr)
						{
							//move = temp->FindFile(f);
							int idx = temp->GetFileIndexwithExtension(move->name, move->extension);
							temp->files.deleteDataWithIndex(idx);
							temp = t.root;
							while (moveto.length() > 0)
							{
								f = moveto.substr(0, moveto.find('\\'));
								moveto = moveto.substr(f.length() + 1, moveto.length());
								temp = temp->FindFolder2(f);
								if (temp == nullptr)
								{
									cout << "\t Error! Path does not exists..." << endl;
									return true;
								}
							}
							bool check = temp->checkfile(move->name, move->extension);
							if (check == false)
							{
								move->path = temp->path + "\\" + move->name;
								temp->InsertNewFile(move);
								cout << "\t File named " << "'" << move->name << move->extension << "'" << " has been moved successfully to path " << "I:\\" << copiedto << endl;
							}
							else
							{
								cout << "\tError! File already present in destination..." << endl;
							}
						}
						else
						{
							cout << "\t Error! Source file is not found" << endl;
						}

					}
					else
					{
						cout << "Error! Input extension is not valid" << endl;
					}
				}
			}

			//if (opr.length() == command.length())
			//{
			//	cout << "\tThe syntax of the command is incorrect." << endl;
			//}
			//else
			//{

			//	string movefrom = command.substr(opr.length() + 4, command.find(' '));
			//	string moveto = command.substr((opr.length() + movefrom.length() + 5), command.length());
			//	File* move;

			//	//finding file in path folder
			//	Folder* temp = t.root;
			//	string f;
			//	while (movefrom.length() > 0)
			//	{
			//		f = movefrom.substr(0, movefrom.find('\\'));
			//		movefrom = movefrom.substr(f.length() + 1, movefrom.length());
			//		if (movefrom.length() != 0)
			//		{
			//			temp = temp->FindFolder(f);
			//		}
			//		if (temp == nullptr)
			//		{
			//			cout << "\tPath does not exists..." << endl;
			//			return true;
			//		}
			//	}

			//	move = temp->FindFile(f);
			//	int idx = temp->GetFileIndex(move->name);
			//	temp->files.deleteDataWithIndex(idx);

			//	temp = t.root;
			//	while (moveto.length() > 0)
			//	{
			//		f = moveto.substr(0, moveto.find('\\'));
			//		moveto = moveto.substr(f.length() + 1, moveto.length());
			//		temp = temp->FindFolder2(f);
			//		if (temp == nullptr)
			//		{
			//			cout << "\t Path does not exists..." << endl;
			//			return true;
			//		}
			//	}
			//	move->path = temp->path + "\\" + move->name;
			//	temp->InsertNewFile(move);
			//}
		}
		else if (opr == "edit")
		{
			string fName = command.substr(opr.length() + 1, command.length());
			File* f = t.CF->FindFile(fName);
			if (f != nullptr)
			{
				ifstream read;
				string filename = f->name + "." + f->extension;
				read.open(filename);
				Editor e;
				e.openSaveFile(read);
				read.close();
				ofstream write;
				write.open(filename);
				system("cls");
				e.editFile(write);
				system("cls");
				write.close();

			}
		}
		else if (opr == "findf")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string command1 = command.substr(6);
				int dotposition = FindCharacterPosition('.', command1);
				if (dotposition == -1)
				{
					cout << "Error! Extension Not Found" << endl;
				}
				else
				{
					string filename = command1.substr(0, dotposition);
					int spaceindex = FindCharacterPosition(' ', command1);
					string extension = command1.substr(dotposition, spaceindex-1);
					bool checkextension = checkextensions(extension);
					if (checkextension)
					{
					    File* checkfile = t.CF->FindFilewithextension(filename, extension);
						if (checkfile != nullptr)
						{
							string command3 = command1.substr(spaceindex+1);
							string data = command3.substr(0);
							if (data == "")
							{
								cout << "ERROR! Data not found" << endl;
							}
							else
							{
								bool isdata = t.CF->FindDataInFile(checkfile, data);
								cout << "---------- " << checkfile->name << checkfile->extension << endl;
								if (isdata)
								{
									cout << checkfile->data << endl;
								}
								
							}
						}
						else
						{
							cout << "ERROR! File not founfd" << endl;
						}
					}
					else
					{
						cout << "ERROR! Invalid Extension" << endl;
					}
				}
			}
		}
		else if (opr == "findstr")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string data = command.substr(8);
				t.CF->findString(data);
			}
		}
		else if (opr == "tree")
		{
			cout << "Folder PATH listing\n";
			cout << "Volume serial number is A85D-58F9\n";
			t.CF->printDirectoryTree(t.CF);
		}
		else if (opr == "print")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string command1 = command.substr(6);
				int dotposition = FindCharacterPosition('.', command1);
				if (dotposition == -1)
				{
					cout << "ERROR! Please enter valid extension" << endl;
				}
				else
				{
					string filename = command1.substr(0, dotposition);
					string fileextension = command1.substr(dotposition);
					bool checkextension = checkextensions(fileextension);
					if (checkextension)
					{
						File* file = t.CF->FindFilewithextension(filename, fileextension);
						if (file == nullptr)
						{
							cout << "ERROR! File not found" << endl;
						}
						else
						{
							PrintQueue.push_back(file->name);
							cout << "File has been added to queue successfully" << endl;
						}

					}
					else
					{
						cout << "ERROR! Please enter valid extension" << endl;
					}
				}
			}
		}
		else if (opr == "queue")
		{

			for (auto filename : PrintQueue)
			{
				int timeleft = rand() % 60;
				cout << "\t" << filename << " - Time Left: " << timeleft << " seconds" << endl;
			}
			cout << endl;
			
			
		}
		else if (opr == "pprint")
		{
			if (opr.length() == command.length())
			{
				cout << "\tThe syntax of the command is incorrect." << endl;
			}
			else
			{
				string command1 = command.substr(7);
				int dotposition = FindCharacterPosition('.', command1);
				if (dotposition == -1)
				{
					cout << "ERROR! Please enter valid extension" << endl;
				}
				else
				{
					string filename = command1.substr(0, dotposition);
					string fileextension = command1.substr(dotposition);
					bool checkextension = checkextensions(fileextension);
					if (checkextension)
					{
						File* file = t.CF->FindFilewithextension(filename, fileextension);
						if (file == nullptr)
						{
							cout << "ERROR! File not found" << endl;
						}
						else
						{
							PriorityQueue.push(Fileattrib(file->name, (file->size + (rand() % 100))));
							cout << "File has been added to priority queue successfully" << endl;
						}

					}
					else
					{
						cout << "ERROR! Please enter valid extension" << endl;
					}
				}
			}
		}
		else if (opr == "pqueue")
		{
			priority_queue<Fileattrib> copy = PriorityQueue;
			cout << "\t" << "File Name" << "\t" << "File Size" << "\t" << "Time Left" << endl;
			while (!copy.empty())
			{
				int timeleft = rand() % 60;
				cout << "\t" << copy.top().filename << "\t" << copy.top().filesize << "\t" << timeleft << endl;
				copy.pop();
			}
			cout << endl;
		}
		else
		{
			cout << "\t" << "'" << opr << "'" << " is not recognized as an internal or external command,\n \t operable program or batch file." << endl;
		}


		t.Print();
		return false;

	}
};
