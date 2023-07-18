#include<stdio.h>
#include<string>
#include<fstream>
#include<iostream>
#include<process.h>
#include<algorithm>
#include<conio.h>
#include<stdlib.h>

using namespace std;

class coseq
{
public: char list1[100][20], list2[100][20];
	  int n1, n2;
	  void load();
	  void sort();
	  void match();
};
fstream f1, f2, of;

void coseq::load()
{
	n1 = n2 = -1;
	while (!f1.eof())
		f1.getline(list1[++n1], 15, '\n');
	while (!f2.eof())
		f2.getline(list2[++n2], 15, '\n');
}
void coseq::sort()
{
	char temp[30];
	for(int i=0;i<=n1;i++)
		for(int j=i+1;j<=n1;j++)
			if (strcmp(list1[i], list1[j]) > 0)
			{
				strcpy_s(temp, list1[i]);
				strcpy_s(list1[i], list1[j]);
				strcpy_s(list1[j], temp);
			}
	for (int k = 0; k <= n2; k++)
		for (int l = k + 1; l<= n2; l++)
			if (strcmp(list2[k], list2[l]) > 0)
			{
				strcpy_s(temp, list2[k]);
				strcpy_s(list2[k], list2[l]);
				strcpy_s(list2[l], temp);
			}
}

void coseq::match()
{
	int i = 0, c = 0, j = 0;
	while(i <= n1 && j <= n2)
	{
		if (strcmp(list1[i], list2[j]) == 0)
		{
			cout << "match : " << ++c << list1[i] << endl;
			of << list1[i] << endl;
			i++;
			j++;
			continue;
		}
		else if (strcmp(list1[i], list2[j]) > 0)
			j++;
		else
			i++;
	}
}
void main()
{
	coseq cq;
	f1.open("file1.txt", ios::in);
	f2.open("file2.txt",ios::in);
	if (!f1 || !f2)
	{
		cout << "Errr in opening\n";
		exit(0);
	}
	cq.load();
	of.open("file3.txt", ios::out);
	cq.sort();
	cq.match();

}
