#pragma once

#ifndef MODIFIESVISITOR_H
#define MODIFIESVISITOR_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Visitor.h"
#include "../AST/StmtNode.h"
#include "../../PKB/PKBStorageAPI.h"


class ModifiesVisitor : public Visitor {
public:
	explicit ModifiesVisitor(PKBStorageAPI pkbStorageApi);
	virtual ~ModifiesVisitor();

	void visitProcedureNode(int stmtIndex, int lastStmt, std::string procedureName) override;
	void visitCallNode(int stmtIndex, std::string procName, std::string callerProcName) override;
	void visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes) override;
	void visitIfNode(int stmtIndex,
		int lastStmt,
		std::vector<StmtNode*> ifContainer,
		std::vector<StmtNode*> thenContainer) override;
	void visitReadNode(int stmtIndex, std::string varName) override;
	void visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode) override;
	void visitExpressionNode(ExpressionNode* self) override;

private:
	PKBStorageAPI pkbStorageApi;
	std::unordered_map<int, std::unordered_set<std::string>> varExprMapping;
	std::unordered_map<std::string, std::unordered_set<int>> allCallNodes;
	std::unordered_map<std::string, std::unordered_map<int, std::unordered_set<std::string>>> procAllVarsMapping;
};

#endif
