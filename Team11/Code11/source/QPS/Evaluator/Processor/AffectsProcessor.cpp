#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>
#include <queue>

#include "AffectsProcessor.h"
#include "../../../Common/Types.h"

AffectsProcessor::AffectsProcessor(PKBQueryAPI pkbQueryApi) : AffectsBaseProcessor(pkbQueryApi) {
	AffectsProcessor::cache = new QPSCache();
}

AffectsProcessor::AffectsProcessor(QPSCache* cache, PKBQueryAPI pkbQueryApi) :
	AffectsBaseProcessor(pkbQueryApi) {
	this->cache = cache;
}

AffectsProcessor::~AffectsProcessor() {
	delete AffectsProcessor::cache;
}

const char NONE_STMT[] = "0";

bool AffectsProcessor::checkTraversal(StmtIndex left, StmtIndex right) {
	std::string modifiedVar = pkbQueryApi.getRelationshipRightArg(RelationshipType::MODIFIES_S, left).front();
	std::unordered_set<StmtIndex> explored;
	std::queue<StmtIndex> frontier;
	frontier.push(left);
	while (!frontier.empty()) {
		StmtIndex idx = frontier.front();
		frontier.pop();
		std::vector<std::string> nexts = pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, idx);
		for (auto& suc : nexts) {
			int s = std::stoi(suc);
			if (pkbQueryApi.getStmtTypeFromStmtIdx(s).empty()) {
				return false;
			}
			if (s == right) {
				return true;
			}
			StatementType stmtType = pkbQueryApi.getStmtTypeFromStmtIdx(s).front();
			if (stmtType == StatementType::CALL_STMT
				&& checkModifiedPath(left, s)) {
				break;
			}

			if (isNonContainerStmt(s)
				&& checkModifiedPath(left, s)) {
				continue;
			}

			if (isPureContainerStmt(s)
				&& checkModifiedPath(left, s)
				&& stmtType != StatementType::IF_STMT) {
				continue;
			}


			if (explored.find(s) == explored.end()) {
				explored.insert(s);
				frontier.push(s);
			}
		}
		explored.insert(idx);
	}
	return false;
}

bool AffectsProcessor::checkRs(const std::string& leftIdx, const std::string& rightIdx) {
	int left = std::stoi(leftIdx);
	int right = std::stoi(rightIdx);
	if (isInvalid(left, right)) {
		return false;
	}
	std::vector<std::string> modifiedVar =
		pkbQueryApi.getRelationshipRightArg(RelationshipType::MODIFIES_S, left);
	std::vector<std::string> usesVars =
		pkbQueryApi.getRelationshipRightArg(RelationshipType::USES_S, right);

	if (find(usesVars.begin(), usesVars.end(), modifiedVar.at(0)) == usesVars.end()
		|| usesVars.size() == 0) {
		return false;
	}
	if (this->cache->contains(left, right)) {
		return true;
	}

	if (this->cache->hasComputedPred(left) && this->cache->hasComputedSuc(right)) {
		return false;
	}
	return checkTraversal(left, right);
}

std::vector<std::string> AffectsProcessor::getNext(StmtIndex idx) {
	return pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, idx);
}

std::vector<std::string> AffectsProcessor::getPrev(StmtIndex idx) {
	return pkbQueryApi.getRelationshipLeftArg(RelationshipType::NEXT, idx);
}

std::vector<std::string> AffectsProcessor::getAllLeftStmt(std::string rightIndex) {
	StmtIndex right = std::stoi(rightIndex);
	if (this->cache->hasComputedSuc(right)) {
		std::unordered_set<StmtIndex> res = this->cache->getLeftArgs(right);
		return getVector(res);
	}
	std::unordered_set<StmtIndex> allStmt;
	std::queue<StmtIndex> frontier;
	frontier.push(right);
	std::unordered_set<StmtIndex> explored;
	while (!frontier.empty()) {
		StmtIndex stmt = frontier.front();
		frontier.pop();
		std::vector<std::string> nexts = getPrev(stmt);
		for (auto& n : nexts) {
			if (n == "0") {     // To check for dummy node prior the first stmt
				break;
			}
			StmtIndex s = std::stoi(n);
			if (checkRs(n, rightIndex)) {
				this->cache->insert(s, right);
				allStmt.insert(s);
			}
			if (explored.find(s) == explored.end()) {
				explored.insert(s);
				frontier.push(s);
			}
		}
		explored.insert(stmt);
	}
	this->cache->insertSucs(right);
	return getVector(allStmt);
}

std::vector<std::string> AffectsProcessor::getAllRightStmt(std::string leftIndex) {
	StmtIndex left = std::stoi(leftIndex);
	if (this->cache->hasComputedPred(left)) {
		std::unordered_set<StmtIndex> res = this->cache->getRightArgs(left);
		return getVector(res);
	}
	std::unordered_set<StmtIndex> allStmt;
	std::queue<StmtIndex> frontier;
	frontier.push(left);
	std::unordered_set<StmtIndex> explored;
	while (!frontier.empty()) {
		StmtIndex stmt = frontier.front();
		frontier.pop();
		std::vector<std::string> nexts = getNext(stmt);
		for (auto& n : nexts) {
			if (n == "0") {     // To check for dummy node prior the first stmt
				break;
			}
			StmtIndex s = std::stoi(n);
			if (checkRs(leftIndex, n)) {
				allStmt.insert(s);
				this->cache->insert(left, s);
			}
			if (explored.find(s) == explored.end()) {
				explored.insert(s);
				frontier.push(s);
			}
		}
		explored.insert(stmt);
	}
	this->cache->insertPreds(left);
	return getVector(allStmt);
}

bool AffectsProcessor::contains(StmtIndex left, StmtIndex right) {
	return this->cache->contains(left, right);
}

QPSCache* AffectsProcessor::getCache() {
	return this->cache;
}
