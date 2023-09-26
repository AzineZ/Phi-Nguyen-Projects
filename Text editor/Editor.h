#pragma once
#include "Node.h"

//class for linked list
class Editor
{
public:
	//WHERE CHARACTER IS STORED
	char letter;

	//X & Y FOR CURSOR LOCATION, ROWNUMS FOR ROWS ARRAY
	int x, y, rowNums;

	//CREATE POINTERS THAT LOCATE HEAD AND TAIL AND CURRENT LOCATION IN THE LINKED LIST
	Node* start;
	Node* end;
	Node* curr;

	//ROWS OF LINKED LISTS
	Node* rows[10];

	//CONSTRUCTOR
	Editor();

	//GET CHARACTER
	void getchar();

	//GO DOWN ONE LINE WHEN ENTER IS PRESSED
	void newline();

	//MAKE A LINKED LIST WITH CHARACTER FROM PARAMETER
	void add(char letter);

	//DELETE ONE CHARACTER
	void erase();

	//PRINT OUT WHAT'S IN THE MEMORY PRECISELY
	void display();

	//NAVIGATING WITH ARROWS
	void move();

	//WRITE TO A FILE OR CREATE NEW ONE AND WRITE TO IT
	void write();

	//READ FROM FILE
	void read();

	//DELETE ALLOCATED MEMORY
	void deallocate();

	//PRINT MENU BELOW THE TEXT NEAR BOTTOM OF THE SCREEN
	void displaymenu();
};
