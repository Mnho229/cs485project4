#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "helperfunctions.h"

using namespace std;

void parser(string inputLine);
void program_center(vector<token> cmdline);
map<string, string> variables;


int main() {
	variables["PATH"] = "/bin:/usr/bin";
	variables["ShowTokens"] = "0";

	string input;
	string currentDirectory;
	
	while(input != "bye"){
		cout << "sish >";
		getline(cin,input);
		parser(input);
	}


}

void parser(string inputLine) {
	vector<token> tokenList = scanner(inputLine);

	if (variables["ShowTokens"] == "1") {

	}
	//syntax

	//built in commands
	if (tokenList[0].type == "variable" && tokenList[1].content == "=") {
		tokenList[0].usage = "variable";
		tokenList[1].usage = "assignment";
		tokenList[2].usage = "variableDef";
	}

	if (tokenList[0].content == "#") {
		for (int i = 0; i < tokenList.size() ; i++) {
			tokenList[i].usage = "comment";
		}
	}

	if (tokenList[0].content == "defprompt") {

	}

	if (tokenList[0].content == "cd") {

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
			
			int pid_ps = fork();
			if (pid_ps == 0) {

				char *args[] = {};
				for (int i = 1; i < cmdline.size() - 1 ; i++) {

					char * temp =const_cast<char *>((cmdline[i].content).c_str());

					args[i] = temp;

				}
				execv(args[0], args);

			}
		}
		else {

			int pid_ps = fork();
			if (pid_ps == 0) {

				char *args[] = {};
				for (int i = 1; i < cmdline.size() ; i++) {

					char * temp =const_cast<char *>((cmdline[i].content).c_str());

					args[i] = temp;

				}
				execv(args[0], args);
				pid_t pid = wait(0);
			}
		}



	}

	if (cmdline[0].content == "assignto") {

	}



}


