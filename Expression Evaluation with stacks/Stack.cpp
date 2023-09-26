#include <iostream>
#include <fstream>
#include "Stack.h"
#include <string>
#include <windows.h>

//initialize variables
Expression::Expression()
{
	countnums = countops = final = answer = 0;

}


//manipulate cursor
void Expression::gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

//push operator to operator stack
void Expression::pushop(char c)
{
	ops[countops] = c;
	countops++;
}

//push number to number stack
void Expression::pushnum(int c)
{
	/*int ia = c - '0';*/
	nums[countnums] = c;
	countnums++;
}

//pop number from num stack
int Expression::popnum()
{
	int temp = nums[countnums - 1];
	nums[countnums - 1] = 0;
	countnums--;
	return temp;
}

//pop operator from op stack
char Expression::popop()
{
	char temp = ops[countops - 1];
	ops[countops - 1] = '\0';
	countops--;
	return temp;
}

//return the priority of the operator
int Expression::precedence(char c)
{
	if (c == '+' || c == '-')
		return 1;
	else if (c == '*' || c == '/')
		return 2;
	else
		return 0; //give () lowest priority
}

//pop 2 numbers and 1 operator, animate as well
int Expression::solve()
{
	int num2 = popnum();
	int num1 = popnum();
	char op = popop();
	int answer;
	switch (op)
	{
	case '+':
		answer = num1 + num2;
		animatesolve(num1, num2, op, answer);
		return answer;
	case '-':
		answer = num1 - num2;
		animatesolve(num1, num2, op, answer);
		return answer;
	case '*':
		answer = num1 * num2;
		animatesolve(num1, num2, op, answer);
		return answer;
	case '/':
		answer = num1 / num2;
		animatesolve(num1, num2, op, answer);
		return answer;
	default:
		return 0;
	}
}

void Expression::evaluate()
{
	ifstream in;
	in.open("C:\\temp\\input.txt");
	if (in.is_open())
	{
		while (in.get(c))
		{
			if (isdigit(c)) //if it's a number
			{
				char nextchar = in.peek(); //check next character to see if it's a number
				if (isdigit(nextchar)) //2 digits
				{
					//get the next number and combine the two numbers
					in.get(nextchar);
					string s1{ c };
					string s2{ nextchar };
					string s = s1 + s2;
					int num2di = stoi(s);
					pushnum(num2di);
					animatepushnum(2, num2di);
				}
				else //1 digit
				{
					string ss{ c };
					int num1di = stoi(ss);
					pushnum(num1di);
					animatepushnum(1, num1di);
				}
			}
			else if (c == '(')
			{
				//push ( and animate
				pushop(c);
				animatepushop(c);
			}
			else if (c == ')')
			{
				//solve issue for many operators inside parenthesis
				animatepushop(c);
				if (ops[countops - 1] != '(') //solve the expression inside ()
				{
					animatepopbrackets(c); //animate ')'
					while (ops[countops - 1] != '(')
					{
						answer = solve();
						nums[countnums] = answer;
						countnums++;
					}
					animatepopbrackets(ops[countops - 1]);
				}
				ops[countops - 1] = '\0';
				countops--;
			}
			else if (c == '+' || c == '-' || c == '*' || c == '/')
			{
				//if stack op is empty or top stack op is smaller than c
				if (countops == 0 || precedence(c) > precedence(ops[countops - 1]))
				{
					pushop(c);
					animatepushop(c);
				}
				//if top stack op is bigger or equal to c
				else if (precedence(c) <= precedence(ops[countops - 1]))
				{
					//repeat as long as op stack is not empty and top of op stack >= c
					while (countops != 0 && precedence(c) <= precedence(ops[countops - 1]))
					{
						answer = solve();
						nums[countnums] = answer;
						countnums++;
					}
					pushop(c);
					animatepushop(c);
				}
			}
		}
		while (countops != 0)
		{
			final = solve();
			nums[countnums] = final;
			countnums++;
		}
	}
	in.close();
	gotoxy(xlocation, ylocation - 1); //go to the end of expression and print final answer
	cout << "  =  " << final;
}

//return final answer
int Expression::finalanswer()
{
	return final;
}

//print expression
void Expression::displayexp()
{
	ifstream inf;
	char a;
	int counter = 0;
	inf.open("C:\\temp\\input.txt");
	if (inf.is_open())
	{
		gotoxy(0, 1);
		while (inf.get(a))
		{
			display[counter] = a;
			counter++;
		}
	}
	for (int i = 0; i <= counter; i++)
		cout << display[i];

	inf.close();
}

//animate number being pushed into stack
void Expression::animatepushnum(int digit, int num)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int m = xlocation;
	int n = ylocation;
	gotoxy(m, n);
	SetConsoleTextAttribute(hConsole, 15);
	cout << num;
	Sleep(500);
	while (m != numstacklocation)
	{
		gotoxy(m, n);
		SetConsoleTextAttribute(hConsole, 15);
		cout << num;
		Sleep(20);
		gotoxy(m, n);
		SetConsoleTextAttribute(hConsole, 0);
		cout << num;
		m++;
	}

	int z = ylocation;
	while (z != numstackbottom)
	{
		gotoxy(m, z);
		SetConsoleTextAttribute(hConsole, 15);
		cout << num;
		Sleep(50);
		gotoxy(m, z);
		SetConsoleTextAttribute(hConsole, 0);
		cout << num;
		z++;
	}
	gotoxy(numstacklocation, z - 1);
	SetConsoleTextAttribute(hConsole, 15);
	cout << num;
	xlocation = xlocation + digit;
	numstackbottom--;
	
}

