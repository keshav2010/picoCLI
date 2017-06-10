#pragma once
#include "command.h"
using namespace std;
class Cmd_io : public Command{
public:
	//overriding Command Class Methods
	int check_cmd(const string& _CMD);
	//overriding Command Class Methods
	void execute_cmd();
	//void execute_cmd(const string& _CMD);
};