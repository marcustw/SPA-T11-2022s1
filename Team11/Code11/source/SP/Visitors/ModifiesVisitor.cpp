#include "ModifiesVisitor.h"
#include "../../Common/Types.h"
#include "../Extractors/ExtractorUtils.h"

ModifiesVisitor::ModifiesVisitor(PKBStorageAPI pkbStorageApi) : pkbStorageApi(pkbStorageApi) {}
ModifiesVisitor::~ModifiesVisitor() {}

void ModifiesVisitor::visitProcedureNode(int stmtIndex, int lastStmt, std::string procName) {
	std::vector<std::string> s2Lst = std::vector<std::string>();
	for (int i = stmtIndex; i <= lastStmt; i++) {
		for (auto& c : varExprMapping[i]) {
			s2Lst.push_back(c);
		}
	}
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::MODIFIES_P, procName, s2Lst);

	/*
		Handling of Procedure Call only when procedure has been successfully built.
		If handling only segments of code, it may not be included in the modifies relation.
	*/
	if (allCallNodes.find(procName) != allCallNodes.end()) {
		for (auto& stmtNo : allCallNodes[procName]) {
			pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::MODIFIES_S, stmtNo, s2Lst);
		}
	}

	procAllVarsMapping[procName] = varExprMapping;
	varExprMapping.clear();
}

void ModifiesVisitor::visitCallNode(int stmtIndex, std::string procName, std::string callerProcName) {
	allCallNodes[procName].insert(stmtIndex);
}

void ModifiesVisitor::visitReadNode(int stmtIndex, std::string varName)
{
	std::vector<std::string> s2Lst = std::vector<std::string>();
	s2Lst.push_back(varName);
	varExprMapping[stmtIndex].insert(varName);
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::MODIFIES_S, stmtIndex, s2Lst);
}

void ModifiesVisitor::visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode)
{
	std::vector<std::string> s2Lst = std::vector<std::string>();
	s2Lst.push_back(varName);
	varExprMapping[stmtIndex].insert(varName);
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::MODIFIES_S, stmtIndex, s2Lst);
}

void ModifiesVisitor::visitExpressionNode(ExpressionNode* self)
{
	ExpressionType exprType = self->getExpressionType();
	StmtIndex stmtIndex = self->getStmtIndex();
	ExpressionPos exprPos = self->getExpressionPos();
	std::string value = self->getValue();

	std::vector<std::string> s2Lst = std::vector<std::string>();
	if (exprType == ExpressionType::VARIABLE && exprPos == ExpressionPos::LHS) {
		varExprMapping[stmtIndex].insert(value);
		s2Lst.push_back(value);
		pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::MODIFIES_S, stmtIndex, s2Lst);
	}
}

void ModifiesVisitor::visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes)
{
	std::vector<std::string> s2Lst = std::vector<std::string>();

	for (int i = stmtIndex + 1; i <= lastStmt; i++) {
		for (auto& c : varExprMapping[i]) {
			s2Lst.push_back(c);
		}
	}
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::MODIFIES_S, stmtIndex, s2Lst);
}

void ModifiesVisitor::visitIfNode(int stmtIndex,
	int lastStmt,
	std::vector<StmtNode*> ifContainer,
	std::vector<StmtNode*> thenContainer)
{
	std::vector<std::string> s2Lst = std::vector<std::string>();

	for (int i = stmtIndex + 1; i <= lastStmt; i++) {
		for (auto& c : varExprMapping[i]) {
			s2Lst.push_back(c);
		}
	}
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::MODIFIES_S, stmtIndex, s2Lst);
}
