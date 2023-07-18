#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<fstream>
#include<string>
#include<iostream>
#include<algorithm>

using namespace std;
class student
{
public: char name[15], usn[15], branch[15], buffer[100];

}s,s1[100],temp;
char extra[45];
int i, no = 0, mode = 1;

void pack()
{
	fstream app;
	if (mode == 0)
		app.open("st1.txt", ios::app);
	else
		app.open("st1.txt", ios::out);
	if (!app)
	{
		cout << "Cant open file in output mode\n";
		_getch();
		exit(0);
	}
	strcpy_s(s.buffer, s.name);
	strcat_s(s.buffer, "|");
	strcat_s(s.buffer, s.usn);
	strcat_s(s.buffer, "|");
	strcat_s(s.buffer, s.branch);
	int count = strlen(s.buffer);
	for(int k=0;k<45-count;k++)
		strcat_s(s.buffer, "|");
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
		cout << "Cant open file in output mode\n";
		_getch();
		exit(0);
	}
	while (!in.eof())
	{
		in.getline(s1[i].name, 15, '|');
		in.getline(s1[i].usn, 15, '|');
		in.getline(s1[i].branch, 15, '|');
		in.getline(extra, 45, '\n');
		no++;
		i++;
	}
	in.close();
}
void write()
{
	cout << "Enter name:";
	cin >> s.name;
	cout << "Enter usn : ";
	cin >> s.usn;
	cout << "Enter branch: ";
	cin >> s.branch;
	pack();
	mode = 0;
}
void search()
{
	char usn[15];
	cout << "Enter usn : ";
		cin >> usn;
	unpack();
	for (i = 0; i < no; i++)
	{
		if (strcmp(usn, s1[i].usn) == 0)
		{
			cout << "Record found\n";
			cout << "\n" << s1[i].name << "\t" << s1[i].usn << "\t" << s1[i].branch;
			return;
		}
	}
	cout<<"Record not found \n";
	return;
}
void modify()
{
	char usn[15];
	cout << "Enter usn : ";
	cin >> usn;
	int j;
	unpack();
	no--;
	for (j = 0; j < no; j++)
	{
		if (strcmp(s1[j].usn, usn) == 0)
		{
			cout<<"Enter name : ";
				cin >> s1[j].name;
				cout << "Enter usn:";
				cin >> s1[j].usn;
				cout << "Enter branch :";
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
	cout << "Record modified \n";
}
void display()
{
	unpack();
	for (i = 0; i < no; i++)
		cout << "\n" << s1[i].name << "\t" << s1[i].usn << "\t" << s1[i].branch;
	_getch();
}
void main()
{
	int ch;
	for (;;)
	{
		cout << "\n1-write\n2-display\n3-search\n4-modify\n";
		cout << "Enter choice :";
		cin >> ch;
		switch (ch)
		{
		case 1: write();
			break;
		case 2:  display();
			break;
		case 3: search();
			break;
		case 4: modify();
			break;
		case 0: Default:cout << "Invalid coice\n";
			break;
		}
	}
}