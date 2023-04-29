#pragma once

#include <exception>
#include <string>

class SPAException : public std::exception {
	std::string errorMsg;
public:
	// Constructor
	explicit SPAException(std::string errorMsg);
	// std::exception method
	const char* what() const override;
};

class SyntaxError : public SPAException {
public:
	explicit SyntaxError(std::string errorMsg);

	static const char PROCEDURE_KEYWORD[];
	static const char PROCEDURE_OPENING_CURLY[];
	static const char PROCEDURE_CLOSING_CURLY[];
	static const char PROCEDURE_NAME[];
	static const char EMPTY_PROCEDURE[];

	static const char INVALID_STMT[];
	static const char NO_SEMICOLON[];


	static const char WHILE_OPENING_BRACKET[];
	static const char WHILE_CLOSING_BRACKET[];
	static const char WHILE_OPENING_CURLY[];
	static const char WHILE_CLOSING_CURLY[];

	static const char IF_OPENING_BRACKET[];
	static const char IF_CLOSING_BRACKET[];
	static const char IF_OPENING_CURLY[];
	static const char IF_CLOSING_CURLY[];
	static const char THEN_KEYWORD[];
	static const char ELSE_KEYWORD[];

	static const char COND_CLOSING_BRACKET[];
	static const char COND_OPENING_BRACKET[];

	static const char INVALID_INTEGER[];
	static const char INVALID_EXPRESSION[];

	static const char SYNTAX_ERROR[];
};

class SPSemanticError : public SPAException {
public:
	explicit SPSemanticError(std::string errorMsg);

	static const char CYCLIC_PROCEDURE_CALL[];
	static const char DUPLICATE_PROCEDURE_NAME[];
	static const char UNDECLARED_PROCEDURE[];
};

class QPSException : public SPAException {
public:
	explicit QPSException(std::string errorMsg);
	static const char QPS_SYNTAX_ERROR[];
	static const char QPS_SEMANTIC_ERROR[];

	// For Future Extensions
	static const char NO_IMPLEMENTATION[];
};

class PKBException : public SPAException {
public:
	explicit PKBException(std::string errorMsg);
	static const char PKB_INVALID_STMT_TYPE[];
	static const char PKB_INVALID_RELATIONSHIP_TYPE[];
};
