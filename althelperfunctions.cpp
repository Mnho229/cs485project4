#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct token {
	string type;
	string content;
	string usage;
};


inline vector<token> scanner(string scanned) {
	vector<string> compiledStrings;
	vector<token> compiledTokens;
	token stuff;
	while (!scanned.empty()) {
		signed int checker = scanned.find(' ');
		if (checker != -1) {
			int spacemarker = scanned.find(" ");

			if (scanned.find('\"') == 0) {

				int quotemarker = scanned.find('\"', 1);
				int altspacemarker = scanned.find(' ', quotemarker);
				if (altspacemarker != -1) {
					compiledStrings.push_back( scanned.substr(0, altspacemarker) );
					scanned.erase(0, altspacemarker + 1);
					continue;
				}
				else {
					compiledStrings.push_back(scanned);
					scanned.erase(0, scanned.length());
					break;
				}

			}

			string sender = scanned.substr(0, spacemarker);

			compiledStrings.push_back(sender);
			scanned.erase(0, spacemarker + 1);

		}
		else {
			compiledStrings.push_back(scanned);
			scanned.erase(0, scanned.length());
			break;
		}
	}

	compiledStrings.push_back(" ");

	for (size_t i = 0; i < compiledStrings.size() ; i++) {
		if (compiledStrings[i] == " ") {
			compiledStrings.pop_back();
			break;
		}
		//string
		if (compiledStrings[i].find('\"') == 0) {
			stuff.content = compiledStrings[i].substr(1, compiledStrings[i].find('\"', 1) - 1);
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
		if ( compiledStrings[i].find("$") == 0)
		{
			stuff.content = compiledStrings[i];
			stuff.type = "variable";
			compiledTokens.push_back(stuff);
			continue;
		}
		if (i == 0 && compiledStrings[i+1] == "=" && compiledStrings[i] != "#") {
				stuff.content = compiledStrings[i];
				stuff.type = "variable";
				compiledTokens.push_back(stuff);
				continue;
			}

		// statement for metachar '#'
		if (compiledStrings[i] == "#" ){

			stuff.type = "metachar";
			stuff.content = "#";
			compiledTokens.push_back(stuff);
			continue;
		}

		// statement for metachar '='
		if(compiledStrings[i] == "="){

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

