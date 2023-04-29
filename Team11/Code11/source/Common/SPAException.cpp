#include "SPAException.h"

SPAException::SPAException(std::string errorMsg):
	errorMsg(errorMsg) {}

const char* SPAException::what() const {
	return errorMsg.c_str();
}

// For future extensions
const char QPSException::NO_IMPLEMENTATION[] = "Not Implemented Yet";

SyntaxError::SyntaxError(std::string errorMsg) : SPAException(errorMsg) { }

const char SyntaxError::PROCEDURE_KEYWORD[] = "Procedure keyword: \"procedure\" is missing";
const char SyntaxError::PROCEDURE_OPENING_CURLY[] = "Procedure opening curly bracket is missing";
const char SyntaxError::PROCEDURE_CLOSING_CURLY[] = "Procedure closing curly bracket is missing";
const char SyntaxError::PROCEDURE_NAME[] = "Procedure name is invalid";
const char SyntaxError::EMPTY_PROCEDURE[] = "Procedure does not contain any statements";

const char SyntaxError::INVALID_STMT[] = "Invalid Statement";
const char SyntaxError::NO_SEMICOLON[] = "No semicolon for statement";

const char SyntaxError::WHILE_OPENING_BRACKET[] = "While opening bracket is missing";
const char SyntaxError::WHILE_CLOSING_BRACKET[] = "While closing bracket is missing";
const char SyntaxError::WHILE_OPENING_CURLY[] = "While opening curly bracket is missing";
const char SyntaxError::WHILE_CLOSING_CURLY[] = "While closing curly bracket is missing";

const char SyntaxError::IF_OPENING_BRACKET[] = "If opening bracket is missing";
const char SyntaxError::IF_CLOSING_BRACKET[] = "If closing bracket is missing";
const char SyntaxError::IF_OPENING_CURLY[] = "If opening curly is missing";
const char SyntaxError::IF_CLOSING_CURLY[] = "If closing curly is missing";

const char SyntaxError::THEN_KEYWORD[] = "Then keyword is missing from if statement";
const char SyntaxError::ELSE_KEYWORD[] = "Else keyword is missing from if statement";

const char SyntaxError::COND_CLOSING_BRACKET[] = "Conditional Expression closing bracket is missing";
const char SyntaxError::COND_OPENING_BRACKET[] = "Conditional Expression opening bracket is missing";

const char SyntaxError::INVALID_INTEGER[] = "Invalid Integer";

const char SyntaxError::INVALID_EXPRESSION[] = "Invalid Expression";

const char SyntaxError::SYNTAX_ERROR[] = "Syntax Error";

SPSemanticError::SPSemanticError(std::string errorMsg) : SPAException(errorMsg) { }

const char SPSemanticError::CYCLIC_PROCEDURE_CALL[] = "Cyclical procedure calls found";

const char SPSemanticError::DUPLICATE_PROCEDURE_NAME[] = "Duplicate Procedure names declared";

const char SPSemanticError::UNDECLARED_PROCEDURE[] = "Undeclared procedure called";


QPSException::QPSException(std::string errorMsg) : SPAException(errorMsg) { }

const char QPSException::QPS_SEMANTIC_ERROR[] = "SemanticError";

const char QPSException::QPS_SYNTAX_ERROR[] = "SyntaxError";

PKBException::PKBException(std::string errorMsg) : SPAException(errorMsg) { }

const char PKBException::PKB_INVALID_STMT_TYPE[] = "Invalid Statement type";

const char PKBException::PKB_INVALID_RELATIONSHIP_TYPE[] = "Invalid Relationship type";


