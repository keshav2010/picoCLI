#include "stdafx.h" //if using visualStudio, Pre-Compiled headerfile option is not used. 
using namespace std;
int main()
{	
	cmdEngine *engine = new cmdEngine;
	engine->start_cmdEngine(); //starts the command Line Engine
	delete engine;
	return 0;
}
