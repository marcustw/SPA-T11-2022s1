#include <unordered_map>
#include <vector>

#include "UsesVisitor.h"
#include "../../Common/Types.h"
#include "../Extractors/ExtractorUtils.h"

UsesVisitor::UsesVisitor(PKBStorageAPI pkbStorageApi) : pkbStorageApi(pkbStorageApi) {}
UsesVisitor::~UsesVisitor() {}

void UsesVisitor::visitProcedureNode(int stmtIndex, int lastStmt, std::string procName)
{
	std::vector<std::string> s2Lst = std::vector<std::string>();

	for (int i = stmtIndex; i <= lastStmt; i++) {
		for (auto& c : varExprMapping[i]) {
			s2Lst.push_back(c);
		}
	}
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::USES_P, procName, s2Lst);

	if (allCallNodes.find(procName) != allCallNodes.end()) {
		for (auto& stmtNo : allCallNodes[procName]) {
			pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::USES_S, stmtNo, s2Lst);
		}
	}

	procAllVarsMapping[procName] = varExprMapping;
	varExprMapping.clear();
}

void UsesVisitor::visitCallNode(int stmtIndex, std::string procName, std::string callerProcName)
{
	allCallNodes[procName].insert(stmtIndex);
}

void UsesVisitor::visitPrintNode(int stmtIndex, std::string varName)
{
	if (varExprMapping.find(stmtIndex) == varExprMapping.end()) {
		varExprMapping[stmtIndex] = std::unordered_set<std::string>();
	}
	varExprMapping.at(stmtIndex).insert(varName);
	std::vector<std::string> s2Lst =
		std::vector<std::string>(varExprMapping[stmtIndex].begin(), varExprMapping[stmtIndex].end());
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::USES_S, stmtIndex, s2Lst);
}

void UsesVisitor::visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode)
{
	if (varExprMapping.find(stmtIndex) == varExprMapping.end()) {
		varExprMapping[stmtIndex] = std::unordered_set<std::string>();
	}
	std::vector<std::string> s2Lst =
		std::vector<std::string>(varExprMapping[stmtIndex].begin(), varExprMapping[stmtIndex].end());

	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::USES_S, stmtIndex, s2Lst);
}

void UsesVisitor::visitExpressionNode(ExpressionNode* self)
{
	ExpressionType exprType = self->getExpressionType();
	ExpressionPos exprPos = self->getExpressionPos();
	StmtIndex stmtIndex = self->getStmtIndex();
	std::string value = self->getValue();

	if (exprType == ExpressionType::VARIABLE && exprPos != ExpressionPos::LHS) {
		if (varExprMapping.find(stmtIndex) == varExprMapping.end()) {
			varExprMapping[stmtIndex] = std::unordered_set<std::string>();
		}
		varExprMapping[stmtIndex].insert(value);
	}
}

void UsesVisitor::visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> childrenStmtNodes)
{
	std::vector<std::string> allVars = std::vector<std::string>();
	if (varExprMapping.find(stmtIndex) == varExprMapping.end()) {
		varExprMapping[stmtIndex] = std::unordered_set<std::string>();
	}
	allVars = std::vector<std::string>(varExprMapping[stmtIndex].begin(), varExprMapping[stmtIndex].end());
	for (int i = stmtIndex + 1; i <= lastStmt; i++) {
		allVars.insert(allVars.end(), varExprMapping[i].begin(), varExprMapping[i].end());
	}
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::USES_S, stmtIndex, allVars);
}

void UsesVisitor::visitIfNode(int stmtIndex,
	int lastStmt,
	std::vector<StmtNode*> ifContainer,
	std::vector<StmtNode*> thenContainer)
{
	std::vector<std::string> allVars = std::vector<std::string>();
	if (varExprMapping.find(stmtIndex) == varExprMapping.end()) {
		varExprMapping[stmtIndex] = std::unordered_set<std::string>();
	}
	allVars = std::vector<std::string>(varExprMapping[stmtIndex].begin(), varExprMapping[stmtIndex].end());
	for (int i = stmtIndex + 1; i <= lastStmt; i++) {
		allVars.insert(allVars.end(), varExprMapping[i].begin(), varExprMapping[i].end());
	}
	std::vector<std::string> s2Lst = std::vector<std::string>(allVars.begin(), allVars.end());

	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::USES_S, stmtIndex, s2Lst);
}
