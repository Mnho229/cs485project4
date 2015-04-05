CS485 Project 4

Group Members:
	Alcibiades I Holmes
	Michael Ho

FILES:
	helperfunctions.h
	helperfunctions.cpp
	main.cpp
	makefile

Description
	Project 4's purpose is to create a shell that reads basic shell lines and does supported commands.

	cmd line:
		Although short, the main function prints the prompt and then calls the parser, the main source of operations in a while loop.  Some variables within the global map variable are pre-declared.

	Scanner:
		The scanner is called within the parser to handle a string that represents the command written by the user.	

		In althelperfunctions.cpp, there lies a struct token with three string variables to store the type, content and usage for the inputted commands and the scanner proedure.
		While the input is read and separated by white space (with a special case for strings), The scanner separates each individual item and feeds them into a string vector.  The scanner erases every item it is done feeding to the vector of strings until the scanned string is empty.

		The scanner then looks at the vector of strings.  It determines the type of each item via presence of certain characters, looking ahead in the vector, and checking for equality.  With each item read and its type & content determined, it gets pushed into the vector of tokens.

		After every item has been scanned through, the vector of tokens is pushed back to the parser.

	Parsing:
		The parser parses through the vector of tokens from the scanner through a massive conditional pipeline.  As we go down the parser, I'll explain the algorithms on the way.

		Replacing $variable
			This algorithm utilizes finding a variable with a "$" in an index other than zero.  If such a variable exists in the vector, it searches through the map with an iterator and if present, switches out the variable with the stored definition and a changed type to 'word'.

		ShowTokens Check via flags.

		If statement for Comments.

		Variables
			Assigns or reassigns variables in the map after argument-checking if statements.

		Defprompt command check.

		cd command check.

		Listprocs
			Utilizes waitpid for any detection of processes terminated and pops them in the vector holding them.

		Bye exit check

		Program-control commands
			Any run or assignto commands are redirected to another function called program_center which takes a vector of tokens as an argument.  After determining if its run or assignto, a char* array is created, filled with the representatives of tokens, and ends with a 0 to be used in a forked execvp procedure, while checking if <bg> is used.

			If assignto is used, then output is redirected to a file via dup2 and open, which is then read into the new variable definition.

		Organizer (ShowTokens)
			If the ShowTokens flag is true, the algorithm present in this function will print the Type, Content, and the Usage in an easy-to-read format.  The length of the biggest Type and Content present within the vector of tokens are used to help make the output statements more readable

	Limitations of sish:
		Listprocs may not work as intended.


		
