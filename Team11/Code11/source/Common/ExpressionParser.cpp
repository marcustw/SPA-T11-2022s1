#include "ExpressionParser.h"

const std::vector<std::string> EXP_OPER = { "+", "-" };
const std::vector<std::string> TERM_OPER = { "*", "/", "%" };
const std::vector<std::string> LOG_OPER = { "&&", "||" };
const std::vector<std::string> REL_OPER = { "<", "<=", ">", ">=", "!=", "=="};


ExpressionParser::ExpressionParser(Lexer* lexerPtr) {
	lexer = lexerPtr;
}

Lexer* ExpressionParser::getLexer() {
	return lexer;
}

ExpressionNode* ExpressionParser::extractExpressionNode(int stmtIndex) {
	ExpressionNode* leftTerm = extractTermNode(stmtIndex);
	// will either return the original leftTerm or an EXP operator
	return extractRightExpressionNode(leftTerm, stmtIndex);
}

ExpressionNode* ExpressionParser::extractRightExpressionNode(ExpressionNode* leftTerm, int stmtIndex) {
	std::string look_ahead = lexer->lookAhead();
	for (std::string OP : EXP_OPER) {  // for every possible expression
		if (look_ahead == OP) {
			// EXP_OPER found, treat the rest of the expression as another expression with leftTerm as leftChild
			lexer->getNextSymbol();
			ExpressionNode* operation = new ExpressionNode(stmtIndex, look_ahead, ExpressionType::EXP_OPR);
			operation->addLeftChild(leftTerm);
			ExpressionNode* rightTerm = extractTermNode(stmtIndex);
			operation->addRightChild(rightTerm);
			return extractRightExpressionNode(operation, stmtIndex);
		}
	}
	return leftTerm;
}

ExpressionNode* ExpressionParser::extractTermNode(int stmtIndex) {
	ExpressionNode* leftFactor = extractFactorNode(stmtIndex);
	return extractRightTermNode(leftFactor, stmtIndex);
}

ExpressionNode* ExpressionParser::extractRightTermNode(ExpressionNode* leftFactor, int stmtIndex) {
	std::string look_ahead = lexer->lookAhead();
	for (std::string OP : TERM_OPER) {
		if (look_ahead == OP) {  // TERM_OPR found
			ExpressionNode* operation = new ExpressionNode(stmtIndex, lexer->getNextSymbol(),
				ExpressionType::TERM_OPR);
			operation->addLeftChild(leftFactor);
			operation->addRightChild(extractFactorNode(stmtIndex));

			return extractRightTermNode(operation, stmtIndex);
		}
	}
	return leftFactor;
}

ExpressionNode* ExpressionParser::extractFactorNode(int stmtIndex) {
	std::string var = lexer->getName();
	if (!var.empty()) {
		return new ExpressionNode(stmtIndex, var, ExpressionType::VARIABLE);
	}

	std::string integer = lexer->getInteger();
	if (!integer.empty()) {
		return new ExpressionNode(stmtIndex, integer, ExpressionType::CONSTANT);
	}

	std::string symbol = "" + lexer->getNextSymbol();
	if (symbol == "(") {
		ExpressionNode* innerExp = extractExpressionNode(stmtIndex);
		if (lexer->getNextSymbol() != ")") throw SyntaxError(SyntaxError::INVALID_EXPRESSION);
		return innerExp;
	}

	throw SyntaxError(SyntaxError::INVALID_EXPRESSION);
	return new ExpressionNode();
}

ExpressionNode* ExpressionParser::extractCondExpressionNode(int stmtIndex) {
	ExpressionNode* condExp;
	std::string symbol = lexer->getNextSymbol();
	if (symbol == "!") {  // its a not
		condExp = new ExpressionNode(stmtIndex, symbol, ExpressionType::LOGICAL_OPR);
		lexer->getNextSymbol();
		condExp->addLeftChild(extractCondExpressionNode(stmtIndex));
		lexer->getNextSymbol();
		return condExp;
	} else if (symbol == "(") {  // assuming you cant bracket for nth, like ((1 > 2)). expect to see && or ||
		ExpressionNode* left = extractCondExpressionNode(stmtIndex);
		if (lexer->getNextSymbol() != ")") { throw SyntaxError(SyntaxError::COND_CLOSING_BRACKET); }
		std::string logOperator = lexer->getOperator();
		if (std::find(LOG_OPER.begin(), LOG_OPER.end(), logOperator) == LOG_OPER.end()) {
			throw SyntaxError(SyntaxError::INVALID_EXPRESSION);
		}
		condExp = new ExpressionNode(stmtIndex, logOperator, ExpressionType::LOGICAL_OPR);
		condExp->addLeftChild(left);
		if (lexer->getNextSymbol() != "(") { throw SyntaxError(SyntaxError::COND_OPENING_BRACKET); }
		condExp->addRightChild(extractCondExpressionNode(stmtIndex));
		if (lexer->getNextSymbol() != ")") { throw SyntaxError(SyntaxError::COND_CLOSING_BRACKET); }
		return condExp;
	}
	return extractRelExpressionNode(stmtIndex);
}

ExpressionNode* ExpressionParser::extractRelExpressionNode(int stmtIndex) {
	ExpressionNode* left = extractExpressionNode(stmtIndex);

	std::string symbol = lexer->getOperator();
	if (std::find(REL_OPER.begin(), REL_OPER.end(), symbol) == REL_OPER.end()) {
		throw SyntaxError(SyntaxError::INVALID_EXPRESSION);
	}
	ExpressionNode* relExpr = new ExpressionNode( stmtIndex, symbol, ExpressionType::REL_EXPR );
	relExpr->addLeftChild(left);
	ExpressionNode* right = extractExpressionNode(stmtIndex);
	relExpr->addRightChild(right);
	return relExpr;
}

