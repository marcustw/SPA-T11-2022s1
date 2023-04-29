#include <typeinfo>

#include "CFG.h"
#include "../AST/ProcedureNode.h"
#include "../AST/StmtNode.h"



CFG::CFG() {
    cfgMap = new std::unordered_map<int, std::unordered_set<int>>();
    predecessors = std::vector<int>{ 0 };
}

std::unordered_map<int, std::unordered_set<int>>* CFG::generateCFGMap(ProgrammeNode* ASTRoot) {
    processProgrammeNode(ASTRoot);
    return cfgMap;
}

void CFG::processProgrammeNode(ProgrammeNode* ASTRoot) {
    std::vector<ProcedureNode*> procedures = ASTRoot->getProcedureNodes();
    for (ProcedureNode* procedure : procedures) {
        predecessors.clear();
        predecessors.push_back(0);
        processProcedureNode(procedure);
    }
}

void CFG::processProcedureNode(ProcedureNode* procedureNode) {
    StmtLstNode* stmtLst = procedureNode->getStmtLstNode();
    processStmtLst(stmtLst);
}

void CFG::processStmtLst(StmtLstNode* stmtLstNode) {
    std::vector<StmtNode*> stmts = stmtLstNode->getStmtNodes();
    for (StmtNode* stmt : stmts) {
        if (typeid(*stmt) == typeid(WhileNode)) {
            processWhileNode(stmt);
        } else if (typeid(*stmt) == typeid(IfNode)) {
            processIfNode(stmt);
        } else {
            processStmt(stmt);
        }
    }
}

void CFG::processStmt(StmtNode* stmt) {
    for (int stmtIndex : predecessors) {
        (*cfgMap)[stmtIndex].insert(stmt->getStmtIndex());
    }
    predecessors.clear();
    predecessors.push_back(stmt->getStmtIndex());
}

void CFG::processWhileNode(StmtNode* stmt) {
    for (int stmtIndex : predecessors) {
        (*cfgMap)[stmtIndex].insert(stmt->getStmtIndex());
    }
    predecessors.clear();
    predecessors.push_back(stmt->getStmtIndex());

    int whileIndex = static_cast<int>(stmt->getStmtIndex());

    WhileNode* whileNode = static_cast<WhileNode*>(stmt);
    StmtLstNode* stmtLst = whileNode->getStmtLst();
    processStmtLst(stmtLst);
    for (int stmtIndex : predecessors) {
        (*cfgMap)[stmtIndex].insert(stmt->getStmtIndex());
    }
    predecessors.clear();
    predecessors.push_back(stmt->getStmtIndex());
}

void CFG::processIfNode(StmtNode* stmt) {
    for (int stmtIndex : predecessors) {
        (*cfgMap)[stmtIndex].insert(stmt->getStmtIndex());
    }
    predecessors.clear();
    predecessors.push_back(stmt->getStmtIndex());

    int ifIndex = static_cast<int>(stmt->getStmtIndex());

    IfNode* ifNode = static_cast<IfNode*>(stmt);
    StmtLstNode* ifStmtLst = ifNode->getIfStmtLst();
    processStmtLst(ifStmtLst);

    std::vector<int> ifStmtLstPredecessors = std::vector<int>(predecessors);
    predecessors.clear();
    predecessors.push_back(ifIndex);

    StmtLstNode* elseStmtLst = ifNode->getElseStmtLst();
    processStmtLst(elseStmtLst);

    predecessors.insert(predecessors.begin(), ifStmtLstPredecessors.begin(), ifStmtLstPredecessors.end());
}

