#include "FollowsVisitor.h"

#include <vector>
#include <iterator>
#include <unordered_map>

FollowsVisitor::FollowsVisitor(PKBStorageAPI pkbStorageApi) : pkbStorageApi(pkbStorageApi) {}
FollowsVisitor::~FollowsVisitor() {}

void FollowsVisitor::visitStmtLstNode(std::vector<StmtNode*> stmtNodes) {
	if (!stmtNodes.empty()) {
		const size_t adjMatrixSize = stmtNodes.size();
		for (size_t i = 0; i < adjMatrixSize - 1; i++) {
			int s1 = stmtNodes[i]->getStmtIndex();
			int s2 = stmtNodes[i + 1]->getStmtIndex();
			pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::FOLLOWS, s1, s2);
			for (size_t j = i + 1; j < adjMatrixSize; j++) {
				int s3 = stmtNodes[j]->getStmtIndex();
				std::vector<int> ls = { s3 };
				pkbStorageApi.PKBStorageAPI::setRelationship(RelationshipType::FOLLOWS_T, s1, ls);
			}
		}
	}
}
