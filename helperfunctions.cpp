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

	if (scanned.find("\"") == 0) {
		stuff.content = scanned.substr(1, scanned.find("\"", 1) - 1 );
		stuff.type = "string";

		scanned.erase(0, spacemarker);
		return stuff;
	}
}

