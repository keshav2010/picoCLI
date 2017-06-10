#include "stack.h"
#include<string>
#include<iostream>
using namespace std;
//Not using STL at the moment ... 
//stack.cpp is just temporary work-around till a more suitable solution is found
node::node()
{
	cmd = " ";
	next = NULL;
}
stack::stack()
{
	top = NULL;
	temp = NULL;
}
void stack::pop()
{
	temp = top;
	if (temp == NULL)
		return;
	top = top->next;
	delete temp;
}
int stack::isEmpty() {
	return (top == NULL) ? 1 : 0;
}
void stack::clear() {
	temp = top;
	while (temp != NULL)
	{
		top = top->next;
		delete temp;
		temp = top;
	}
}
string stack::read(int index)
{
	if (index >= 0 && index <= MAX_SIZE - 1)
	{
		int begin = 0;
		temp = top;
		while (temp != NULL)
		{
			if (begin == index)
			{
				return temp->cmd;
				break;
			}
			begin++;
			temp = temp->next;
		}
	}
	else
	{
		cout << "\nINDEX OUT OF STACK RANGE\n";
		return NULL;
	}
}
void stack::push(const string& _CMD)
{
	temp = new node;
	if (temp == NULL)
	{
		cout << "\nERROR : stack > push > temp receives NULL value\n";
		return;
	}
	temp->cmd = _CMD;
	temp->next = top;
	top = temp;
}