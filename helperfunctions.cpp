#include <iostream>
#include <string>

using namespace std;

struct token {
	string type;
	string content;
};


static token scanner(string & scanned){
	token stuff;

	int spacemarker = scanned.find(" \t\0");
	string sender = scanned.substr(0, spacemarker);

	//string
	if (scanned.find("\"") == 0) {
		stuff.content = scanned.substr(1, scanned.find("\"", 1) - 1 );
		stuff.type = "string";

		scanned.erase(0, spacemarker);
		return stuff;
	}

	//keyword
	string keywords[7] = {"defprompt", "cd", "listprocs", "bye", "run", "assignto", "<bg>"};
	for (int i = 0; i < 8; i++) {
		if (sender == keywords[i]) {

			stuff.content = sender;
			stuff.type = "keyword";
			scanned.erase(0, spacemarker);
		}
	}

	//variable
	if (scanned.find("$") == 0 || spaceMarker + 1 == scanned.find("=") ) {

	}
}

