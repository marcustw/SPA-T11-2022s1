#include <vector>
#include <string>

#include "Lexer.h"

/* Lexer object would take in a program, tokenize it and return a list of tokens
*  This list of tokens would then be given to the parser
*/
Lexer::Lexer(std::string program) {
	input = program;
	length = program.length();
	index = 0;
}

int Lexer::getIndex() {
	return index;
}

void Lexer::setIndex(int newIndex) {
	index = newIndex;
}

// moves index past all white spaces until the next character or end of source
// return: number of white spaces
int Lexer::next() {
	int ans = 0;
	while (index < length && isspace(input[index])) {
		index++;
		ans++;
	}
	return ans;
}

bool Lexer::reachedEnd() {
	next();
	return index >= length;
}

std::string Lexer::getName() {
	next();
	// initialise an empty string
	std::string name = "";

	if (isdigit(input[index])) return "";

	// if not end of source and char is alnum, add to return string
	while (index < length && isalnum(input[index])) {
		name += input[index];
		index++;
	}

	return name;
}

std::string Lexer::getOperator() {
	next();
	std::string symbols = "";

	if (!isalnum(input[index]) && !isdigit(input[index])) {
		symbols += input[index];
		index++;
	}

	if (!isspace(input[index]) && !isalnum(input[index]) &&
		!isdigit(input[index]) && input[index] != '(' && input[index] != ')') {
		symbols += input[index];
		index++;
	}

	return symbols;
}

std::string Lexer::getInteger() {
	next();
	std::string integer = "";

	// if not end of source and char is alnum, add to return string
	while (index < length && isdigit(input[index])) {
		integer += input[index];
		index++;
	}
	if (integer.length() > 1 && integer[0] == '0') throw SyntaxError(SyntaxError::INVALID_INTEGER);

	return integer;
}

bool Lexer::isNextChar(char c) {
	next();
	if (index < length && input[index] == c) {
		index++;
		return true;
	}
	return false;
}

char Lexer::getNextChar() {
	next();
	if (index < length) {
		return input[index++];
	}
	return '\0';
}

std::string Lexer::getNextSymbol() {
	next();
	std::string symbol = "";

	if (!isalnum(input[index]) && !isdigit(input[index])) {
		symbol += input[index];
		index++;
	}

	return symbol;
}

std::string Lexer::lookAhead() {
	next();
	std::string look_ahead = "";

	look_ahead += input[index];
	return look_ahead;
}

std::string Lexer::nextName() {
	next();
	std::string next_name = "";
	int cur = index;
	while (cur < length && !isspace(input[cur])) {
		next_name += input[cur++];
	}
	return next_name;
}
