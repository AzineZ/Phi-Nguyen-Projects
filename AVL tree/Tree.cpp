#include "Tree.h"
#include <fstream>
#include <Windows.h>
#include <algorithm>
using namespace std;

Node* Tree::giveroot()
{
	return root;
}


Tree::Tree()
{
	root = nullptr;
}


void Tree::display(Node* r, int xpos, int ypos, int width)
{
	if (r == nullptr)
		return;
	gotoxy(xpos, ypos);
	cout << r->num;
	width = width / 2;

	if (r->right != nullptr)
	{
		gotoxy(xpos, ypos + 1);
		cout << '|';
		for (int i = xpos; i < xpos + width; i++)
			cout << '-';
		gotoxy(xpos + width, ypos + 2);
		cout << '|';
	}
	display(r->right, xpos + width, ypos + 3, width);

	if (r->left != nullptr)
	{
		gotoxy(xpos, ypos + 1);
		cout << '|';
		for (int y = xpos; y > xpos - width; y--)
		{
			gotoxy(y - 1, ypos + 1);
			cout << '-';
		}
		gotoxy(xpos - width, ypos + 2);
		cout << '|';
	}
	display(r->left, xpos - width, ypos + 3, width);
}

void Tree::nlr(Node* r)
{
	cout << r->num << ' ';

	if (r->left != nullptr)
		nlr(r->left);

	if (r->right != nullptr)
		nlr(r->right);
}

void Tree::gotoxy(int x, int y)
{
	{
		static HANDLE h = NULL;
		if (!h)
			h = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD c = { x, y };
		SetConsoleCursorPosition(h, c);
	}
}

Node* Tree::insert(Node* r, int x)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0);
	display(root, xpos, ypos, 60);
	if (root == nullptr)
	{
		Node* p = new Node(x);
		root = p;
		SetConsoleTextAttribute(hConsole, 15);
		display(root, xpos, ypos, 60);
	}

	else if (x < r->num)
	{
		if (r->left == nullptr)
		{
			Node* p = new Node(x);
			r->left = p;
		}
		else
		{
			r->left = insert(r->left, x);
			r = rebalance(r);
		}
	}

	else if (x > r->num)
	{
		if (r->right == nullptr)
		{
			Node* p = new Node(x);
			r->right = p;
		}
		else
		{
			r->right = insert(r->right, x);
			r = rebalance(r);
		}
	}

	if (r == root)
	{
		SetConsoleTextAttribute(hConsole, 15);
		display(root, xpos, ypos, 60);
	}
	return r;

}

Node* Tree::del(Node* r, int x)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 0);
	display(root, xpos, ypos, 60);

	if (x < r->num)
	{
		r->left = del(r->left, x);
		if (r == root)
		{
			r = rebalance(r);
			root = r;
		}
		else
			r = rebalance(r);
	}

	else if (x > r->num)
	{
		r->right = del(r->right, x);
		if (r == root)
		{
			r = rebalance(r);
			root = r;
		}
		else
			r = rebalance(r);
	}

	else if (x == r->num)
	{
		//WHEN LEFT AND RIGHT OF TARGET ARE NULLPTR
		if (r->left == nullptr && r->right == nullptr)
		{
			if (r == root)
			{
				delete(r);
				root = nullptr;
				return root;
			}

			else if (r != root)
			{
				delete(r);
				r = nullptr;
				return r;
			}
		}

		//WHEN THERE'S AT LEAST ONE SIDE IS NOT NULLPTR
		else
		{
			//IF LEFT IS NULLPTR AND RIGHT HAS SOMETHING
			if (r->left == nullptr)
			{
				Node* temp = r->right;
				if (r == root)
				{
					delete(r);
					root = temp;
					root = rebalance(root);
					SetConsoleTextAttribute(hConsole, 15);
					display(root, xpos, ypos, 60);
				}
				else
					delete(r);
				return temp;
			}

			//if left is not nulltpr
			else if (r->left != nullptr)
			{
				//IF RIGHT HAS NOTHING AFTER GOING LEFT
				if (r->left->right == nullptr)
				{
					//if right has something
					if (r->right != nullptr)
					{
						Node* temp = r->left;
						temp->right = r->right;
						if (r == root)
						{
							delete(r);
							root = temp;
							root = rebalance(root);
							SetConsoleTextAttribute(hConsole, 15);
							display(root, xpos, ypos, 60);
						}
						else
							delete(r);
						return temp;
					}

					//if right has nothing
					else if (r->right == nullptr)
					{
						Node* temp = r->left;
						if (r == root)
						{
							delete(r);
							root = temp;
							root = rebalance(root);
							SetConsoleTextAttribute(hConsole, 15);
							display(root, xpos, ypos, 60);
						}
						else
							delete(r);
						return temp;
					}
				}

				//IF right has something after going left
				else if (r->left->right != nullptr)
				{
					Node* temp = r->left;
					while (temp->right->right != nullptr)
					{
						temp = temp->right;
					}

					if (temp->right->left == nullptr)
					{
						r->num = temp->right->num;
						delete(temp->right);
						temp->right = nullptr;
						if (r == root)
						{
							root = rebalance(root);
							SetConsoleTextAttribute(hConsole, 15);
							display(root, xpos, ypos, 60);
						}
						return r;
					}

					else if (temp->right->left != nullptr)
					{
						r->num = temp->right->num;
						Node* temp2 = temp->right->left;
						delete(temp->right);
						temp->right = temp2;
						if (r == root)
						{
							root = rebalance(root);
							SetConsoleTextAttribute(hConsole, 15);
							display(root, xpos, ypos, 60);
						}
						return r;
					}
				}
			}
		}
	}

	if (r == root)
	{
		SetConsoleTextAttribute(hConsole, 15);
		display(root, xpos, ypos, 60);
	}
	return r;
}

int Tree::height(Node* r)
{
	int h = 0;
	if (r != nullptr)
	{
		int lh = height(r->left);
		int rh = height(r->right);
		int max_h = max(lh, rh);
		h = max_h + 1;
		return h;
	}
	return h;
}

int Tree::difference(Node* r)
{
	int lh = height(r->left);
	int rh = height(r->right);
	int diff = lh - rh;
	return diff;
}

Node* Tree::rightright(Node* r)
{
	Node* temp;
	temp = r->right;
	r->right = temp->left;
	temp->left = r;
	return temp;
}

Node* Tree::leftleft(Node* r)
{
	Node* temp;
	temp = r->left;
	r->left = temp->right;
	temp->right = r;
	return temp;
}

Node* Tree::leftright(Node* r)
{
	Node* temp;
	temp = r->left;
	r->left = rightright(temp);
	return leftleft(r);
}

Node* Tree::rightleft(Node* r)
{
	Node* temp;
	temp = r->right;
	r->right = leftleft(temp);
	return rightright(r);
}

Node* Tree::rebalance(Node* r)
{
	Node* temp = r;
	int bl_factor = difference(r);
	if (bl_factor > 1)
	{
		if (difference(r->left) > 0)
			r = leftleft(r);
		else
			r = leftright(r);
	}

	else if (bl_factor < -1)
	{
		if (difference(r->right) > 0)
			r = rightleft(r);
		else
			r = rightright(r);
	}
	
	if (temp == root)
	{
		root = r;
	}
	return r;
}
