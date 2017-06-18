#pragma once
#include<string>

class cmdEngine { //command processing engine ;)
private:
	std::string cmd; //the command line string
	//void process(std::string&); //processor : trimming of command line 
	//int check(const std::string&); //check the processed command line for grammer
//	void execute(const std::string&); //execute the command line for action ;) 
public:
	cmdEngine();
	~cmdEngine();
	void start_cmdEngine();
	void process(std::string&); //trimmer
	int check(const std::string&,int toExecute=1);
};