#include <string>
#include <vector>
#include <iterator>

#include "../Visitors/Visitor.h"
#include "StmtNode.h"
#include "StmtLstNode.h"
#include "ExpressionNode.h"

StmtNode::StmtNode(int index) : TNode() {
    stmtIndex = index;
}

int StmtNode::getStmtIndex() {
    return stmtIndex;
}

ReadNode::ReadNode(int stmtIndex, ExpressionNode* variable) : StmtNode(stmtIndex) {
    var = variable;
}

ReadNode::~ReadNode() {
    delete var;
    var = nullptr;
}

void ReadNode::accept(Visitor* visitor) {
    ExpressionNode* var = this->var;
    visitor->visitReadNode(this->getStmtIndex(), var->getValue());
}

ExpressionNode* ReadNode::getVar() {
    return var;
}

PrintNode::PrintNode(int stmtIndex, ExpressionNode* variable) : StmtNode(stmtIndex) {
    var = variable;
}

PrintNode::~PrintNode() {
    delete var;
    var = nullptr;
}

void PrintNode::accept(Visitor* visitor) {
    ExpressionNode* var = this->var;
    visitor->visitPrintNode(this->getStmtIndex(), var->getValue());
}

ExpressionNode* PrintNode::getVar() {
    return var;
}

CallNode::CallNode(int stmtIndex, std::string procName, std::string caller) : StmtNode(stmtIndex) {
    procedureName = procName;
    callerProcName = caller;
}

void CallNode::accept(Visitor* visitor) {
    visitor->visitCallNode(this->getStmtIndex(), this->procedureName, this->callerProcName);
}

AssignNode::AssignNode(int stmtIndex) : StmtNode(stmtIndex) {}

AssignNode::~AssignNode() {
    delete expression;
    expression = nullptr;

    delete var;
    var = nullptr;
}

void AssignNode::addExpression(ExpressionNode* expr) {
    expression = expr;
}

void AssignNode::addVariable(ExpressionNode* variable) {
    var = variable;
}

void AssignNode::accept(Visitor* visitor) {
    var->accept(visitor);
    expression->accept(visitor);

    ExpressionNode* var = this->var;

    visitor->visitAssignNode(this->getStmtIndex(), var->getValue(), this->expression);
}

ExpressionNode* AssignNode::getVariable() {
    return var;
}

ExpressionNode* AssignNode::getExpression() {
    return expression;
}

WhileNode::WhileNode(int stmtIndex) : StmtNode(stmtIndex) {}

WhileNode::~WhileNode() {
    delete stmtLst;
    stmtLst = nullptr;

    delete condExpr;
    condExpr = nullptr;
}


void WhileNode::setStmtLst(StmtLstNode* stmtLstNode) {
    stmtLst = stmtLstNode;
}


void WhileNode::setCondExp(ExpressionNode* conditionalExp) {
    condExpr = conditionalExp;
}

void WhileNode::accept(Visitor* visitor) {
    condExpr->accept(visitor);
    stmtLst->accept(visitor);

    StmtLstNode* stmtLst = this->stmtLst;

    visitor->visitWhileNode(this->getStmtIndex(), this->lastStmt, stmtLst->getStmtNodes());
}

void WhileNode::setLastStmtIndex(int last) {
    lastStmt = last;
}

int WhileNode::getLastStmt() {
    return lastStmt;
}

StmtLstNode* WhileNode::getStmtLst() {
    return stmtLst;
}
ExpressionNode* WhileNode::getCondExpr() {
    return condExpr;
}

IfNode::IfNode(int stmtIndex) : StmtNode(stmtIndex) {}

IfNode::~IfNode() {
    delete ifStmtLst;
    ifStmtLst = nullptr;

    delete elseStmtLst;
    elseStmtLst = nullptr;

    delete condExpr;
    condExpr = nullptr;
}


void IfNode::setIfStmtLst(StmtLstNode* stmtLst) {
    ifStmtLst = stmtLst;
}

void IfNode::setElseStmtLst(StmtLstNode* stmtLst) {
    elseStmtLst = stmtLst;
}

void IfNode::setCondExp(ExpressionNode* conditionalExp) {
    condExpr = conditionalExp;
}

void IfNode::accept(Visitor* visitor) {
    condExpr->accept(visitor);
    ifStmtLst->accept(visitor);
    elseStmtLst->accept(visitor);

    visitor->visitIfNode(this->getStmtIndex(),
        this->lastStmt, this->ifStmtLst->getStmtNodes(),
        this->elseStmtLst->getStmtNodes());
}

void IfNode::setLastStmtIndex(int last) {
    lastStmt = last;
}

int IfNode::getLastStmt() {
    return lastStmt;
}

StmtLstNode* IfNode::getIfStmtLst() {
    return ifStmtLst;
}

StmtLstNode* IfNode::getElseStmtLst() {
    return elseStmtLst;
}

ExpressionNode* IfNode::getCondExpr() {
    return condExpr;
}
