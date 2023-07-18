#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>
#include<process.h>
#include<algorithm>
#include<conio.h>

using namespace std;

class names
{
public: char name[30];
};

void main()
{
	ofstream out;
	names n[10];
	out.open("file1.txt", ios::out);
	int m;
	cout << "Enter number of names \n";
	cin >> m;
	int p, q;
	char tem;
	for (int i = 0; i < m; i++)
	{
		cout << "Enter names \n";
		cin >> n[i].name;
		cout << "Names in reverse order \n";
		q = strlen(n[i].name) - 1;
		for (p= 0; p< q; p++, q--)
		{
			tem = n[i].name[p];
			n[i].name[p] =n[i].name[q];
			n[i].name[q] = tem;
		}
		cout <<n[i].name << "\n";
		out << n[i].name;
		out << "\n";
		
	}
	cout << endl;
	out.close();
	ofstream outf;
	ifstream in, in2;

	in.open("file1.txt", ios::in);
	outf.open("f1.txt", ios::out);
	char ch[10],temp;
	int k, l;
	cout << "Names from files\n";
	while (in)
	{
		in >> ch;
		if (in)
		{
			l = strlen(ch) - 1;
			for (k = 0; k < l; k++, l--)
			{
				temp = ch[k];
				ch[k] = ch[l];
				ch[l] = temp;
			}
			cout << ch << "\n";
			outf << ch;
			outf << "\n";
		}
	}
	cout << endl;
	outf.close();
	
	in2.open("f1.txt", ios::in);
	outf.open("f2.txt", ios::out);

	string line;

	cout << "Reversed name from file\n";
	while (in2)
	{
		getline(in2, line);
		reverse(line.begin(), line.end());
		cout << line << "\n";
		outf << line;
		outf << "\n";
	}
	in2.close();
	outf.close();
}