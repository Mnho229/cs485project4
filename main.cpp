#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unistd.h>
#include "helperfunctions.h"

using namespace std;

void parser(string inputLine);
void program_center(vector<token> cmdline);
map<string, string> variables;


int main() {
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

	for (int i = 1; i < tokenList.size() ; i++) {
		cout << endl << tokenList[i].content;
		if ((tokenList[i].content).find('$') == 0 && tokenList[i].type == "variable") {

			map<string, string>::iterator it;

			string temp = (tokenList[i].content).substr(1, (tokenList[i].content).length());
			
			for (it = variables.begin(); it != variables.end(); it++) {
				if (it->first == temp) {
					cout << endl << it->second;
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
		for (int i = 0; i < tokenList.size() ; i++) {
			tokenList[i].usage = "comment";
		}

		return;
	}

	if (tokenList[0].type == "variable" && tokenList[1].content == "=") {
		tokenList[0].usage = "variable";
		tokenList[1].usage = "assignment";
		tokenList[2].usage = "variableDef";

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
		tokenList[0].usage = "anyText";
		tokenList[1].usage = "prompt";

		variables["prompt"] = tokenList[1].content;
	}

	if (tokenList[0].content == "cd") {
		if(tokenList[1].type == "word"){
			chdir((tokenList[1].content).c_str());
		}
	}
	if (tokenList[0].content == "bye") {
		exit(0);
	}

	//Program-control commands
	if (tokenList[0].content == "run" || tokenList[0].content == "assignto") {

			program_center(tokenList);
	}
}

void program_center(vector<token> cmdline) {

	if (cmdline[0].content == "run") {
		
		if (cmdline[ cmdline.size() - 1 ].content == "<bg>") {

			char *args[cmdline.size()-1];

			for (int i = 1; i < cmdline.size() - 1 ; i++) {

			 	char * temp =const_cast<char *>((cmdline[i].content).c_str());
			 	args[i-1] = temp;
			 	cout << endl << args[i-1];
			 }
			 args[cmdline.size() - 2] = 0;

			 int pid_ps = fork();

			 if (pid_ps > 0) {

			 }
			 else {
			 	execvp(args[0], args);
			 }
		}
		else {
		
			char *args[cmdline.size()];
			 	
			 for (int i = 1; i < cmdline.size() ; i++) {

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
			 	
			 for (int i = 2; i < cmdline.size() ; i++) {

			 	char * temp =const_cast<char *>((cmdline[i].content).c_str());
			 	args[i - 2] = temp;

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


