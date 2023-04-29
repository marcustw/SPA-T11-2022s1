#include <vector>
#include <iterator>
#include <typeinfo>

#include "StmtLstNode.h"
#include "StmtNode.h"
#include "../Visitors/Visitor.h"


StmtLstNode::StmtLstNode() : TNode() {}

StmtLstNode::~StmtLstNode() {
    for (StmtNode*& stmtNode : stmtNodes) {
        delete stmtNode;
        stmtNode = nullptr;
    }
}

void StmtLstNode::addStmt(StmtNode* stmt) {
    stmtNodes.push_back(stmt);
}

int StmtLstNode::getStmtIndex() {
    return stmtIndex;
}

std::vector<StmtNode*> StmtLstNode::getStmtNodes() {
    return stmtNodes;
}


void StmtLstNode::accept(Visitor* visitor) {
    std::vector<StmtNode*>::iterator iter = stmtNodes.begin();
    for (iter; iter != stmtNodes.end(); ++iter) {
        if (typeid(**iter) == typeid(ReadNode)) {
            ReadNode* readNode = dynamic_cast<ReadNode*>(*iter);
            readNode->ReadNode::accept(visitor);
        } else if (typeid(**iter) == typeid(PrintNode)) {
            PrintNode* printNode = dynamic_cast<PrintNode*>(*iter);
            printNode->PrintNode::accept(visitor);
        } else if (typeid(**iter) == typeid(IfNode)) {
            IfNode* ifNode = dynamic_cast<IfNode*>(*iter);
            ifNode->IfNode::accept(visitor);
        } else if (typeid(**iter) == typeid(CallNode)) {
            CallNode* callNode = dynamic_cast<CallNode*>(*iter);
            callNode->CallNode::accept(visitor);
        } else if (typeid(**iter) == typeid(WhileNode)) {
            WhileNode* whileNode = dynamic_cast<WhileNode*>(*iter);
            whileNode->WhileNode::accept(visitor);
        } else {
            AssignNode* assignNode = dynamic_cast<AssignNode*>(*iter);
            assignNode->AssignNode::accept(visitor);
        }
    }
    visitor->visitStmtLstNode(this->stmtNodes);
}
