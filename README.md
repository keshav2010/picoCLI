# picoCLI
picoCLI is a tiny program with Command line interface written in C++ (for Windows platform only) 

1. quickly create/append to text-files and make short-notes/reminders 
2. quickly read from text-files
3. invoke a command(pre-defined as well as system-level commands such as shutdown) within specified time period by initiating a countdown timer

**Command Construct**
picoCLI breaks a command into 4 parts ( * in front means this part is required)
1. MAJOR* : The MAJOR part specifies the major action that command will initiate, for example "read" or "write" in case of input-output 
2. SUBMAJOR : SUBMAJOR is an optional part, that means a user can constructs his/her own command without need to mention SUBMAJOR command
3. SUBCMD* : SUBCMD stands for sub-command, this serve as a parameter to MAJOR command, every command that picoCLI contains, need a parameter to act upon
4. USERINPUT : in case a command needs user-input, user can write code for specifying USERINPUT properties 

**command.h : Abstract Class**
command.h is an abstract class every command (predefined or defined by programmer) must inherit publically
it specifies the properties of a command such as 
1. isValid 
2. Pattern[6]
3. MAJOR, SUBMAJOR, SUBCMD, USERINPUT

and some Functions 
1. int sumPattern(int beg, int end)
2. int check_cmd(const std::string&)//needs to be override by programmer
3. void execute_cmd() //needs to be override by programmer

_check_cmd function should check a command syntax, if its valid, return 1 else return 0_
#
_execute_cmd function should be responsible for execution of a command_
#
**# #Existing Commands**
1. read file [ filename.txt ]
2. write file [ filename.txt ] < userinput here >
3. do [ (any command here) ] < seconds here >
4. shutdown
5. -q 

#

**# #Examples**

1. write file [ myfile.txt ] < this goes in file >
2. do [ write file [ myfile.txt ] < this goes in file too > ] < 2 > 
3. do [ do [ write file [ myfile.txt ] < third line > ] < 2 > ] < 3 > 
4. read file [ myfile.txt ] 
5. do [ shutdown ] < 50 > 
#
**execution will be like ** 
myfile.txt will be created and first line will be written ("this goes in file") 
next, a do-trigger alarm is set, after 2 second, it will re-open file and write "this goes in file too" as second line
next a do-trigger alarm is set, after 3 second, it calls another do-alarm, which now execute for further 2 seconds (total : 5 second pause) and finally "third line" will be written to file

read file command will show content of file
and lastly, do statement will execute shutdown command after 50 seconds, Shutting down the operating system (windows)
