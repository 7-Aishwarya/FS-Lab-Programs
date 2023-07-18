#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<process.h>

using namespace std;
#define datafile "stdfile.txt"
#define indexfile "indfile.txt"

class student
{
public: char dusn[15], name[15], branch[15], sem[15];
	  void add();
	  void pack();
	  void unpack();
	  void recdisp(int);
	  void remove(int);
	  void datadisp();
	  friend int search(char*);
};
class index
{
public: char iusn[15], addr[15];
	  void initial();
	  void write();
}in,id[100];

fstream ifile, stdfile;

char buffer[100];
int i, indsize, mode = 0;

void opener(fstream& sfile, char* fn, int mode)
{
	try
	{
		sfile.open(fn, mode);
	}
	catch (std::ios_base::failure& e)
	{
		cout << e.what() << "\n";
	}
	if (!sfile)
	{
		cout << "Unable to open file\n";
		_getch();
		exit(1);
	}
}
void index::initial()
{
	ifile.open(indexfile, ios::in);
	if (!ifile)
	{
		indsize = 0;
		return;

	}
	for (indsize == 0;; indsize++)
	{
		ifile.getline(id[indsize].iusn, 15, '|');
		ifile.getline(id[indsize].addr, 5, '\n');
		if (ifile.eof())
			break;
	}
	ifile.close();
}
void index::write()
{
	opener(ifile, (char*)indexfile, ios::out);
	for (i = 0; i < indsize; i++)
		ifile << id[i].iusn << "|" << id[i].addr << "\n";
	ifile.close();
}
int search(char* fusn)
{
	int low = 0;
	int mid;
	int high = indsize - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (strcmp(fusn, id[mid].iusn) == 0)
			return mid;
		else if (strcmp(fusn, id[mid].iusn) > 0)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}
void student::add()
{
	int k;
	cout << "Enter usn :";
	cin >> dusn;
	if (search(dusn) >= 0)
	{
		cout << "Duplicate records cant be inseted \n";
		_getch();
		return;
	}
	for (i = indsize; i > 0; i--)
	{
		if (strcmp(dusn, id[i - 1].iusn) < 0)
			id[i] = id[i - 1];
		else
			break;
	}
	if (mode)
		opener(stdfile, (char*)datafile, ios::app);
	else
	{
		opener(stdfile, (char*)datafile, ios::out);
		mode = 1;
	}
	cout << "Enter name : ";
		cin >> name;
		cout << "Enter branch : ";
		cin >> branch;
		cout << "Enter sem : ";
		cin >> sem;
		pack();
		stdfile.seekg(0, ios::end);
		k = stdfile.tellg();
		stdfile << buffer << endl;
		strcpy_s(id[i].iusn, dusn);
		_itoa_s(k,id[i].addr, 10);
		indsize++;
		stdfile.close();
}
void student::recdisp(int pos)
{
	opener(stdfile, (char*)datafile, ios::in);
	stdfile.seekg(atoi(id[pos].addr), ios::beg);
	unpack();
	if (dusn[0] == '$')
	{
		cout<<"Record dleted\n";
		return;
	}
	cout << "\n" << dusn << "\t" << name << "\t" << branch << "\t" << sem;
	stdfile.close();
}
void student::remove(int pos)
{
	opener(stdfile, (char*)datafile, ios::in |ios::out);
	stdfile.seekg(atoi(id[pos].addr), ios::beg);
	stdfile.put('$');
	for (i = pos; i < indsize; i++)
	{
		id[i] = id[i + 1];
		indsize--;
	}
	stdfile.close();
	in.write();
}
void student::pack()
{
	strcpy_s(buffer, dusn);
	strcat_s(buffer, "|");
	strcat_s(buffer, name);
	strcat_s(buffer, "|");
	strcat_s(buffer, branch);
	strcat_s(buffer, "|");
	strcat_s(buffer, sem);
}
void student::unpack()
{
	stdfile.getline(dusn, 15, '|');
	stdfile.getline(name, 15, '|');
	stdfile.getline(branch, 15, '|');
	stdfile.getline(sem ,15, '\n');
}
void student::datadisp()
{
	while (1)
	{
		unpack();
		if (dusn[0] == '$')
		{
			cout << "Record alrdy deleted\n";
			
		}
		cout << "\n" << dusn << "\t" << name << "\t" << branch << "\t" << sem<<endl;
		if (stdfile.eof())
		{
			stdfile.close();
			break;
		}
	}
}
void main()
{
	student s;
	int flag, pos;
	char susn[15];
	int ch;
	for (;;)
	{
		cout << "\n1-Add\n2-display\n3-search\n4-remove\n0-exit";
		cout << "Enter choice:";
		cin >>ch;
		switch (ch)
		{
		case 1: s.add();
			in.write();
			break;
		case 2: opener(stdfile, (char*)datafile, ios:: in);
			s.datadisp();
			for (i = 0; i < indsize; i++)
				cout << id[i].iusn << "|" << id[i].addr << "\n";
			break;
		case 3: cout << "Enter usn :";
			cin >> susn;
			flag = search(susn);
			if (flag == -1)
			{
				cout << "Record not found\n";
			}
			else
				s.recdisp(flag);
			break;
		case 4:  cout << "Enter usn :";
			cin >> susn;
			pos = search(susn);
			if (pos == -1)
			{
				cout << "Record not found\n";
			}
			else
				s.remove(pos);
			break;
		case 0: default:cout << "Invalid\n";
			break; 
		}
	}

}