#pragma once

#ifndef PATTERNVISITOR_H
#define PATTERNVISITOR_H

#include "Visitor.h"
#include "../AST/StmtNode.h"
#include "../AST/ExpressionNode.h"
#include "../../PKB/PKBStorageAPI.h"

class PatternVisitor : public Visitor {
	PKBStorageAPI pkbStorageApi;
public:
	explicit PatternVisitor(PKBStorageAPI pkbStorageApi);
	virtual ~PatternVisitor();

	void visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode) override;
	void visitExpressionNode(ExpressionNode* self) override;
};

#endif
