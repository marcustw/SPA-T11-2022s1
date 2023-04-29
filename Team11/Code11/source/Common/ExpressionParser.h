#pragma once

#include "../SP/AST/ExpressionNode.h"
#include "../Common/Lexer.h"
#include "../Common/SPAException.h"

#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

class ExpressionParser {
public:
	explicit ExpressionParser(Lexer* lexer);
	Lexer* getLexer();
	ExpressionNode* extractExpressionNode(int stmtIndex);
	ExpressionNode* extractCondExpressionNode(int stmtIndex);


private:
	Lexer* lexer;
	ExpressionNode* extractRightExpressionNode(ExpressionNode* leftTerm, int stmtIndex);
	ExpressionNode* extractTermNode(int stmtIndex);
	ExpressionNode* extractRightTermNode(ExpressionNode* leftFactor, int stmtIndex);
	ExpressionNode* extractFactorNode(int stmtIndex);
	ExpressionNode* extractRelExpressionNode(int stmtIndex);
};

#endif
