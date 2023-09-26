#include <iostream>
#include <conio.h> // for _getch()
#include "Editor.h" //for the class editor which also contains class node
#include <windows.h>
using namespace std;

//function declaration
void setFontSize(int FontSize);

int main()
{
	//set font size to 20
	setFontSize(20);

	//automatically go to windowed fullscreen mode
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

	//make white background and black text
	system("color 70");

	//create the editor
	Editor ed;

	while (1) //LOOP INFINITELY
	{
		//print menu
		ed.displaymenu();

		ed.getchar();

		//EXIT WHEN ESC IS PRESSED
		if (ed.letter == 27)
		{
			system("cls");
			cout << "Thank you for using my editor." << endl;
			break; //break out of loop
		}

		//DELETE ONE CHARACTER WHEN BACKSPACE IS PRESSED
		else if (ed.letter == 8)
		{
			//delete one character
			ed.erase();
		}

		//NEW LINE WHEN ENTER IS PRESSED
		else if (ed.letter == 13)
		{
			//go down new line
			ed.newline();
		}

		//NAVIGATING USING ARROWS
		else if (ed.letter == -32)
		{
			ed.getchar();
			ed.move();
		}

		//OPERATION WITH FILE
		else if (ed.letter == 0)
		{
			ed.getchar();

			//WRITE TO FILE
			if (ed.letter == 59)
			{
				ed.write();
			}

			//READ FROM FILE
			else if (ed.letter == 60)
			{
				ed.read();
			}
		}

		//NORMAL CHARACTER
		else
		{
			ed.add(ed.letter);
		}

		//DISPLAY THE LINKED LIST PROPERLY
		system("cls");
		ed.display();
	}

	//DELETE ALLOCATED MEMORY
	ed.deallocate();
	return 0;
}

//function definition
void setFontSize(int FontSize)
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = FontSize; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}