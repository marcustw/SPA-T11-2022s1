#include "EntityVisitor.h"
#include "../../Common/Types.h"
#include "../Extractors/ExtractorUtils.h"

EntityVisitor::EntityVisitor(PKBStorageAPI pkbStorageApi) : pkbStorageApi(pkbStorageApi) {}
EntityVisitor::~EntityVisitor() {}


void EntityVisitor::visitProcedureNode(int stmtIndex, int lastStmt, std::string procedureName) {
    pkbStorageApi.PKBStorageAPI::insertProc(stmtIndex, lastStmt, procedureName);
}

void EntityVisitor::visitReadNode(int stmtIndex, std::string varName) {
    pkbStorageApi.PKBStorageAPI::insertRead(stmtIndex, varName);
    pkbStorageApi.PKBStorageAPI::insertVar(stmtIndex, varName);
    pkbStorageApi.PKBStorageAPI::insertStmt(stmtIndex, StatementType::READ_STMT);
}

void EntityVisitor::visitPrintNode(int stmtIndex, std::string varName) {
    pkbStorageApi.PKBStorageAPI::insertPrint(stmtIndex, varName);
    pkbStorageApi.PKBStorageAPI::insertVar(stmtIndex, varName);
    pkbStorageApi.PKBStorageAPI::insertStmt(stmtIndex, StatementType::PRINT_STMT);
}

void EntityVisitor::visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode) {
    pkbStorageApi.PKBStorageAPI::insertAssign(stmtIndex, varName);
    pkbStorageApi.PKBStorageAPI::insertStmt(stmtIndex, StatementType::ASSIGN_STMT);
}

void EntityVisitor::visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes) {
    pkbStorageApi.PKBStorageAPI::insertStmt(stmtIndex, StatementType::WHILE_STMT);
    pkbStorageApi.PKBStorageAPI::insertWhileContainer(stmtIndex, lastStmt);
}

void EntityVisitor::visitIfNode(int stmtIndex,
    int lastStmt,
    std::vector<StmtNode*> ifContainer,
    std::vector<StmtNode*> thenContainer) {
    pkbStorageApi.PKBStorageAPI::insertStmt(stmtIndex, StatementType::IF_STMT);

    std::vector<int> ifContainerIndexes = std::vector<int>();
    std::vector<int> tempIfContainerIndexes = getChildStmtIndexes(ifContainer);
    ifContainerIndexes.push_back(stmtIndex);
    ifContainerIndexes.insert(std::end(ifContainerIndexes),
        std::begin(tempIfContainerIndexes),
        std::end(tempIfContainerIndexes));

    std::vector<int> thenContainerIndexes = getChildStmtIndexes(thenContainer);
    thenContainerIndexes.push_back(lastStmt);

    std::vector<std::vector<int>> motherIfContainer = std::vector<std::vector<int>>();
    motherIfContainer.push_back(ifContainerIndexes);
    motherIfContainer.push_back(thenContainerIndexes);

    pkbStorageApi.PKBStorageAPI::insertIfContainer(motherIfContainer);
}

void EntityVisitor::visitCallNode(int stmtIndex, std::string procName, std::string callerProcName) {
    pkbStorageApi.PKBStorageAPI::insertProcCall(stmtIndex, procName, callerProcName);
    pkbStorageApi.PKBStorageAPI::insertStmt(stmtIndex, StatementType::CALL_STMT);
    pkbStorageApi.PKBStorageAPI::updateProcCall(procName, callerProcName);
}

void EntityVisitor::visitExpressionNode(ExpressionNode* self) {
    if (self->getExpressionType() == ExpressionType::VARIABLE) {
        pkbStorageApi.PKBStorageAPI::insertVar(self->getStmtIndex(), self->getValue());
    } else if (self->getExpressionType() == ExpressionType::CONSTANT) {
        std::vector<int> allConst;
        allConst.push_back(std::stoi(self->getValue()));
        pkbStorageApi.PKBStorageAPI::insertConst(self->getStmtIndex(), allConst);
    }
}
