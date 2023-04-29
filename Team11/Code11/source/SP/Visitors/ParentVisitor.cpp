#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>

#include "ParentVisitor.h"
#include "../../Common/Types.h"
#include "../Extractors/ExtractorUtils.h"

ParentVisitor::ParentVisitor(PKBStorageAPI pkbStorageApi) : pkbStorageApi(pkbStorageApi) {}
ParentVisitor::~ParentVisitor() {}


void ParentVisitor::visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes)
{
	std::vector<int> s2Lst = getChildStmtIndexes(whileStmtNodes);
	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::PARENT, stmtIndex, s2Lst);
}

void ParentVisitor::visitIfNode(int stmtIndex,
	int lastStmt,
	std::vector<StmtNode*> ifContainer,
	std::vector<StmtNode*> elseContainer)
{
	std::vector<int> s2LstIf = getChildStmtIndexes(ifContainer);
	std::vector<int> s2LstElse = getChildStmtIndexes(elseContainer);
	copy(s2LstElse.begin(), s2LstElse.end(), back_inserter(s2LstIf));

	pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::PARENT, stmtIndex, s2LstIf);
}
