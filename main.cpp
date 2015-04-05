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
void organizer(vector<token>Tokens, bool flag);
map<string, string> variables;
vector<string> processList;

string ToString(size_t sz) {
	stringstream ss;
	ss << sz;
	return ss.str();
}

int main(int argc, char *argv[]) {
	variables["PATH"] = "/bin:/usr/bin";
	variables["ShowTokens"] = "0";
	variables["prompt"] = "sish >";

	string input;
	
	while(input != "bye"){
		cout << endl << variables["prompt"];
		getline(cin,input);
		parser(input);
	}


}

void parser(string inputLine) {
	bool tokenDisplay = false;

	vector<token> tokenList = scanner(inputLine);

	for (size_t i = 1; i < tokenList.size() ; i++) {
		
		if ((tokenList[i].content).find('$') == 0 && tokenList[i].type == "variable") {

			map<string, string>::iterator it;

			string temp = (tokenList[i].content).substr(1, (tokenList[i].content).length());
			
			for (it = variables.begin(); it != variables.end(); it++) {
				if (it->first == temp) {
					tokenList[i].content = it->second;
					tokenList[i].type = "word";
				}
			}
		}
	}

	if (variables["ShowTokens"] == "1") {
		tokenDisplay = true;
	}
	else {
		tokenDisplay = false;
	}
	//syntax

	//built in commands
	if (tokenList[0].content == "#") {
		for (size_t i = 0; i < tokenList.size() ; i++) {
			tokenList[i].usage = "comment";
		}
		organizer(tokenList, tokenDisplay);
		return;
	}

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

		if ((tokenList[0].content).find("$") == 0) {
			string temp = (tokenList[0].content).substr(1, (tokenList[0].content).length());
			variables[temp] = tokenList[2].content;
		}
		else {
			variables[tokenList[0].content] = tokenList[2].content;
		}

		return;
	}

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

			if(tokenList[1].type == "word"){
				tokenList[0].usage = "change directory";
				tokenList[1].usage = "anyText";


				chdir((tokenList[1].content).c_str());
				return;
			}

			else{
				cout << "please enter word for cd command." << endl;
				return;
			}
		}
	}

	if (tokenList[0].content == "listprocs") {
		
		tokenList[0].usage = "listprocs";
		organizer(tokenList, tokenDisplay);

		if (tokenList.size() > 1) {
			cout << "listprocs is meant to be run by itself. No arguments.";
			return;
		}

		int status;
		pid_t pid = waitpid(-1, &status, WNOHANG);
		if (pid > 0) {
			processList.pop_back();
		}
		for (size_t i = 0; i < processList.size(); i++) {
			cout << endl << i << ". " << processList[i];
		}
	}
	
	if (tokenList[0].content == "bye") {
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
		program_center(tokenList);
	}

}

void program_center(vector<token> cmdline) {

	if (cmdline[0].content == "run") {
		
		if (cmdline[ cmdline.size() - 1 ].content == "<bg>") {

			char *args[cmdline.size()-1];

			for (size_t i = 1; i < cmdline.size() - 1 ; i++) {

			 	char * temp =const_cast<char *>((cmdline[i].content).c_str());
			 	args[i-1] = temp;
			 	cout << endl << args[i-1];
			 }
			 args[cmdline.size() - 2] = 0;

			 string concat1 = cmdline[1].content;

			 processList.push_back(concat1);
			 int pid_ps = fork();

			 if (pid_ps > 0) {

			 }
			 else {
			 	execvp(args[0], args);
			 }
		}
		else {
		
			char *args[cmdline.size()];
			 	
			 for (size_t i = 1; i < cmdline.size() ; i++) {

			 	char * temp =const_cast<char *>((cmdline[i].content).c_str());
			 	args[i - 1] = temp;

			 }
			 	
			 args[cmdline.size() - 1] = 0;

			 int pid_ps = fork();

			 if (pid_ps > 0) {
			 	wait(0);
			 }
			 else {
			 	execvp(args[0], args);
			 }
		}



	}

	if (cmdline[0].content == "assignto") {

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
			 	int fd = open("temp.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
			 	dup2(fd, 1);
			 	close(fd);
			 	execvp(args[0], args);
			 }
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

void organizer(vector<token>Tokens, bool flag){
	if (flag == true) {
		size_t tokenum = 0;
		size_t typeSize = 0;
		string bigType;
		size_t contentSize = 0;
		string bigContent;

		for (size_t i = 0; i < Tokens.size(); i++) {
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


		while(tokenum != Tokens.size()){
			string currentType = "Token Type = " + Tokens[tokenum].type;
			string currentContent = "Token = " + Tokens[tokenum].content;
			while(currentType.length() < maxType.length() + 5 || currentContent.length() < maxContent.length() ) {

				if (currentType.length() < maxType.length() + 5) {
					currentType = currentType + " ";
				}
				if (currentContent.length() < maxContent.length()){
					currentContent = currentContent + " ";
				}
			}
			cout << endl;
			cout << left << currentType ;
			cout << right<< currentContent ;
			cout << setw(15) << "Usage = " << Tokens[tokenum].usage << endl;
			tokenum++;
		}
		cout << endl;
	}
	return;
}


