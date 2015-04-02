#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct token {
	string type;
	string content;
};


static vector<token> scanner(string scanned) {
	vector<string> compiledStrings;
	vector<token> compiledTokens;
	token stuff;
	while (!scanned.empty()) {
		if (scanned.find(' ') != -1) {
			int spacemarker = scanned.find(" ");
			string sender = scanned.substr(0, spacemarker);

			compiledStrings.push_back(sender);
			scanned.erase(0, spacemarker + 1);

		}
		else {
			cout << endl << scanned;
			compiledStrings.push_back(scanned);
			scanned.erase(0, scanned.length());
			break;
		}
	}
	for (int i = 0; i < compiledStrings.size() ; i++) {
			cout << endl << "in stringvector: " << compiledStrings[i];
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
		else if (compiledStrings[i] == "defprompt" || compiledStrings[i] == "cd" || compiledStrings[i] == "listprocs" || 
			compiledStrings[i] == "bye" || compiledStrings[i] == "run" || compiledStrings[i] == "assignto" || compiledStrings[i] == "<bg>") {
			stuff.content = compiledStrings[i];
			stuff.type = "keyword";
			
			compiledTokens.push_back(stuff);
			continue;
		}

		//variable
		else if ( compiledStrings[i].find("$") == 0)
		{
			stuff.content = compiledStrings[i].substr(1);
			stuff.type = "variable";
			compiledTokens.push_back(stuff);
			continue;
		}
		else if (compiledStrings[i+1] != NULL) {
				stuff.content = compiledStrings[i];
				stuff.type = "variable";
				compiledTokens.push_back(stuff);
				continue;
			}

		// statement for metachar '#'
		else if (compiledStrings[i] == "#" ){

			stuff.type = "metachar";
			stuff.content = "#";
			compiledTokens.push_back(stuff);
			continue;
		}

		// statement for metachar '='
		else if(compiledStrings[i] == "="){

			stuff.content = "=";
			stuff.type = "metachar";
			compiledTokens.push_back(stuff);
			continue;
		}

		else {
			stuff.type = "word";
			stuff.content = compiledStrings[i];
			compiledTokens.push_back(stuff);
		}

	}

	return compiledTokens;

}

