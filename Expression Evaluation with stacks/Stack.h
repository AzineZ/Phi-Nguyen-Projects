#pragma once
#include <iostream>
using namespace std;

class Expression
{
public:
	//stack for operands
	int nums[10] = {};

	//stack for operators
	char ops[10] = {};

	//array to display expression
	char display[30] = {};

	//operand stack x location
	int numstacklocation = 61;

	//operator stack x location
	int opstacklocation = 87;

	//operand stack limit
	int numstackbottom = 30;

	//operator stack limit
	int opstackbottom = 30;

	//point to the location of the number about to be moved on screen
	int xlocation = 0;

	//location of expression on screen
	int ylocation = 2;

	//counters for operand and operator stacks. Answer for after everytime
	//numbers are popped out for solving and final for final answer for the expression
	//Initialize them by 0
	int countnums, countops, final, answer;

	//a char variable to get a character in the file
	char c;

	//Constructor
	Expression();

	//manipulate cursor
	void gotoxy(int x, int y);

	//push a number into operand stack
	void pushop(char c);

	//push an operator or bracket into operator stack
	void pushnum(int c);

	//pop a number from operand stack
	int popnum();

	//pop an operator or bracket from operator stack
	char popop();

	//return priority of the operator
	int precedence(char c);

	//solve the two operands and one operator that are popped out for solving
	int solve();

	//evaluate the expression, animate as well
	void evaluate();

	//return final answer. 
	int finalanswer();

	//display expression on screen
	void displayexp();

	//define
	//animate number moving to operand stack
	void animatepushnum(int digit, int num);

	//draw stacks on screen
	void displaystacks();

	//animate operators/brackets moving to operator stack
	void animatepushop(char c);

	//animate numbers and operator popped out and solve
	void animatesolve(int num1, int num2, char op, int answer);

	//pop brackets
	void animatepopbrackets(char bracket);
};