#include "cmdengine.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include "cmd_io.h" //for read/write and -q command
#include "cmd_do.h" // for do commands
using namespace std;

//Constructor
cmdEngine::cmdEngine() {
	cout << "Activating Engine\n";
}
//Destructor
cmdEngine::~cmdEngine() {
	cout << "DeActivating Engine\n";
}

//Starting Point of CMDEngine Class
void cmdEngine::start_cmdEngine() {
	cout << "Command Line Engine Active...\n\n"; 
	/*
	*/
	while (1) {
		cout << ">>>>"; 
		getline(cin, cmd); //get input
		process(cmd); //process 
		cout << "proccessed : " << cmd << "\n";
		int x = check(cmd);
		if (x == 0)
			cout << "\n check failed for "<<cmd<<"\n";
	}
}
void cmdEngine::process(string& _CMD) {
	//removing whitespaces, trims the command line

	for (long int i = 0; i < _CMD.size(); i++) {
		if (i == 0) {
			if (_CMD.at(i) == ' ') {
				_CMD.erase(0, 1);//removes the 0-th element
				i = -1;
			}
		}
		else if (i <= _CMD.size() - 2) {
			if (_CMD.at(i) == ' '&& _CMD.at(i + 1) == ' ') {
				_CMD.erase(_CMD.begin() + i);
				i--;
			}
		}
		else if (i == _CMD.size() - 1) {
			if (_CMD.at(i) == ' ') {
				_CMD.pop_back();
			}
		}
	}//for loop [0 to _CMD.size()-1 ]
	cout <<"processing done :"<< _CMD <<"<"<<endl;
}
int cmdEngine::check(const string& _CMD,int toExecute)//toExecute set true by default
{
	istringstream sin(_CMD);
	string major_command;
	int isCorrect = 0;
	sin >> major_command;//read first major command , note that submajor can also be read 
	cout << "Major is : " << major_command << "\n";
	if (major_command == "read" || major_command == "write"||major_command=="-q") 
	{
		//cout << "detected major_command\n";
		Cmd_io *cmd_io=new Cmd_io;
		//cout << "initialized command_io engine\n";
		if (cmd_io->check_cmd(_CMD)) 
		{
			isCorrect = 1;
			if(toExecute) 
				cmd_io->execute_cmd();//calls the Execute method of cmdEngine
		}
		else {
			if (cmd_io != NULL)
				delete cmd_io;
			isCorrect = 0;
			cout << "\n ERROR : error in command ("<<major_command<<")\n ";
			return 0;//check failed
		}
		cout << "deleting cmd-io\n";
		if (cmd_io != NULL)
		{	
			delete cmd_io;
			cout << "deleted\n";
		}
		return isCorrect; 
	}
	
	else if (major_command == "do" || major_command == "shutdown")
	{	
		if(major_command=="shutdown")
		{	isCorrect=1;
			if(toExecute){
				cout << "Shutdown Code Here";
			}
			return isCorrect;
		}
		cout << "initializing cmd_do\n";
		Cmd_do *cmd_do=new Cmd_do;
		cout << "calling check_cmd(_CMD) , _CMD is :" << _CMD << ":\n";
		if(cmd_do->check_cmd(_CMD))
		{	
			if(toExecute)
				cmd_do->execute_cmd();
			isCorrect=1;
		}
		else
		{	
			isCorrect=0;
			cout<<"\n ERROR : error in command do\n";
		}
		if(cmd_do!=NULL)
			delete cmd_do;
		return isCorrect;
		
	}
	else {
		cout << "\n " << major_command << " is an invalid command \n";
		return 0;
	}
}