//animate operator being push to stack
void Expression::animatepushop(char c)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int m = xlocation;
	int n = ylocation;
	gotoxy(m, n);
	SetConsoleTextAttribute(hConsole, 15);
	cout << c;
	Sleep(500);
	while (m != opstacklocation)
	{
		gotoxy(m, n);
		SetConsoleTextAttribute(hConsole, 15);
		cout << c;
		Sleep(20);
		gotoxy(m, n);
		SetConsoleTextAttribute(hConsole, 0);
		cout << c;
		m++;
	}

	int z = ylocation;
	while (z != opstackbottom)
	{
		gotoxy(m, z);
		SetConsoleTextAttribute(hConsole, 15);
		cout << c;
		Sleep(50);
		gotoxy(m, z);
		SetConsoleTextAttribute(hConsole, 0);
		cout << c;
		z++;
	}
	gotoxy(opstacklocation, z - 1);
	SetConsoleTextAttribute(hConsole, 15);
	cout << c;
	xlocation++;
	opstackbottom--;
}

//animate solving (move num2 then op then num1)
void Expression::animatesolve(int num1, int num2, char op, int answer)
{
	//PRE SOLVE
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//move num2
	int numX = numstacklocation;
	int numY = numstackbottom;
	int opX = opstacklocation;
	int opY = opstackbottom;
	int i = 0;

	while (numY != ylocation) // move up
	{
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << num2;
		Sleep(50);
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << num2;
		numY--;
	}
	while (i != 20)
	{
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << num2;
		Sleep(20);
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << num2;
		numX++;
		i++;
	}
	gotoxy(numX, numY);
	SetConsoleTextAttribute(hConsole, 15);
	cout << num2;
	numstackbottom++;
	numY = numstackbottom;
	numX = numstacklocation;
	i = 0;


	//move op
	while (opY != 4) // move up
	{
		gotoxy(opX, opY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << op;
		Sleep(50);
		gotoxy(opX, opY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << op;
		opY--;
	}
	while (i != 13)
	{
		gotoxy(opX, opY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << op;
		Sleep(20);
		gotoxy(opX, opY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << op;
		opX--;
		i++;
	}
	while (opY != ylocation) // move up
	{
		gotoxy(opX, opY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << op;
		Sleep(50);
		gotoxy(opX, opY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << op;
		opY--;
	}
	gotoxy(opX, opY);
	SetConsoleTextAttribute(hConsole, 15);
	cout << op;
	opstackbottom++;
	opY = opstackbottom;
	opX = opstacklocation;
	i = 0;


	//move num1
	while (numY != ylocation) // move up
	{
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << num1;
		Sleep(50);
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << num1;
		numY--;
	}
	while (i != 5)
	{
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << num1;
		Sleep(20);
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << num1;
		numX++;
		i++;
	}
	gotoxy(numX, numY);
	SetConsoleTextAttribute(hConsole, 15);
	cout << num1;
	numstackbottom++;
	numY = numstackbottom;
	numX = numstacklocation;
	i = 0;

	Sleep(300);
	gotoxy(85, ylocation);
	cout << " =   " << answer;
	Sleep(500);
	gotoxy(66, ylocation);
	SetConsoleTextAttribute(hConsole, 0);
	cout << num1;
	gotoxy(74, ylocation);
	SetConsoleTextAttribute(hConsole, 0);
	cout << num1;
	gotoxy(81, ylocation);
	SetConsoleTextAttribute(hConsole, 0);
	cout << num2;
	gotoxy(86, ylocation);
	SetConsoleTextAttribute(hConsole, 0);
	cout << '=';

	//put answer back to stack
	numX = 90;
	numY = ylocation;
	while (numX != numstacklocation)
	{
		gotoxy(numX, numY); //move left
		SetConsoleTextAttribute(hConsole, 15);
		cout << answer;
		Sleep(20);
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << answer;
		numX--;
	}
	while (numY != numstackbottom) // move down
	{
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << answer;
		Sleep(50);
		gotoxy(numX, numY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << answer;
		numY++;
	}
	gotoxy(numX, numY - 1);
	SetConsoleTextAttribute(hConsole, 15);
	cout << answer;
	numstackbottom--;
}

//animate popping ( and )
void Expression::animatepopbrackets(char bracket)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int opX = opstacklocation;
	int opY = opstackbottom;
	while (opY != 0) // move up
	{
		gotoxy(opX, opY);
		SetConsoleTextAttribute(hConsole, 15);
		cout << bracket;
		Sleep(30);
		gotoxy(opX, opY);
		SetConsoleTextAttribute(hConsole, 0);
		cout << bracket;
		opY--;
	}
	opstackbottom++;
}


//display stacks
void Expression::displaystacks()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int x = 60;
	int y = 10;
	int a = 25;
	for (int i = 0; i < 20; i++)
	{
		gotoxy(x, y);
		SetConsoleTextAttribute(hConsole, 9);
		cout << char(219) << "   " << char(219);
		gotoxy(x + a, y);
		SetConsoleTextAttribute(hConsole, 10);
		cout << char(219) << "   " << char(219);
		y++;
	}
	gotoxy(x, y);
	for (int i = 0; i < 5; i++)
	{
		SetConsoleTextAttribute(hConsole, 9);
		cout << char(219);

	}
	gotoxy(x + a, y);
	for (int i = 0; i < 5; i++)
	{
		SetConsoleTextAttribute(hConsole, 10);
		cout << char(219);

	}
	gotoxy(59, 32);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Operands                Operators";
}
