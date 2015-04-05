#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdlib.h>
#include "helperfunctions.h"
#include <sstream>
#include <fstream>

using namespace std;

void parser(string inputLine);
void program_center(vector<token> cmdline);
void organizer(vector<token>Tokens, bool flag); //various occurences of this will be common through procedures for ShowTokens.
map<string, string> variables; //where the variables are stored
vector<string> processList;

string ToString(size_t sz) { //Used for parameter numbers in run/assignto ShowTokens procedure
	stringstream ss;
	ss << sz;
	return ss.str();
}
//Executes the main procedure in a while loop, shows prompt, and takes user input with getline.
int main(int argc, char *argv[]) {
	//preset variables for map
	variables["PATH"] = "/bin:/usr/bin";
	variables["ShowTokens"] = "0";
	variables["prompt"] = "sish >";

	string input;
	
	while(input != "bye" && input != "control-D"){
		cout << endl << variables["prompt"];
		getline(cin,input);
		parser(input);
	}


}
//The operation center for parsing a command and executing it.  Takes user input from main().
void parser(string inputLine) {
	bool tokenDisplay = false;

	vector<token> tokenList = scanner(inputLine);  //Scanner is called for vector of tokens

	//checks for any variables with "$" at a non-zero index and replaces them with stored definition from global map.
	for (size_t i = 1; i < tokenList.size() ; i++) { 
		
		if ((tokenList[i].content).find('$') == 0 && tokenList[i].type == "variable") {

			map<string, string>::iterator it; //iterator for traversing through map

			string temp = (tokenList[i].content).substr(1, (tokenList[i].content).length());
			
			for (it = variables.begin(); it != variables.end(); it++) {
				if (it->first == temp) {
					tokenList[i].content = it->second;
					tokenList[i].type = "word";
				}
			}
		}
	}

	if (variables["ShowTokens"] == "1") { //Flag checker for ShowTokens
		tokenDisplay = true;
	}
	else {
		tokenDisplay = false;
	}

	//built in commands
	if (tokenList[0].content == "#") { //comments
		for (size_t i = 0; i < tokenList.size() ; i++) {
			tokenList[i].usage = "comment";
		}
		organizer(tokenList, tokenDisplay);
		return;
	}
	//variables with argument checking and redefintion.
	if (tokenList[0].type == "variable" && tokenList[1].content == "=") {
		if (tokenList.size() > 3) {
			cout << endl << "Error: too many arguments";
			return;
		}
		if (tokenList.size() == 2) {
			cout << endl << "Error: Nothing to set the variable equal to:";
			return;
		}

		tokenList[0].usage = "variable";
		tokenList[1].usage = "assignment";
		tokenList[2].usage = "variableDef";
		organizer(tokenList, tokenDisplay);

		//sets new variables within map
		if ((tokenList[0].content).find("$") == 0) { //if variable has zero index and dollar sign
			string temp = (tokenList[0].content).substr(1, (tokenList[0].content).length());
			variables[temp] = tokenList[2].content;
		}
		else {
			variables[tokenList[0].content] = tokenList[2].content; 
		}

		return;
	}
	//redefines new prompt if executed with argument-checking
	if (tokenList[0].content == "defprompt") {
		if(tokenList.size() > 2){
			cout << endl << "Error too many arguments......";
			return;
		}
		if (tokenList.size() == 1) {
			cout << endl << "Error: Need a string prompt to accompany defprompt";
			return;
		}
		else{
			tokenList[0].usage = "anyText";
			tokenList[1].usage = "prompt";

			organizer(tokenList, tokenDisplay);

			variables["prompt"] = tokenList[1].content;
			return;
		}	
	}
	//changes directory with execution of this procedure with argument-checking
	if (tokenList[0].content == "cd") {
		if(tokenList.size()==1){

			cout << "Error. Please enter a path for cd command."<< endl;
			return;
		}

		if(tokenList.size() > 2){
			cout << "Error. To many inputs for command. Please try again." << endl;
			return;
		}
		else{

			if (tokenList[1].type == "word"){
				tokenList[0].usage = "change directory";
				tokenList[1].usage = "anyText";

				organizer(tokenList, tokenDisplay);
				chdir((tokenList[1].content).c_str());
				return;
			}

			else{
				cout << "please enter word for cd command." << endl;
				return;
			}
		}
	}
	//list currently on-going processes
	if (tokenList[0].content == "listprocs") {
		
		tokenList[0].usage = "listprocs";
		organizer(tokenList, tokenDisplay);

		if (tokenList.size() > 1) {
			cout << "listprocs is meant to be run by itself. No arguments.";
			return;
		}

		int status;
		pid_t pid = waitpid(-1, &status, WNOHANG); //checks for processes.
		if (pid > 0) { //if process is terminated, process is popped from vector.
			processList.pop_back();
		}
		for (size_t i = 0; i < processList.size(); i++) { //printing of processes
			cout << endl << i << ". " << processList[i];
		}
	}
	
	if (tokenList[0].content == "bye" || tokenList[0].content == "control-D") { //Exiting the shell
		exit(0);
	}

	//Program-control commands
	if (tokenList[0].content == "run" || tokenList[0].content == "assignto") {

		if (tokenList[0].content == "run") {
			tokenList[0].usage = "run";
			tokenList[1].usage = "cmd";

			if (tokenList.size() > 2) {
				for (size_t i = 2; i < tokenList.size() ; i++) {
					tokenList[i].usage = "Parameter " + ToString(i - 1);
				}
			}
		}
		if (tokenList[0].content == "assignto") {
			tokenList[0].usage = "assignto";
			tokenList[1].usage = "variable";
			tokenList[2].usage = "cmd";
			if (tokenList.size() > 3) {
				for (size_t i = 3; i < tokenList.size() ; i++) {
					tokenList[i].usage = "Parameter " + ToString(i - 2);
				}
			}
		}
		organizer(tokenList, tokenDisplay);
		program_center(tokenList); //separate procedure used to handle run and assignto and takes vector of tokens as an argument.
	}

}

