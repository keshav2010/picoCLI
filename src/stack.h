#pragma once
#include<string>
using namespace std;
class node
{
public:
	string cmd;
	node *next;
	node();
};
class stack
{
protected:
	const int MAX_SIZE=4;
public:
	node *top, *temp;
	stack();
	void push(const string&);
	string read(int); //index <= MAX_SIZE-1
	void clear();
	void pop();
	int isEmpty();
};