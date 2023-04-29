#include <string>
#include <vector>

#include "TNode.h"
#include "ProcedureNode.h"
#include "StmtLstNode.h"
#include "../Visitors/Visitor.h"

ProcedureNode::ProcedureNode(std::string proc, int stmtIdx) : TNode() {
	procedureName = proc;
    stmtIndex = stmtIdx;
}

ProcedureNode::~ProcedureNode() {
    delete stmtLstNode;
    stmtLstNode = nullptr;
}

void ProcedureNode::addStmtLst(StmtLstNode* stmtLst) {
	stmtLstNode = stmtLst;
}

void ProcedureNode::addLastStmt(int stmtIdx) {
    lastStmt = stmtIdx;
}

void ProcedureNode::accept(Visitor* visitor) {
    stmtLstNode->accept(visitor);
    visitor->visitProcedureNode(this->stmtIndex, this->lastStmt, this->procedureName);
}

int ProcedureNode::getStmtIndex() {
    return stmtIndex;
}
int ProcedureNode::getLastStmt() {
    return lastStmt;
}
StmtLstNode* ProcedureNode::getStmtLstNode() {
    return stmtLstNode;
}
std::string ProcedureNode::getProcedureName() {
    return procedureName;
}