void program_center(vector<token> cmdline) {

	if (cmdline[0].content == "run") { //run
		
		if (cmdline[ cmdline.size() - 1 ].content == "<bg>") { //with <bg> present

			char *args[cmdline.size()-1]; //new char * array to be used in execvp

			for (size_t i = 1; i < cmdline.size() - 1 ; i++) { //translate all token content to char *

			 	char * temp =const_cast<char *>((cmdline[i].content).c_str()); //no const trouble
			 	args[i-1] = temp;
			 	
			 }
			 args[cmdline.size() - 2] = 0; //adds a zero at the end for use in execvp

			 string concat1 = cmdline[1].content; //this statement and the next adds process to processlist.
			 processList.push_back(concat1);

			 int pid_ps = fork(); //new child process

			 if (pid_ps > 0) { //parent immediately goes to next command

			 }
			 else { //child process activates command while automatically searching $PATH
			 	execvp(args[0], args);
			 }
		}
		else { //without <bg>
		
			char *args[cmdline.size()];
			 	
			 for (size_t i = 1; i < cmdline.size() ; i++) {

			 	char * temp =const_cast<char *>((cmdline[i].content).c_str());
			 	args[i - 1] = temp;

			 }
			 	
			 args[cmdline.size() - 1] = 0;

			 int pid_ps = fork();

			 if (pid_ps > 0) {
			 	wait(0); //without <bg>, parent waits for child to get done before continuing.
			 }
			 else {
			 	execvp(args[0], args);
			 }
		}



	}

	if (cmdline[0].content == "assignto") { //assignto
		//almost the same procedure as run
		char *args[cmdline.size()];
			 	
			 for (size_t i = 2; i < cmdline.size() ; i++) {

			 	char * temp =const_cast<char *>((cmdline[i].content).c_str());
			 	args[i - 2] = temp;
			 }
			 	
			 args[cmdline.size() - 2] = 0;
			 int pid_ps = fork();

			 if (pid_ps > 0) {

			 	wait(0);
			 	
			 }
			 else {
			 	//before executing, creates a temp file used to redirect output of command to the file.
			 	int fd = open("temp.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR); //read/write intent, creation of file if not present || allows read/write permissions
			 	dup2(fd, 1); //allows redirection via stdout
			 	close(fd); //closes
			 	execvp(args[0], args); //execution with output redirected to file
			 }
		// the following procedure reads from the file and stores it in a string, which is then used
		// as the defintion for the new variable in the global map
		fstream tempFile;
		string temp;
		string definition;
		tempFile.open("temp.txt");

		while(getline(tempFile, temp)) {
			definition = definition + temp + "\n";
		}
		variables[cmdline[1].content] = definition;
		tempFile.close();
	}
}
//The ShowTokens Algorithm, which only executes if flag is true
void organizer(vector<token>Tokens, bool flag){
	if (flag == true) {
		cout << endl;
		size_t tokenum = 0; //token index
		size_t typeSize = 0; //helps keep track of size of string.  Same for its content brother.
		string bigType; //Biggest possible string,  Same for its content brother.
		size_t contentSize = 0;
		string bigContent;

		for (size_t i = 0; i < Tokens.size(); i++) { //finds largest type/content within vector of tokens
			if (typeSize < (Tokens[i].type).length()) {
				typeSize = (Tokens[i].type).length();
				bigType = Tokens[i].type;
			}
			if (contentSize < (Tokens[i].content).length()) {
				contentSize = (Tokens[i].content).length();
				bigContent = Tokens[i].content;
			}
		}

		string maxType = "Token Type = " + bigType;
		string maxContent = "Token = " + bigContent;

		// loops through the vector of tokens and sets the current index of tokens
		while(tokenum != Tokens.size()){
			string currentType = "Token Type = " + Tokens[tokenum].type;
			string currentContent = "Token = " + Tokens[tokenum].content;
			//if the current index of tokens is less than maxType/maxContent, then add whitespace at the end until lengths matches up
			while(currentType.length() < maxType.length() + 5 || currentContent.length() < maxContent.length() ) {

				if (currentType.length() < maxType.length() + 5) {
					currentType = currentType + " ";
				}
				if (currentContent.length() < maxContent.length()){
					currentContent = currentContent + " ";
				}
			}
			//prints the strings
			cout << left << currentType ;
			cout << right<< currentContent ;
			cout << setw(15) << "Usage = " << Tokens[tokenum].usage << endl;
			tokenum++;
		}
		cout << endl;
	}
	return;
}


