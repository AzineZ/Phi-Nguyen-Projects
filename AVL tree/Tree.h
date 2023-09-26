#pragma once
#include <iostream>
#include "Node.h"
#include <windows.h>
using namespace std;



class Tree
{
public:
	Node* root = nullptr;

	//return root
	Node* giveroot();

	//starting coordinates
	int xpos = 69;
	int ypos = 4;

	//constructor
	Tree();

	//display tree
	void display(Node* r, int xpos, int ypos, int width);

	//display NLR
	void nlr(Node* r);

	//go to a location on console
	void gotoxy(int x, int y);

	//add number to tree
	Node* insert(Node* r, int x);

	//delete number from tree
	Node* del(Node* r, int x);

	//calculate height of a node
	int height(Node* r);

	//find difference between both sides of a node
	int difference(Node* r);

	//rotating functions
	Node* rightright(Node* r);
	Node* leftleft(Node* r);
	Node* leftright(Node* r);
	Node* rightleft(Node* r);
	Node* rebalance(Node* r);
};