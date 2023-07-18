#include<conio.h>
#include<process.h>
#include<string>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<algorithm>
#include<stdlib.h>

using namespace std;

class student
{
public: char name[15], usn[15], branch[15], buffer[100];
}temp,s,s1[100];
int i, no = 0, mode = 0;

void pack()
{
	fstream app;
	if (mode == 0)
		app.open("st2.txt", ios::app);
	else
		app.open("st2.txt", ios::out);
	if (!app)
	{
		cout << "Cant open file in output mode \n";
		_getch();
		exit(0);
	}
	strcpy_s(s.buffer, s.name);
	strcat_s(s.buffer, "|");
	strcat_s(s.buffer, s.usn);
	strcat_s(s.buffer, "|");
	strcat_s(s.buffer, s.branch);
	strcat_s(s.buffer, "\n");
	app << s.buffer;
	app.close();
}
void unpack()
{
	fstream in;
	in.open("st2.txt", ios::in);
	i = 0; no = 0;
	if (!in)
	{
		cout << "Cant open file in input mode \n";
		_getch();
		exit(0);
	}
	while (!in.eof())
	{
		in.getline(s1[i].name, 15, '|');
		in.getline(s1[i].usn, 15, '|');
		in.getline(s1[i].branch, 15, '\n');
		no++;
		i++;
	}
	in.close();
}
void write()
{
	cout << "Enter name \n";
	cin >> s.name;
	cout << "Enter usn \n";
	cin >> s.usn;
	cout << "Enter branch \n";
	cin >> s.branch;
	pack();
	mode = 0;
}
void search()
{
	char usn[15];
	cout << "Enter usn \n";
	cin >> usn;
	unpack();
	for (i = 0; i < no; i++)
	{
		if (strcmp(s1[i].usn, usn) == 0)
		{
			cout << "Record found \n";
			cout << "\n" << s1[i].name << "\t" << s1[i].usn << "\t" << s1[i].branch;
			_getch();
			return;
		}
	}
	cout << "Record not found \n";
}
void modify()
{
	char usn[15], j;
	cout << "Enter usn \n";
	cin >> usn;
	unpack();
	no--;
	for (j = 0; j < no; j++)
	{
		if (strcmp(s1[j].usn, usn) == 0)
		{
			cout << "Enter new name \n";
			cin >> s1[j].name;
			cout << "Enter new usn \n";
			cin >> s1[j].usn;
			cout << "Enter new branch \n";
			cin >> s1[j].branch;
			break;
		}
	}
	if (j == no)
	{
		cout << "Record not found \n";
		_getch();
		return;
	}
	mode = 1;
	for (j = 0; j < no; j++)
	{
		strcpy_s(s.name, s1[j].name);
		strcpy_s(s.usn, s1[j].usn);
		strcpy_s(s.branch, s1[j].branch);
		pack();
		mode = 0;
	}
	cout << "record modified\n";
}
void display()
{
	unpack();
	for(i=0;i<no;i++)
		cout << "\n" << s1[i].name << "\t" << s1[i].usn << "\t" << s1[i].branch;
	_getch();
}
void main()
{
	int ch;
	for (;;)
	{
		cout << "1-write\n2-display\n3-search\n4-modify\n0-exit";
		cout << "Enter choice :\n";
		cin >> ch;
		switch (ch)
		{
		case 1: write();
			break;
		case 2: display();
			break;
		case 3: search();
			break;
		case 4:modify();
			break;
		case 5:exit(0);
		default:cout << "Invalid choice\n";
			break;
		}
	}
}