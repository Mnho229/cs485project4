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
	
	while(input != "bye"){
		cout << "sish$ <";
		getline(cin,input);
		parser(input);
	}


}

void parser(string inputLine) {
	vector<token> tokenList;

	while(inputLine != "") {
		token reply = scanner(inputLine);

		if (reply.type == "takeout") {
			continue;
		}

		tokenList.push_back(reply);

	}
	for (int i = 0; i < tokenList.size() ; i++) {

		cout << endl << tokenList[i].type << endl << tokenList[i].content << endl;

	}
	//syntax
}