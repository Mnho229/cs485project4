#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "helperfunctions.h"

using namespace std;

void parser(string inputLine);
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

	for (int i = 0; i < tokenList.size() ; i++) {

		cout << endl << tokenList[i].type << endl << tokenList[i].content;

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

	}
}

void program_center() {

	




}


