#include <iostream>
#include <ctime>    // for time
#include "World.h"
#include "windows.h" //for playsound
#include <conio.h> // for kbhit, getch
using namespace std;

//Function declarations

//set cursor location
void gotoxy(int x, int y);

//hide cursor
void ShowConsoleCursor(bool showFlag);

//move title from bottom up
void title();


int main()
{
    //play wav file in background
    PlaySound(TEXT("ANbySP.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //make program runs on windowed fullscreen automatically so everything is aligned in the center
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);

    //hide cursor
    ShowConsoleCursor(false);
    char ch;

    //display title animation
    title();

    //sleep to match with the music
    Sleep(2000);
    system("cls");
    World myWorld(time(0));
    myWorld.display();

    while (1)
    {   
        //add and print correct organism when a specific key is pressed
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'a' || ch == 'A')
            {
                myWorld.createOrganisms(ANT, 1);
                gotoxy(44, 2);
                SetConsoleTextAttribute(hConsole, 12);
                cout << "   One ant added!";
                Sleep(150);
                gotoxy(44, 2);
                SetConsoleTextAttribute(hConsole, 0);
                cout << "   One ant added!";
            }
            else if (ch == 'b' || ch == 'B')
            {
                myWorld.createOrganisms(BUG, 1);
                gotoxy(44, 2);
                SetConsoleTextAttribute(hConsole, 10);
                cout << "   One bug added!";
                Sleep(150);
                gotoxy(44, 2);
                SetConsoleTextAttribute(hConsole, 0);
                cout << "   One bug added!";
            }
            else if (ch == 't' || ch == 'T')
            {
                myWorld.createOrganisms(TWINBUG, 2);
                gotoxy(44, 2);
                SetConsoleTextAttribute(hConsole, 14);
                cout << "Two twin bugs added!";
                Sleep(150);
                gotoxy(44, 2);
                SetConsoleTextAttribute(hConsole, 0);
                cout << "Two twin bugs added!";
            }
        }
        
        myWorld.simulateOneStep();
        myWorld.display();
        Sleep(500);
    }
    return 0;
}


//Function Definitions
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}




void title()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = 20;
    while (x != 0)
    {
        system("cls");
        gotoxy(35, 2 + x);
        SetConsoleTextAttribute(hConsole, 10);
        cout << " _______ _            ____  " << endl;
        gotoxy(35, 3 + x);
        SetConsoleTextAttribute(hConsole, 9);
        cout << "|__   __| |          |  _ \\ " << endl;
        gotoxy(35, 4 + x);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "   | |  | |__   ___  | |_) |_   _  __ _ " << endl;
        gotoxy(35, 5 + x);
        SetConsoleTextAttribute(hConsole, 9);
        cout << "   | |  | '_ \\ / _ \\ |  _ <| | | |/ _` |" << endl;
        gotoxy(35, 6 + x);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "   | |  | | | |  __/ | |_) | |_| | (_| |" << endl;
        gotoxy(35, 7 + x);
        SetConsoleTextAttribute(hConsole, 9);
        cout << "   |_|__|_| |_|\\___| |____/ \\__,_|\\__, |" << endl;
        gotoxy(35, 8 + x);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "    / ____|                        __/ |" << endl;
        gotoxy(35, 9 + x);
        SetConsoleTextAttribute(hConsole, 9);
        cout << "   | |  __  __ _ _ __ ___   ___   |___/ " << endl;
        gotoxy(35, 10 + x);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "   | | |_ |/ _` | '_ ` _ \\ / _ \\        " << endl;
        gotoxy(35, 11 + x);
        SetConsoleTextAttribute(hConsole, 9);
        cout << "   | |__| | (_| | | | | | |  __/        " << endl;
        gotoxy(35, 12 + x);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "    \\_____|\\__,_|_| |_| |_|\\___|        " << endl;
        x--;
        Sleep(70);
    }                          
    SetConsoleTextAttribute(hConsole, 15);
}

