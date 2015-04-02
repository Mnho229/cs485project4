#include <iostream>
#include <string>

using namespace std;

struct token {
	string type;
	string content;
};


static token scanner(string & scanned){
	while (scanned != "") {

		token stuff;

		int spacemarker = scanned.find(' ');
		string sender = scanned.substr(0, spacemarker);

		if (scanned.find(' ') == 0) {
			scanned.erase(0, 1);
			stuff.type = "takeout";
			stuff.content = "takeout";
			return stuff;
		}

		//string
		if (scanned.find('\"') == 0) {
			stuff.content = scanned.substr(1, scanned.find('\"', 1) - 1 );
			stuff.type = "string";

			scanned.erase(0, spacemarker);
			return stuff;
		}

		if (sender == "defprompt" || sender == "cd" || sender == "listprocs" || 
			sender == "bye" || sender == "run" || sender == "assignto" || sender == "<bg>") {
			stuff.content = sender;
			stuff.type = "keyword";
			scanned.erase(0, spacemarker);
			return stuff;
		}

		//variable
		if (scanned.find('$') == 0 || scanned.substr(scanned.find_first_not_of(' ', sender.length()), 1) == "=")
		{
			if (scanned.find('$') == 0) {
				stuff.content = sender.substr(1);
				stuff.type = "variable";
				scanned.erase(0, spacemarker);
				return stuff;
			}
			else {
				stuff.content = sender;
				stuff.type = "variable";
				scanned.erase(0, spacemarker);
				return stuff;
			}
		}

		//metacharacter
		if (scanned.find('#')== 0 ){
			stuff.type = "metachar";
			stuff.content = "#";
			scanned.erase(0,spacemarker);
			return stuff;
		}

		if(scanned.find('=')==0){
			stuff.content = "=";
			stuff.type = "metachar";
			scanned.erase(0,spacemarker);
			return stuff;
		}
		cout << endl << "terminate?";
		stuff.type = "word";
		stuff.content = sender;
		scanned.erase(0, spacemarker);
		return stuff;

		//keyword
		/*
		string keywords[7] = {"defprompt", "cd", "listprocs", "bye", "run", "assignto", "<bg>"};
		for (int i = 0; i < 8; i++) {
			if (sender == keywords[i]) {
				cout << endl << "Sender: " << sender;
				stuff.content = keywords[i];
				stuff.type = "keyword";
				scanned.erase(0, spacemarker);
				return stuff;
			}
		}
		*/
	}

}

