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

