#include <iostream>
#include <string>
#include <vector>

using namespace std;

//main item used in almost all procedures
struct token {
	string type;
	string content;
	string usage;
};

//function that takes a string and scans it down into a vector of tokens.
inline vector<token> scanner(string scanned) {
	vector<string> compiledStrings;
	vector<token> compiledTokens;
	token stuff;

	//scans string down to a vector of strings separated by whitespace.
	while (!scanned.empty()) {
		signed int checker = scanned.find(' ');
		if (checker != -1) {
			int spacemarker = scanned.find(" ");

			//special case for strings, especially with spaces present between quotes
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
			scanned.erase(0, spacemarker + 1); //scanned item is erased so that work can immediately begin on next item.

		}
		else {
			compiledStrings.push_back(scanned);
			scanned.erase(0, scanned.length());
			break;
		}
	}
	//procedure to scan vector of strings to vector of tokens begin.
	compiledStrings.push_back(" "); //allows support of the variable look-ahead trick.

	for (size_t i = 0; i < compiledStrings.size() ; i++) { //This procedure is only here for look-ahead.
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
		//variable variant utilizing the look-ahead method
		if (i == 0 && compiledStrings[i+1] == "=" && compiledStrings[i] != "#") {
				stuff.content = compiledStrings[i];
				stuff.type = "variable";
				compiledTokens.push_back(stuff);
				continue;
			}

		//metachar '#'
		if (compiledStrings[i] == "#" ){

			stuff.type = "metachar";
			stuff.content = "#";
			compiledTokens.push_back(stuff);
			continue;
		}

		//metachar '='
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

