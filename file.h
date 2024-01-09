#pragma once
#include<iostream>
using namespace std;
class File
{
public:
	string name;
	string extension;
	bool isHidden;
	string data;
	string path;
	string timeofcreation;
	int size;

	File(string n = "New File", string ext = "", string path = "", string data = "hello")
	{
		name = n;
		this->data = data;
		this->path = path;
		isHidden = false;
		if (ext == "")
		{
			extension = ".txt";
		}
		else
		{
			extension = ext;
		}
		SaveTime();
		savesize();
	}
	void savesize()
	{
		this->size = sizeof(*this);
	}
	void SaveTime()
	{
		time_t now = time(0);
		struct tm timeinfo;

		if (localtime_s(&timeinfo, &now) == 0) {
			char dt[25];
			strftime(dt, sizeof(dt), "%m/%d/%Y   %I:%M %p", &timeinfo);
			timeofcreation = dt;
		}
		else {
			timeofcreation = "error";
		}
	}

};
