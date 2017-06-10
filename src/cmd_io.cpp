#include "cmd_io.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include "stack.h"

using namespace std;
//handles Input (write) and Output (read) operations 
//CMD_IO constructs : read/write/q(MAJOR) | file (SUBMAJOR) | filename.txt (SUBCMD) | file-data (USERINPUT)

int Cmd_io::check_cmd(const string& _CMD)
{
	stack Stack;
	istringstream sin(_CMD);
	string word;
	int readSUBCMD = 0, readUI = 0;
	
	while (sin >> word)
	{
		//MAJOR 
		if ((word == "read" || word == "write" || word == "-q")&&!readUI && Stack.isEmpty())
		{
			if (word == "read")
			{
				pattern[4] = 1;
				pattern[5] = 1;
			}
			else if (word == "-q")
			{
				cout << "word is -q " << MAJOR.size() << "\n";
				if (MAJOR.size() == 0)//-q is a MAJOR parameter passed by USER
				{
					MAJOR = "-q";
					return 1;
				}else
				{
					return 0;//return 0 (invalid) , -q is not treated as MAJOR command
				}
			}
			if (pattern[1] == 0)
			{
				pattern[0] = 1;
				MAJOR = word;//Capital Major is inherited from command abstract class
			}
			else {
				isValid = 0;
				break;
			}
			
		}
		//SUBMAJOR
		else if (word == "file" && !readUI && Stack.isEmpty())
		{
			if (pattern[0] == 1)
			{
				if ((MAJOR == "write" && sumPattern(1, 5) == 0) || (MAJOR == "read" && sumPattern(1, 3) == 0))
				{
					SUBMAJOR = word;
					pattern[1] = 1;
				}
			}
			else
			{
				isValid = 0;
				break;
			}
		}
		else if (word == "[" && !readUI)
		{
			if (Stack.isEmpty())
			{

				if ( (pattern[2] == 0 && pattern[0] == 1 && pattern[1] == 1 && sumPattern(3, 5) == 0 && MAJOR=="write" ) || (pattern[0] == 1 && pattern[1] == 1 && pattern[2] == 0 && pattern[3] == 0&&MAJOR=="read") )
				{
					pattern[2] = 1;
					readSUBCMD = 1;
				}
				else
				{
					isValid = 0;
					break;
				}
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
					if ((sumPattern(0, 2) == 3 && sumPattern(3, 5) == 0 && MAJOR=="write") ||(sumPattern(0, 2) == 3 && pattern[3] == 0 && MAJOR == "read") )
					{
						pattern[3] = 1;
						readSUBCMD = 0;
					}
				}
			}
			else
			{
				isValid = 0;
				break;
			}
		}
		else if (word == "<")
		{
			if (MAJOR == "write")
			{
				readUI =1;
				Stack.push(word);
			}
			else if (MAJOR == "read")
			{
				isValid = 0;//not valid
				break;//break loop
			}
		}
		else if (word == ">")
		{
			if (MAJOR == "read")
			{
				isValid = 0;
				break;
			}
			if (!Stack.isEmpty())
			{
				Stack.pop();
				if (Stack.isEmpty())
				{
					if (sumPattern(0, 3) == 4 && sumPattern(4, 5) == 0)
					{
						pattern[5] = 1;
						pattern[4] = 1;
						readUI = 0;
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
			SUBCMD += word;
		}
		else if (readUI == 1)
		{
			USERINPUT += word;
		}
		
	}//end of while loop
	//Extracted Command Constructs : MAJOR,SUBMAJOR,SUBCMD,USERINPUT
	//Extracted isValid , validity check
	//Extracted Pattern[6] data 
	if (isValid == 1 && sumPattern(0, 5) == 6) //is completely valid
	{
		return 1;
	}
	MAJOR.clear();
	SUBMAJOR.clear();
	SUBCMD.clear();
	USERINPUT.clear();
	return 0;
}
void Cmd_io::execute_cmd() {
	
	if (MAJOR == "-q")
	{
		exit(0);
	}
	//data extracted : for read/write operations 
	string word;
	string fname;
	fstream file;
	string content;
	char IO = MAJOR.at(0);//extract 'w' from write or 'r' from read
	fname = SUBCMD;//subcmd stores filename
	content = USERINPUT;
	//----------------------------------
	//execution starts
	if (IO == 'r') {
		file.open(fname.c_str(), ios::in);
		string word;
		while (getline(file, word)) {
			cout << word << "\n";
		}
		file.close();
	}
	else if (IO == 'w') {
		file.open(fname.c_str(), ios::out | ios::app);
		file << content;
		file << endl;
		file.close();
	}
}