#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<process.h>
#include<stdlib.h>
#include<conio.h>
#include<algorithm>
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
		app.open("st1.txt", ios::app);
	else
		app.open("st1.txt", ios::out);
	if (!app)
	{
		cout << "CAnt open file in output mode\n";
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
	in.open("st1.txt", ios::in);
	i = 0; no = 0;
	if (!in)
	{
		cout << "CAnt open file in input mode \n";
		_getch();
		exit(0);
	}
	while (!in.eof())
	{
		in.getline(s1[i].name, 15,'|');
		in.getline(s1[i].usn, 15, '|');
		in.getline(s1[i].branch, 15, '\n');
		no++;
		i++;
	}
	in.close();
}
void write()
{
	cout << "Enter name :";
	cin >> s.name;
	cout << "Enter usn:";
	cin >> s.usn;
	cout << "Enter branch :";
	cin >> s.branch;
	pack();
	mode = 0;
}
void search()
{
	int rrn;
	cout << "Enter rrn : ";
	cin >> rrn;
	unpack();
	no--;
	for (i = 0; i < no; i++)
	{
		if (rrn == i)
		{
			cout << "Record found \n";
			cout << "\n" << s1[i].name << "\t" << s1[i].usn << "\t" << s1[i].branch;
			_getch();
			return;
		}
	}
	cout << "Record not found \n";
	_getch();
	return;
}
void main()
{
	int ch;
	for (;;)
	{
		cout << "\n1-write\n2-search\n0-exit\n";
		cout << "Enter choice :\n";
		cin >> ch;
		switch (ch)
		{
		case 1: write();
			break;
		case 2: search();
			break;
		case 0: exit(0);
		default:cout << "Invalid option \n";
			break;
		}
	}
}