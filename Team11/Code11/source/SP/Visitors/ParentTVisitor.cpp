#include <vector>

#include "ParentTVisitor.h"
#include "../../Common/Types.h"
#include "../Extractors/ExtractorUtils.h"

ParentTVisitor::ParentTVisitor(PKBStorageAPI pkbStorageApi) : pkbStorageApi(pkbStorageApi) {}
ParentTVisitor::~ParentTVisitor() {}

void ParentTVisitor::visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes)
{
	std::vector<int> s2Lst = std::vector<int>();
	for (int i = stmtIndex + 1; i <= lastStmt; i++) {
		s2Lst.push_back(i);
	}
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::PARENT_T, stmtIndex, s2Lst);
}

void ParentTVisitor::visitIfNode(int stmtIndex,
	int lastStmt,
	std::vector<StmtNode*> ifContainer,
	std::vector<StmtNode*> thenContainer)
{
	std::vector<int> s2Lst = std::vector<int>();
	for (int i = stmtIndex + 1; i <= lastStmt; i++) {
		s2Lst.push_back(i);
	}
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::PARENT_T, stmtIndex, s2Lst);
}
