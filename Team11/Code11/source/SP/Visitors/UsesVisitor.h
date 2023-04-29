#pragma once

#ifndef USESVISITOR_H
#define USESVISITOR_H

#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <iterator>

#include "Visitor.h"
#include "../AST/StmtNode.h"
#include "../../PKB/PKBStorageAPI.h"


class UsesVisitor : public Visitor {
public:
	explicit UsesVisitor(PKBStorageAPI pkbStorageApi);
	virtual ~UsesVisitor();
	PKBStorageAPI pkbStorageApi;

	void visitProcedureNode(int stmtIndex, int lastStmt, std::string procName) override;
	void visitCallNode(int stmtIndex, std::string procName, std::string callerProcName) override;
	void visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes) override;
	void visitIfNode(int stmtIndex,
		int lastStmt,
		std::vector<StmtNode*> ifContainer,
		std::vector<StmtNode*> thenContainer) override;
	void visitPrintNode(int stmtIndex, std::string varName) override;
	void visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode) override;
	void visitExpressionNode(ExpressionNode* self) override;

private:
	std::unordered_map<int, std::unordered_set<std::string>> varExprMapping =
		std::unordered_map<int, std::unordered_set<std::string>>();
	std::unordered_map<std::string, std::unordered_set<int>> allCallNodes =
		std::unordered_map<std::string, std::unordered_set<int>>();
	std::unordered_map<std::string, std::unordered_map<int, std::unordered_set<std::string>>> procAllVarsMapping =
		std::unordered_map<std::string, std::unordered_map<int, std::unordered_set<std::string>>>();
};

#endif
