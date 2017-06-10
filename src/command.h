#pragma once
#include<string>
#include<iostream>
//an abstract class that must be inherited in public-mode for command related action

//the derived class must inherit it in public-mode, pattern[6] is then treated as 
// an internal member that is supposed to be VISIBLE ONLY TO MEMBERS of cmd_<major> Class.
//Command general type is : MAJOR MINOR OTHER 
//name of the class that inherits from Command must be as follow : cmd_<MAJOR> , example cmd_do , cmd_io (for read/write)
class Command {
protected:
	int isValid;//0(false) / 1(true)
	int pattern[6] = { 0,0,0,0,0,0 }; //initially set to false , all 0s need to be 1s for true
	std::string MAJOR, SUBMAJOR, SUBCMD, USERINPUT;
	int sumPattern(int beg, int end)
	{
		int sum = 0;
		if (beg >= 0 && beg <= 5 && end <= 5 && end >= beg&&end >= 0)
		{
			for (int i = beg; i <= end; i++)
			{
				sum += pattern[i];
			}
		}
		else std::cout << "error\n";
		return sum;
	}
	Command() {
		//init Validity
		isValid = 1;//consider true by default
		//----x-----
	}

public:
	virtual int check_cmd(const std::string&) = 0; //this may work upon pattern matching+keyword checking+extracting 
	virtual void execute_cmd() = 0;//this is intended to perform execution of code
};