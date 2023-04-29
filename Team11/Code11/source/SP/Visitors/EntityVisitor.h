#pragma once

#ifndef ENTITYVISITOR_H
#define ENTITYVISITOR_H

#include <vector>
#include <string>

#include "Visitor.h"
#include "../AST/ProcedureNode.h"
#include "../AST/StmtNode.h"
#include "../AST/ExpressionNode.h"
#include "../../PKB/PKBStorageAPI.h"

class StmtNode;

class EntityVisitor : public Visitor {
	PKBStorageAPI pkbStorageApi;
public:
	explicit EntityVisitor(PKBStorageAPI pkbStorageApi);
	virtual ~EntityVisitor();

	void visitProcedureNode(int stmtIndex, int lastStmt, std::string procedureName) override;
	void visitReadNode(int stmtIndex, std::string varName) override;
	void visitPrintNode(int stmtIndex, std::string varName) override;
	void visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode) override;
	void visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes) override;
	void visitIfNode(int stmtIndex,
		int lastStmt,
		std::vector<StmtNode*> ifContainer,
		std::vector<StmtNode*> thenContainer) override;
	void visitCallNode(int stmtIndex, std::string procName, std::string callerProcName) override;
	void visitExpressionNode(ExpressionNode* self) override;
};

#endif
