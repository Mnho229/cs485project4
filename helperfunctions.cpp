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
	if (scanned.find("$") == 0 || scanned.substr(scanned.find_first_not_of(" \t", sender.length() + 1), 1) == "=" )
	{
		if (scanned.find("$") == 0) {
			stuff.content = sender.substr(1);
			stuff.type = "variable";
			scanned.erase(0, spacemarker);
		}
		else {
			stuff.content = sender;
			stuff.type = "variable";
			scanned.erase(0, spacemarker);
		}
	}

<<<<<<< HEAD

=======
	//metacharacter
	if (scanned.find("#")== 0 ){
		stuff.type = "metachar";
		stuff.content = "#";
		scanned.erase(0,spacemarker);
	}

	if(scanned.find("=")==0){
		stuff.content = "=";
		stuff.type = "metachar";
		scanned.erase(0,spacemarker);
	}
>>>>>>> 0965f9d1fb23f785a6d126994a14ff5a6c6faafd
}

