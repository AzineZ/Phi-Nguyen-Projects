#include <iostream>
#include "Editor.h"
#include <conio.h>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;


//MANIPULATE CURSOR
void gotoxy(int x, int y) {

	COORD pos = { x, y };

	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(output, pos);

}

//CONSTRUCTOR
Editor::Editor()
{
	letter = ' ';
	for (int i = 0; i < 10; i++)
		rows[i] = nullptr;

	x = y = rowNums = 0;
	start = curr = end = nullptr;
}

//ASSIGN CHARACTER TO LETTER VARIABLE
void Editor::getchar()
{
	letter = _getch();
}

//GO DOWN ONE LINE AND MAKE THESE POINTERS POINT TO NULL LIKE THE BEGINNING
void Editor::newline()
{
	rowNums++;
	start = end = curr = rows[rowNums];
	x = 0;
	y++;
}

//MAKE NEW NODE WITH CHARACTER THAT WAS PRESSED
void Editor::add(char letter)
{
	if (start == nullptr) //BEGINNING OF THE LINKED LIST
	{
		Node* p = new Node(letter);
		start = p;
		end = p;
		curr = p;
		rows[rowNums] = start;
		start->prev = rows[rowNums];
		x++;
	}
	else if (start != nullptr) //NOT BEGINNING OF THE LINKED LIST
	{
		if (curr == end) //AT THE END OF LINKED LIST
		{
			Node* p = new Node(letter);
			end->next = p;
			p->prev = end;
			end = p;
			curr = end;
			x++;
		}
		else if (curr == start && x == 0) //ADD MORE TO THE HEAD OF LINKED LIST
		{
			Node* p = new Node(letter);
			p->next = start;
			start->prev = p;
			curr = p;
			rows[rowNums] = p;
			start = p;
			x++;
		}
		else if (curr != end) //BETWEEN START AND END
		{
			Node* p = new Node(letter);
			p->next = curr->next;
			curr->next->prev = p;
			curr->next = p;
			p->prev = curr;
			curr = curr->next;
			x++;
		}
	}
			
}

//DELETE ONE CHARACTER
void Editor::erase()
{
	{
		//when we at the head of the linked list
		if (end == rows[rowNums])
		{
			//if we have a row above 
			if (rowNums > 0)
			{
				if (rows[rowNums - 1] == nullptr) //BLANK ROW ABOVE, DELETE CURRENT ROW AND MOVE TO THAT BLANK ROW
				{
					rowNums--;
					start = end = curr = rows[rowNums];
					delete(rows[rowNums + 1]);
					rows[rowNums + 1] = nullptr;
					x = 0;
					y--;
				}
				else //NO BLANK ROW ABOVE, DELETE CURRENT ROW AND MOVE TO LAST NODE OF THE LINKED LIST IN THE ROW ABOVE
				{
					rowNums--;
					x = 1;
					start = rows[rowNums];
					end = start;
					while (end->next != nullptr)
					{
						end = end->next;
						x++;
					}
					curr = end;
					y--;
					delete(rows[rowNums + 1]);
					rows[rowNums + 1] = nullptr;

				}
			}

			//if we're at the first row, delete row and make everything point to nullptr like beginning
			else if (rowNums == 0)
			{
				delete (rows[rowNums]);
				rows[rowNums] = start = end = curr = nullptr;
				x = 0;
			}
		}

		//if we're not at the head of the linked list
		else
		{
			end = end->prev;
			curr = curr->prev;
			delete(end->next);
			end->next = nullptr;
			x--;
		}
	}
}

//DISPLAY THE ROWS OF LINKED LISTS
void Editor::display()
{
	for (int i = 0; i < 10; i++)
	{
		if (rows[i] != nullptr)
		{
			Node* t;
			t = rows[i];
			while (t != nullptr)
			{
				cout << t->c;
				t = t->next;
			}
		}
		cout << endl;

	}
	gotoxy(x, y);
}

//MOVE CURSOR AND CURR CORRESPONDINGLY TO THE ASCII CODE OF THE ARROW KEY PRESSED
void Editor::move()
{
	{
		//LEFT
		if (letter == 75)
		{
			if (curr == start) 
			{
				if (x == 0) {} //PREVENT CURSOR FROM GOING OUT OF SCREEN
				else
				{
					x--;
				}
			}
			else
			{
				curr = curr->prev;
				x--;
			}
		}

		//RIGHT
		else if (letter == 77)
		{
			if (curr == end) {} //PREVENT CURSOR FROM GOING OUT OF SCREEN
			else
			{
				curr = curr->next;
				x++;
			}
		}

		//UP
		else if (letter == 72)
		{
			if (rowNums != 0) //NOT FIRST ROW
			{
				if (rows[rowNums - 1] == nullptr) //IF ROW ABOVE IS BLANK, MOVE UP AND ASSIGN POINTERS TO NULL
				{
					rowNums--;
					start = end = curr = rows[rowNums];
					x = 0;
					y--;
				}
				else //MOVE UP, MAKE CURR AND CURSOR GO TO THE nth LOCATION THAT MATCH THE nth LOCATION BELOW
				{
					int counter = 0;
					int counter2 = 0;
					Node* a;
					a = rows[rowNums];
					while (a != curr)
					{
						a = a->next;
						counter++;
					}
					rowNums--;
					start = rows[rowNums];
					a = rows[rowNums];
					end = start;
					while (end->next != nullptr)
						end = end->next;

					while (a->next != nullptr && counter != 0)
					{
						a = a->next;
						counter--;
						counter2++;
					}
					curr = a;
					y--;
					x = counter2 + 1;
				}
			}
			else {}
		}

		//DOWN
		else if (letter == 80)
		{
			if (rowNums != 10 && rows[rowNums + 1] == nullptr) //NOT OUT OF ARRAY AND BELOW IS BLANK
			{
				bool end_of_file = true;
				for (int i = rowNums + 1; i < 10; i++) //CHECK THE LOWER REST OF ARRAY TO SEE IF ANY OF THE TEXTS BELOW THAT ROW EXIST
				{
					if (rows[i] != nullptr)
					{
						end_of_file = false;
						break;
					}
				}
				if (end_of_file == false) //IF FALSE MEANS THERE ARE TEXTS BELOW THE BLANK ROW, GO DOWN ONE LINE.
				{
					newline();
				}
			}

			else if (rowNums != 10 && rows[rowNums + 1] != nullptr) //NOT OUT OF ARRAY AND BELOW IS NOT BLANK
			{
				//SIMILAR TO UP WHEN ABOVE IS NOT BLANK, EXCEPT CHANGE THE CURR AND CURSOR TO GO DOWN
				int counter = 0;
				int counter2 = 0;
				Node* a;
				a = rows[rowNums];
				while (a != curr)
				{
					a = a->next;
					counter++;
				}
				rowNums++;
				start = rows[rowNums];
				a = rows[rowNums];
				end = start;
				while (end->next != nullptr)
					end = end->next;

				while (a->next != nullptr && counter != 0)
				{
					a = a->next;
					counter--;
					counter2++;
				}
				curr = a;
				y++;
				x = counter2 + 1;
			}
		}
		else
			return;
	}
}

