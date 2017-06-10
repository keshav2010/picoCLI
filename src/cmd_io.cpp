#include "cmd_io.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include "stack.h"

using namespace std;
//handles Input (write) and Output (read) operations 
//CMD_IO constructs : read/write/q(MAJOR) | file (SUBMAJOR) | filename.txt (SUBCMD) | file-data (USERINPUT)

int Cmd_io::check_cmd(const string& _CMD)
{
	//cout << "inside Cmd_io\n";
	stack Stack;
	istringstream sin(_CMD);
	string word;
	int readSUBCMD = 0, readUI = 0;
	//cout << "Loop Begins\n";
	while (sin >> word)
	{
		//cout << "Current word :" << word << "\n";
		//MAJOR 
		if ((word == "read" || word == "write" || word == "-q")&&!readUI && Stack.isEmpty())
		{
			//cout << "engine-detected-major\n";
			if (word == "read")
			{
				pattern[4] = 1;
				pattern[5] = 1;
			}
			else if (word == "-q")
			{
				if (MAJOR.size() == 0)//-q is a MAJOR parameter passed by USER
					return 1;
				else
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
			if (pattern[0] == 1)// && sumPattern(1, 5) == 0)
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
			//cout << "spotted [\n";
			if (Stack.isEmpty())
			{
				//debug
			//	cout << "Stack is Empty\n";
			//	cout << "pattern when [ is read is \n";
			//	for (int i = 0; i <= 5; i++)
				//	cout << pattern[i] << " ";
			//	cout << "\n";
				//debug-end
				if ( (pattern[2] == 0 && pattern[0] == 1 && pattern[1] == 1 && sumPattern(3, 5) == 0 && MAJOR=="write" ) || (pattern[0] == 1 && pattern[1] == 1 && pattern[2] == 0 && pattern[3] == 0&&MAJOR=="read") )
				{
				//	cout << "if-condition executes\n";
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
	//cout << "Loop Ends\n";
	//for (int i = 0; i <= 5; i++)
	//	cout << pattern[i] << " ";
	//cout << "\n";
	//cout << isValid<<":isValid\n";
	if (isValid == 1 && sumPattern(0, 5) == 6) //is completely valid
	{
		//cout << "CHECK cmd_Io RETURNING 1 \n";
		return 1;
	}
	//cout << "CHECK cmd_Io returning 0";
	MAJOR.clear();
	SUBMAJOR.clear();
	SUBCMD.clear();
	USERINPUT.clear();
	return 0;
}
void Cmd_io::execute_cmd() {

	string word;
	if (MAJOR == "-q")
		exit(0);
	//data extracted : for read/write operations 
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
/*
//note that pattern[6] is also accessible by these methods
int Cmd_io::check_cmd(const string& _CMD) {
	istringstream sin(_CMD);
	string word;

	int isCheckActive = 1; //used to skip content between < > as its user-defined input and no keyword check req.
						   //check all keywords
	while (sin >> word) {
		if (word == "read" || word == "write" || word == "file" || word == "-q") {
			continue;
		}
		else if (word == "[" || word == "<") {
			isCheckActive = 0;//disable error checking now
		}
		else if (word == "]" || word == ">" || word.at(word.size() - 1) == ']' || word.at(word.size() - 1) == '>') {
			isCheckActive = 1;//enable error checking 
		}
		else if (isCheckActive) { //if word is not keyword and checking process is active
			cout << "\n" << word << " : is a invalid command ! Unable to process request.\n";
			return 0;//false, check failed, show error
		}
	}
	sin.str("");//clearing the previous string data
	sin.clear();//reset error-flags to goodbit / no-error state
	//match pattern 
	//int pattern[6] = { 0,0,0,0,0,0 }; //Major + Minor + "[" + "]" + "<" + ">" 
	//istringstream SIN(_CMD);
	
	word.clear();
	sin.str(_CMD);
	cout << "\n--Pattern Check---\n";
	while (sin >> word) {
		cout << "\ncurrent word : " << word << " checking \n";
		if (word == "read" || word == "write" || word == "-q") {
			if (pattern[1] == 0) {
				pattern[0] = 1;
				if (word == "read") {
					pattern[5] = 1;
					pattern[4] = 1;
				}
				else if (word == "-q") {
					pattern[5] = 1;
					pattern[4] = 1;
					pattern[3] = 1;
					pattern[2] = 1;
					pattern[1] = 1;
					break;
				}
			}
			else break;
		}
		else if (word == "file") {
			if (pattern[0])
				pattern[1] = 1;
			else break;
		}
		else if (word == "[") {
			if (pattern[1])
				pattern[2] = 1;
			else break;
		}
		else if (word == "]" || word.at(word.size() - 1) == ']') {
			if (pattern[2])
				pattern[3] = 1;
			else break;
		}
		else if (word == "<") {
			if (pattern[3])
				pattern[4] = 1;
			else break;
		}

		else if (word == ">" || word.at(word.size() - 1) == '>') {
			if (pattern[4])
				pattern[5] = 1;
			else break;
		}
	}
	//out of break

	for (int i = 0; i < 6; i++)
		cout << pattern[i] << " ";
	cout << "\n";
	int isMatch = 1;

	if (pattern[0] == 0) {
		isMatch = 0;
	}
	else if (pattern[1] + pattern[2] + pattern[3] + pattern[4] + pattern[5] == 0) {
		isMatch = pattern[0];
	}
	else if (!(pattern[0] + pattern[1] + pattern[2] + pattern[3] + pattern[4] + pattern[5] == 6))
		isMatch = 0;

	if (!isMatch)
		cout << "Pattern InCorrect\n";
	return isMatch;
}
void Cmd_io::execute_cmd(const string& _CMD) {
	istringstream sin(_CMD);
	string word;

	//data extracted : for read/write operations 
	string fname;
	fstream file;
	string content;
	char IO = 'w';//default
	//-------------------

	//Flags and Controllers

	int getFileName = 0;
	int getFileContent = 0;

	//----------------------------------
	while (sin >> word) {
		if (getFileName) {
			fname = word;
			getFileName = 0;
			//	process(fname);//processes fname
			cout << "\n [DEBUG] file_name : " << fname << "\n";
		}
		if (getFileContent) {
			if (word != ">")
				content = content + word + " ";
			//process(content);
		}
		if (word == "read" || word == "write")
			IO = word.at(0);
		else if (word == "-q") {
			exit(0);
		}
		else if (word == "[") {
			getFileName = 1;
			continue;
		}
		else if (word == "]")
			getFileName = 0;
		else if (word == "<")
			getFileContent = 1;
		else if (word == ">")
			getFileContent = 0;
	}

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
*/