#include <iostream>
#include <fstream>
#include "Stack.h"
#include <windows.h>
using namespace std;

int main()
{
	//play some music
	PlaySound(TEXT("ANbySP.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	cout << "Your expression: " << endl;

	Expression ex;
	ex.displaystacks();
	ex.displayexp();
	ex.evaluate();
	
	return 0;
}