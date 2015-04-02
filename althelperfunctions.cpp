#include <iostream>
#include <string>

using namespace std;

struct token {
	string type;
	string content;
};


static vector<token> scanner(string & scanned){
	vector<string> compiledStrings;
	vector<token> compiledTokens;
	while (scanned != "") {

		token stuff;
		if (scanned.find(' ') != -1) {
			int spacemarker = scanned.find(' ');
			string sender = scanned.substr(0, spacemarker);

			compiledStrings.push_back(sender);
			scanned.erase(0, spacemarker);

		}
		else {
			compiledStrings.push_back(scanned);
			scanned.erase(0);
		}
	}
	for (int i = 0; i < compiledStrings.size() ; i++) {
		//string
		if (compiledStrings[i].find('\"') == 0) {
			stuff.content = compiledStrings[i].substr(1, compiledStrings[i].find('\"', 1) - 1 );
			stuff.type = "string";

			compiledTokens.push_back(stuff);
			continue;
		}
		//keyword
		if (compiledStrings[i] == "defprompt" || compiledStrings[i] == "cd" || compiledStrings[i] == "listprocs" || 
			compiledStrings[i] == "bye" || compiledStrings[i] == "run" || compiledStrings[i] == "assignto" || compiledStrings[i] == "<bg>") {
			stuff.content = compiledStrings[i];
			stuff.type = "keyword";
			
			compiledTokens.push_back(stuff);
			continue;
		}

		//variable
		if (compiledStrings[i].find('$') == 0 || compiledStrings[i+1] == '=')
		{
			if (compiledStrings[i].find('$') == 0) {
				stuff.content = compiledStrings[i].substr(1);
				stuff.type = "variable";
				compiledTokens.push_back(stuff);
				continue;
			}
			else {
				stuff.content = compiledStrings[i];
				stuff.type = "variable";
				compiledTokens.push_back(stuff);
				continue;
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

