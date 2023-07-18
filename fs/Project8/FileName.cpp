#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<conio.h>
#include<fstream>
#include<iostream>
#include<process.h>
#include<algorithm>

using namespace std;
char fname[8][8] = {
	"1.txt",
	"2.txt",
	"3.txt",
	"4.txt",
	"5.txt",
	"6.txt",
	"7.txt",
	"8.txt"
};
fstream file[8];
class record
{
public:char name[20],usn[20];
}rec[20], temp;

void merge(char* file1, char* file2, char* filename)
{
	int k = 0;
	fstream f1, f2;
	f1.open(file1, ios::in);
	f2.open(file2, ios::in);
	while (!f1.eof())
	{
		f1.getline(rec[k].name, 20, '|');
		f1.getline(rec[k++].usn, 20, '\n');
	}
	while (!f2.eof())
	{
		f2.getline(rec[k].name, 20, '|');
		f2.getline(rec[k++].usn, 20, '\n');
	}
	int t, y;
	for(t = 0; t < k - 2;t++)
	for(y=0;y<k-t-2;y++)
		if (strcmp(rec[y].name, rec[y + 1].name) > 0)
		{
			temp = rec[y];
			rec[y] = rec[y + 1];
			rec[y + 1] = temp;
		}
	fstream temp1;
	temp1.open(filename, ios::out);
	for (int t = 1; t < k - 1; t++)
		temp1 << rec[t].name << "|" << rec[t].usn << "\n";
	f1.close();
	f2.close();
	temp1.close();
	return;
}
void kwaymerge()
{
	char filename[100][20] = {
		"11.txt","22.txt","33.txt","44.txt","111.txt","222.txt","1111.txt"
	};
	int k = 0,i;
	for (i = 0; i < 8; i += 2)
		merge(fname[i], fname[i + 1], filename[k++]);
	k = 4;
	for (i = 0; i < 4; i+=2)
		merge(filename[i], filename[i + 1], filename[k++]);
	merge(filename[4], filename[5], filename[6]);
	return;
}
void main()
{
	int no,i;
	char name[20], usn[20];
	cout << "Enter number of records :";
	cin >> no;
	for (i = 0; i < 8; i++)
		file[i].open(fname[i], ios::out);
	for (i = 0; i < no; i++)
	{
		cout << "Enter name:";
		cin >> name;
		cout << "Enter usn:";
		cin >> usn;
		file[i % 8] << name << "|" << usn << "\n";
	}
	for (i = 0; i < 8; i++)
		file[i].close();
	kwaymerge();
	fstream result;
	result.open("1111.txt", ios::in);

	cout << "Sorted \n";
	for (i = 0;i < no; i++)
	{
		result.getline(name, 20, '|');
		result.getline(usn, 20, '\n');
		cout << name << "|" << usn << "\n";

	}
	for (i = 0; i < 8; i++)
		file[i].close();
	result.close();
}