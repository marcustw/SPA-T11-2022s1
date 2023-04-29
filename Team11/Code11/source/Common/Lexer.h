#pragma once

#include <string>
#include <vector>

#include "./SPAException.h"

class Lexer {
public:
	explicit Lexer(std::string program);
	int getIndex();
	void setIndex(int newIndex);

	std::string getName();
	std::string getInteger();
	std::string getOperator();
	char getNextChar();
	bool isNextChar(char c);
	bool reachedEnd();
	std::string getNextSymbol();
	std::string lookAhead();
	std::string nextName();

private:
	std::string input;
	int index;
	int length;
	int next();
};
