#pragma once

#include <string>
#include <vector>
#include "../../Common/Types.h"
#include "../AST/StmtNode.h"
#include "../AST/TNode.h"

#ifndef VISITOR_H
#define VISITOR_H

class StmtNode;
class TNode;

/*
Abstract Visitor Superclass
*/
class Visitor {
public:
    Visitor();

    virtual void visitProgrammeNode() {}
    virtual void visitProcedureNode(int stmtIndex, int lastStmt, std::string procedureName) {}
    virtual void visitStmtLstNode(std::vector<StmtNode*> stmtNodes) {}
    virtual void visitReadNode(int stmtIndex, std::string varName) {}
    virtual void visitPrintNode(int stmtIndex, std::string varName) {}
    virtual void visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode) {}
    virtual void visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes) {}
    virtual void visitIfNode(int stmtIndex,
        int lastStmt,
        std::vector<StmtNode*> ifContainer,
        std::vector<StmtNode*> thenContainer) {}
    virtual void visitCallNode(int stmtIndex, std::string procName, std::string callerProcName) {}
    virtual void visitExpressionNode(ExpressionNode* self) {}
};

#endif
