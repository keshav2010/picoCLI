#include "cmd_do.h"
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include"stack.h"
#include "cmdengine.h" //this may cause problem, perfrom check
using namespace std;
//overriding Command Class Methods
cmdEngine *CMDENGINE;
int Cmd_do::check_cmd(const string& _CMD)
{
	stack Stack;
	istringstream sin(_CMD);
	string word;
	int readSUBCMD = 0, readUI = 0;
	while (sin >> word)
	{
		if (word == "do" && Stack.isEmpty() && !readUI)
		{
			if (pattern[1] == 0)
			{
				pattern[0] = 1;
				MAJOR = word;
			}
			else
			{
				isValid = 0;
				break;
			}
		}
		//SUBMAJOR not present, [ condition handles it
		else if (word == "[" && !readUI)
		{
			if (Stack.isEmpty())
			{
				pattern[1] = 1;//SUBMAJOR handle
				if (pattern[2] == 0 && pattern[0] == 1 && pattern[1] == 1 && sumPattern(3, 5) == 0)
				{
					pattern[2] = 1;
					readSUBCMD = 1;
				}
			}
			else //stack is filled, we need to accept this "[" as SUBCMD 
			{
				SUBCMD += word + " ";
			}
			Stack.push(word);
		}
		else if (word == "]" && !readUI)
		{
			if (!Stack.isEmpty())
			{
				Stack.pop();
				if (Stack.isEmpty())
				{
					if (sumPattern(0, 2) == 3 && sumPattern(3, 5) == 0)
					{
						pattern[3] = 1;
						readSUBCMD = 0;
					}
				}
				else//stack not empty so we need to accept "]" into SUBCMD
				{
					SUBCMD += word + " ";
				}
			}
			else// wrong positions 
			{
				isValid = 0;
				break;
			}
		}
		else if (word == "<")
		{
			readUI = 1;
			Stack.push(word);
		}
		else if (word == ">")
		{
			if (!Stack.isEmpty())
			{
				Stack.pop();
				if (Stack.isEmpty())
				{
					if (sumPattern(0, 3) == 4 && pattern[4] == 0 && pattern[5] == 0)
					{
						pattern[5] = 1;
						pattern[4] = 1;
						readUI = false;
					}
				}
			}
			else
			{
				isValid = 0;
				break;
			}
		}
		else if (readSUBCMD == 1 && readUI == 0)
		{
			SUBCMD += word + " ";
		}
		else if (readUI == 1)
			USERINPUT += word;
	}//end of loop

	if (isValid&&sumPattern(0, 5) == 6)
	{
		CMDENGINE = new cmdEngine;
		CMDENGINE->process(SUBCMD); //trims
		if (CMDENGINE->check(SUBCMD,0))//checks for Validity and does not Executes(toExecute set to 0/false)
		{
			if (CMDENGINE != NULL)
			{
				delete CMDENGINE;
				CMDENGINE = NULL;
			}
			return 1;
		}
		else
		{
			if (CMDENGINE != NULL)
			{
				delete CMDENGINE;
				CMDENGINE = NULL;
			}
			return 0;
		}
	}
	else
	{
		//reset
		MAJOR.clear();
		SUBMAJOR.clear();
		SUBCMD.clear();
		USERINPUT.clear();
		return 0;
	}
}
void Cmd_do::execute_cmd() 
{ 
	int isTrigger = 0;//false
	int time = atoi(USERINPUT.c_str()); //extracts time in second
	do
	{
		_sleep(1000);//1 sec
		time--;
		if (time == 0)
		{
			//trigger subcmd
			isTrigger = 1;
		}
	} while (time > 0);
	if (isTrigger)
	{
		if (CMDENGINE != NULL)
			delete CMDENGINE;
		CMDENGINE = new cmdEngine;
		
		CMDENGINE->check(SUBCMD); //TODO : modify check() fxn , add 1 more param to skip check

		delete CMDENGINE;
		CMDENGINE = NULL;
	}
}