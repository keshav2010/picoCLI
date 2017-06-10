//
#include "stdafx.h" 
using namespace std;
//int ID_valid();
int main()
{	
	/*
	if (!ID_valid()) {
		cout << "Invalid !";
		cin.get();
		return 1;
	}
	*/
	cmdEngine *engine = new cmdEngine;
	engine->start_cmdEngine(); //starts the command Line Engine
	delete engine;
	return 0;
}
/*
int ID_valid() {
	string pass;
	int attempts = 2;
	cout << "Hello Keshav Sharma \n";
	do {
		cout << "Enter Security Key : ";
		getline(cin, pass);
		if (pass == "password") { 
			cout << "Valid Key\n";
			cin.get();
			break;
		}
		else {
			cout << "\n Invalid ! Attempts left : " << attempts-1 << endl;
			if (attempts - 1 == 0)
				return 0;
		}
	} while (attempts--);

	return 1;
}
*/
