#include "Node.h"
#include "Editor.h"

Node::Node(char letter)
{
	c = letter;
	prev = next = nullptr;
}
