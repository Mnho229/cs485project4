Group Members:
	ALcibiades I Holmes
	Michael Ho

FILES:
	helperfunctions.h
	althelperfunctions.cpp
	main.cpp
	makefile
Description
	Project 4's purpose is to create a shell that reads basic shell lines and does supporting commands based on them.

	Scanner:
		located in althelperfunctions.cpp, uses a struct token with three string variables to store the type, content and usage for the inputted commands.
		While the input is read and seperated by white space, The scanner seperates the string into vectors by push_back with each element. Once it is pushed onto a vector, it is erased from the string so the scanner can read the next token. This continues until the string is empty.

		The scanner then looks at the vector created through a nested for loop and differentiates each string with their respective types.

		This then returns the vector of tokens

	Parsing:
		Located in main.
		
