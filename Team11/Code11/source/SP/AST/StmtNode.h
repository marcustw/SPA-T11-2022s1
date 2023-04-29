#pragma once

#include <string>
#include <vector>
#include "TNode.h"

class Visitor;
class StmtLstNode;
class ExpressionNode;
class ProcedureNode;

class StmtNode : public TNode {
public:
	explicit StmtNode(int stmtIndex);

	int getStmtIndex();

private:
	int stmtIndex;
};


class ReadNode : public StmtNode {
public:
	ReadNode(int stmtIndex, ExpressionNode* var);
	~ReadNode();

	void accept(Visitor* visitor);
	ExpressionNode* getVar();

private:
	ExpressionNode* var;
};

class PrintNode : public StmtNode {
public:
	PrintNode(int stmtIndex, ExpressionNode* var);
	~PrintNode();

	void accept(Visitor* visitor);
	ExpressionNode* getVar();
private:
	ExpressionNode* var;
};

class CallNode : public StmtNode {
public:
	CallNode(int stmtIndex, std::string procedureName, std::string callerProcName);
	void accept(Visitor* visitor);
private:
	std::string procedureName;
	std::string callerProcName;
};

class AssignNode : public StmtNode {
public:
	explicit AssignNode(int stmtIndex);
	~AssignNode();

	void accept(Visitor* visitor);
	void addExpression(ExpressionNode* expression);
	void addVariable(ExpressionNode* var);
	ExpressionNode* getVariable();
	ExpressionNode* getExpression();


private:
	ExpressionNode* expression;
	ExpressionNode* var;
};

class WhileNode : public StmtNode {
public:
	explicit WhileNode(int stmtIndex);
	~WhileNode();

	void accept(Visitor* visitor);
	void setStmtLst(StmtLstNode* stmtLst);
	void setCondExp(ExpressionNode* condExpr);
	void setLastStmtIndex(int lastStmt);
	int getLastStmt();
	StmtLstNode* getStmtLst();
	ExpressionNode* getCondExpr();
private:
	int lastStmt;
	StmtLstNode* stmtLst;
	ExpressionNode* condExpr;
};

class IfNode : public StmtNode {
public:
	explicit IfNode(int stmtIndex);
	~IfNode();

	void setIfStmtLst(StmtLstNode* stmtLst);

	void setElseStmtLst(StmtLstNode* stmtLst);
	void setCondExp(ExpressionNode* condExpr);
	void setLastStmtIndex(int lastStmt);
	void accept(Visitor* visitor);

	int getLastStmt();
	StmtLstNode* getIfStmtLst();
	StmtLstNode* getElseStmtLst();
	ExpressionNode* getCondExpr();
private:
	int lastStmt;
	StmtLstNode* ifStmtLst;
	StmtLstNode* elseStmtLst;
	ExpressionNode* condExpr;
};
