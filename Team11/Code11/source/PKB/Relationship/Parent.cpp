
#include "Parent.h"

Parent::Parent() {}

void Parent::insertParent(StmtIndex s0, std::vector<StmtIndex> s1Lst) {
	std::unordered_map<StmtIndex, std::unordered_set<StmtIndex>>::const_iterator s0Exist =
		fromS0ToS1LstParentTable.find(s0);
	std::unordered_set<StmtIndex> stmtSet;
	if (s0Exist != fromS0ToS1LstParentTable.end()) {
		stmtSet = s0Exist->second;
	}
	for (auto& stmt : s1Lst) {
		stmtSet.insert(stmt);
		std::unordered_map<StmtIndex, StmtIndex>::const_iterator s1ParentsExist =
			fromS1ToS0ParentTable.find(s0);
		fromS1ToS0ParentTable[stmt] = s0;
	}
	fromS0ToS1LstParentTable[s0] = stmtSet;
}

std::vector<std::string> Parent::getParentLeftArgLst(StmtIndex rightArg) {
	std::unordered_map<StmtIndex, StmtIndex>::const_iterator rightArgExist =
		fromS1ToS0ParentTable.find(rightArg);
	std::vector<std::string> res;

	if (rightArgExist != fromS1ToS0ParentTable.end()) {
		StmtIndex leftArg = rightArgExist->second;
		res = { std::to_string(leftArg) };
	}
	return res;
}

std::vector<std::string> Parent::getParentRightArgLst(StmtIndex leftArg) {
	std::unordered_map<StmtIndex, std::unordered_set<StmtIndex>>::const_iterator leftArgExist =
		fromS0ToS1LstParentTable.find(leftArg);
	std::vector<std::string> res;

	if (leftArgExist != fromS0ToS1LstParentTable.end()) {
		std::unordered_set<StmtIndex> rightArgLst = leftArgExist->second;
		for (auto& rightArg : rightArgLst) {
			res.push_back(std::to_string(rightArg));
		}
	}
	return res;
}