//WRITE TO EXISTING FILE OR MAKE NEW ONE
void Editor::write()
{
	//PROMPT USER FOR THEIR FILE PATH
	cout << "\n\nEnter file path of existing text file or create a new one \n";
	cout << "For example: C:\\Users\\nph69\\Desktop\\CS135\\filename.txt" << endl;
	cout << "Enter here: ";
	string a;
	getline(cin, a);
	ofstream out;
	out.open(a);

	//IF FILE IS OPENED OR CREATED
	if (out.is_open())
	{
		PlaySound(TEXT("Airline_sound.wav"), NULL, SND_FILENAME | SND_ASYNC); //SMALL NICE SOUND FOR INNOVATION
		for (int i = 0; i < 10; i++)
		{
			if (rows[i] != nullptr)
			{
				Node* t;
				t = rows[i];
				while (t != nullptr)
				{
					out << t->c;
					t = t->next;
				}
				out << endl;
			}
		}
		out.close();  //close the file
		cout << "Your file was successfuly written!";
		Sleep(1500);
	}

	else
	{
		PlaySound(TEXT("error_sound.wav"), NULL, SND_FILENAME | SND_ASYNC); //ERROR SOUND
		cout << "Failed to open file!\n";
		cout << "Please press F1 again and re-enter file path if you want to retry.";
		Sleep(2000);
		system("cls");
	}
}

//READ FROM AN EXISTING FILE
void Editor::read()
{
	//PROMPT USER FOR THEIR FILE PATH
	cout << "\nEnter or paste the exact file path\n";
	cout<<"For example: C:\\Users\\nph69\\Desktop\\CS135\\filename.txt\n";
	cout << "Enter here: ";
	string a;
	getline(cin, a);
	ifstream in;
	in.open(a);

	//IF FILE IS OPENED
	if (in.is_open())
	{
		PlaySound(TEXT("Airline_dual_sound.wav"), NULL, SND_FILENAME | SND_ASYNC); // NICE SOUND
		cout << "Successful!";
		Sleep(1000);
		bool exist = false;

		//DELETING EXISTING TEXT IF EXIST
		for (int i = 0; i < rowNums; i++)
		{
			if (rows[i] != nullptr)
			{
				exist = true;
				break;
			}
		}
		if (exist == true)
		{
			deallocate();
		}
		start = end = curr = nullptr;
		rowNums = 0;
		x = y = 0;
		char c;
		while (in.get(c)) //do this as long as we can get character from the file
		{
			if (c == '\n')
			{
				newline(); //IF END OF LINE IN THE FILE, DO THE SAME THING FOR THE LINKED LIST
			}
			else
			{
				add(c);
			}
		}
		in.close(); //close the file
	}
	else
	{
		PlaySound(TEXT("error_sound.wav"), NULL, SND_FILENAME | SND_ASYNC); //ERROR SOUND
		cout << "Failed to open file!\n";
		cout << "Please press F2 again and re-enter file path if you want to retry.";
		Sleep(2000);
		system("cls");
	}	
}

//DELETE DYNAMICALLY ALLOCATED MEMORY
void Editor::deallocate()
{
	for (int i = 0; i < 10; i++)
	{
		if (rows[i] != nullptr)
		{
			Node* t;
			t = rows[i];
			while (t->next != nullptr)
			{
				t = t->next;
				delete (t->prev);
			}
			rows[i] = nullptr;
		}
	}
}

//DISPLAY MENU NEAR THE BOTTOM OF THE SCREEN
void Editor::displaymenu()
{
	gotoxy(0, 43);
	for (int i = 0; i < 123; i++)
		cout << '-';
	cout << endl;
	cout << "| Ln " << x + 1 << " Col " << y + 1 << " |-------------| ";
	cout << "MENU: Delete (BACKSPACE) | Navigating (ARROW KEYS)\n";
	cout << "                                   Write to file (F1) | Read from file(F2) | Exit (ESC)";
	gotoxy(x, y);
}