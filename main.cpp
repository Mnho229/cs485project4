#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "helperfunctions.h"

using namespace std;

void parser(string inputLine);

int main() {
	string input;
	
	parser("My turban is dirty.");

}

void parser(string inputLine) {
	vector<token> tokenList;

	while(inputLine != "") {
		token reply = scanner(inputLine);

		tokenList.push_back(reply);

	}

	cout << endl << tokenList[0].type << endl << tokenList[0].content << endl;
	//syntax
}