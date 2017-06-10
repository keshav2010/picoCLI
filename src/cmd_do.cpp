#include "cmd_do.h"
#include<sstream>
#include<iostream>
#include "cmdengine.h" //this may cause problem, perfrom check
using namespace std;
//overriding Command Class Methods
int Cmd_do::check_cmd(const string& _CMD) {
	istringstream sin(_CMD);
	string word; // carries a single token

	string sub_cmd = " ";
	string countDown;
	//do [ sub_cmd ] < countDown >

	int isSubCommand = 0;
	int isCheckActive = 1; //used to skip content between < > as its user-defined input and no keyword check req.
						   //check all keywords
	while (sin >> word) {
		if (isSubCommand)
			sub_cmd = sub_cmd + word;
		if (word == "do") {
			continue;
		}
		else if (word == "[" ) {
			isSubCommand = 1;
			isCheckActive = 0;
			continue;
		}
		else if (word == "]" ) {
			isSubCommand = 0;
			isCheckActive = 1;
			continue;
		}
		else if (word == "<")
			isCheckActive = 0;
		else if (word == ">")
			isCheckActive = 1;

		else if (isCheckActive) { //if word is not keyword and checking process is active
			cout << "\n" << word << " : is a invalid command ! Unable to process request.\n";
			return 0;//false, check failed, show error
		}
	}
	//CHECKING SUB_CMD
	cmdEngine *cmdengine = new cmdEngine;
	cout << "\nCall to CmdEngine\n";
	cmdengine->process(sub_cmd); //trims the sub_cmd 
	cout <<"\n SUB COMMAND IS : "<< sub_cmd << "\n";
	delete cmdengine;
	sin.str("");//clearing the previous string data
	sin.clear();//reset error-flags to goodbit / no-error state
	word.clear();
	sin.str(_CMD);
	cout << "\n--Pattern Check---\n";
	while (sin >> word) {
		cout << "\ncurrent word : " << word << " checking \n";
		if (word == "do") {
			if (pattern[1] == 0) {
				pattern[0] = 1;
			}
			else break;
		}
		else if (word == "[") {
			if (pattern[0])
				pattern[1] = 1;
			else break;
		}
		else if (word == "") {
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
//overriding Command Class Methods
void Cmd_do::execute_cmd(const string& _CMD){

}