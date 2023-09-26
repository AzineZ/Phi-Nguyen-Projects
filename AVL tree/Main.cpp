#include <iostream>
#include <fstream>
#include <conio.h>
#include "Tree.h"
#include <Windows.h>
using namespace std;

/*
INSTRUCTION FOR INPUT IN TEMP FILE: 
use 'a' for add, 'd' for delete. Put these between numbers
Example input: 
a
12
a
24
a
88
d
12
d
88
a
90
*/
int main()
{
	//REMEMBER TO fix INPUT.TXT NAME
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Tree t;
	ifstream in;
	in.open("C:\\temp\\input.txt");
	if (in.is_open())
	{
		char a;
		int x;

		while (in.get(a))
		{
			if (a == 'a')
			{
				in >> x;
				Node* r = t.giveroot();
				r = t.insert(r, x);
				Sleep(500);
				in.ignore(20, '\n');
			}

			else if (a == 'd')
			{
				in >> x;
				Node* r = t.giveroot();
				r = t.del(r, x);
				Sleep(500);
				in.ignore(20, '\n');
			}
			
			else if (a == 'e')
			{
				in >> x;
				if (x == -1)
				{
					//do nothing
				}
			}
		}

		//print NLR after all numbers in the file are processed
		t.gotoxy(0, 0);
		Node* b = t.giveroot();
		cout << "NLR: ";
		t.nlr(b);
		in.close();
	}
	t.gotoxy(0, 2);
	char ab;
	do
	{
		t.gotoxy(0, 2);
		cout << "Press 'a' then press enter to exit: ";
		cin >> ab;
	} while (ab != 'a');
	return 0;
}
