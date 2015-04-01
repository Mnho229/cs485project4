#include <iostream>
#include <string>
#include <map>
#include "helperfunctions.cpp"

using namespace std;

int main() {
	string input;


}

void parser(string inputline) {
	vector<token> tokenList;

	while(inputLine != "") {
		int spacemarker = inputline.find(" \t");
		string sender = inputline.substr(0, spacemarker);
		token reply = scanner(sender);

		tokenList.push_back();

		inputLine.erase(0, spacemarker);
	}

	//syntax
}