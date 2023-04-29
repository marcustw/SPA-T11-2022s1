#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>

#include "AffectsBaseProcessor.h"
#include "../../../Common/Types.h"

AffectsBaseProcessor::AffectsBaseProcessor(PKBQueryAPI pkbQueryApi)
	: pkbQueryApi(pkbQueryApi) {}

bool AffectsBaseProcessor::isNonContainerStmt(StmtIndex stmtIndex) {
	return (pkbQueryApi.getContainerRangeFromStmtIdx(StatementType::WHILE_STMT, stmtIndex).empty()
		&& pkbQueryApi.getContainerRangeFromStmtIdx(StatementType::IF_STMT, stmtIndex).empty());
}

bool AffectsBaseProcessor::isPureContainerStmt(StmtIndex stmtIndex) {
	std::vector<std::string> allWhileStmts = pkbQueryApi.getAllWhileContainers();
	return (!AffectsBaseProcessor::isNonContainerStmt(stmtIndex)
		&& (std::find(allWhileStmts.begin(), allWhileStmts.end(), std::to_string(stmtIndex)) ==
			allWhileStmts.end()));
}

std::vector<std::string> AffectsBaseProcessor::getNextStmts(StmtIndex stmtIndex) {
	return pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, stmtIndex);
}

std::vector<std::string> AffectsBaseProcessor::getPrevStmts(StmtIndex stmtIndex) {
	std::vector<std::string> prevStmts = pkbQueryApi.getRelationshipLeftArg(RelationshipType::NEXT, stmtIndex);
	std::reverse(prevStmts.begin(), prevStmts.end());
	return prevStmts;
}

std::vector<std::string> AffectsBaseProcessor::getVector(const std::unordered_set<StmtIndex>& set) {
	std::vector<std::string> ans;
	for (const auto& s : set) {
		ans.push_back(std::to_string(s));
	}
	return ans;
}

bool AffectsBaseProcessor::isInvalid(StmtIndex left, StmtIndex right) {
	std::vector<StatementType> l = pkbQueryApi.getStmtTypeFromStmtIdx(left);
	std::vector<StatementType> r = pkbQueryApi.getStmtTypeFromStmtIdx(right);
	return l.empty() || r.empty() || l.front() != StatementType::ASSIGN_STMT ||
		r.front() != StatementType::ASSIGN_STMT ||
		pkbQueryApi.getRelationshipRightArg(RelationshipType::USES_S, right).empty() ||
		pkbQueryApi.getProcedureFromStmtIdx(left).front() !=
		pkbQueryApi.getProcedureFromStmtIdx(right).front();
}

/*
	Returns False if preliminary constraints are not met for Affects/*(a1, a2):
	1. a1, a2 are assignments
	2. a1, a2 belong in the same procedure
*/
bool AffectsBaseProcessor::checkPrelimConstraints(StmtIndex leftIndex, StmtIndex rightIndex) {
	if (pkbQueryApi.getStmtTypeFromStmtIdx(leftIndex).empty()
		|| pkbQueryApi.getStmtTypeFromStmtIdx(rightIndex).empty()) {
		return false;
	}

	return ((pkbQueryApi.getStmtTypeFromStmtIdx(leftIndex).at(0) == StatementType::ASSIGN_STMT)
		&& (pkbQueryApi.getStmtTypeFromStmtIdx(rightIndex).at(0) == StatementType::ASSIGN_STMT)
		&& !(pkbQueryApi.getProcedureFromStmtIdx(leftIndex).at(0)
			.compare(pkbQueryApi.getProcedureFromStmtIdx(rightIndex).at(0))));
}

bool AffectsBaseProcessor::checkModifiedPath(StmtIndex leftIndex, StmtIndex currentIndex) {
	std::vector<std::string> modifiedVar =
		pkbQueryApi.getRelationshipRightArg(RelationshipType::MODIFIES_S, leftIndex);
	std::vector<std::string> currModifiedVar =
		pkbQueryApi.getRelationshipRightArg(RelationshipType::MODIFIES_S, currentIndex);
	if (modifiedVar.empty()) {
		return false;
	}
	if (std::find(currModifiedVar.begin(), currModifiedVar.end(), modifiedVar.at(0)) == currModifiedVar.end()) {
		return false;
	}
	return true;
}

std::pair<std::vector<std::string>, std::vector<std::string>> AffectsBaseProcessor::getAllAffects() {
	std::vector<std::string> assignStmts = pkbQueryApi.getAllAssignments();
	std::vector<std::string> leftStmts;
	std::vector<std::string> rightStmts;
	for (const std::string& stmt : assignStmts) {
		std::vector<std::string> affected = getAllRightStmt(stmt);
		for (std::string affect : affected) {
			leftStmts.push_back(stmt);
			rightStmts.push_back(affect);
		}
	}
	return std::make_pair(leftStmts, rightStmts);
}
