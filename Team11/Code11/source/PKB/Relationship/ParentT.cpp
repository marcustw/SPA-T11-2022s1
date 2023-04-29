#include "ParentT.h"

ParentT::ParentT() {}

void ParentT::insertParentT(StmtIndex s0, std::vector<StmtIndex> children) {  // need to do to every parentT
	std::unordered_set<StmtIndex> stmtSet;
	stmtSet = parentTTable.contains(TableDirection::LEFTKEY, s0);

	for (auto& child : children) {
		stmtSet.insert(child);
		// populate fromS2ToS0S1LstParentTTable
		std::unordered_set<StmtIndex> parentSet;
		parentSet = parentTTable.contains(TableDirection::RIGHTKEY, child);
		parentSet.insert(s0);;
		std::unordered_set<StmtIndex> s1Parents;
		s1Parents = parentTTable.contains(TableDirection::RIGHTKEY, s0);
		for (auto& s1Parent : s1Parents) {
			parentSet.insert(s1Parent);
		}
		parentTTable.insert(TableDirection::RIGHTKEY, child, parentSet);
	}
	// populate fromS0ToS1S2LstParentTTable
	parentTTable.insert(TableDirection::LEFTKEY, s0, stmtSet);
}

std::vector<std::string> ParentT::getParentTLeftArgLst(StmtIndex rightArg) {
	std::vector<std::string> res;
	std::unordered_set<StmtIndex> leftArgSet = parentTTable.contains(TableDirection::RIGHTKEY, rightArg);
	for (auto& leftArg : leftArgSet) {
		res.push_back(std::to_string(leftArg));
    }
    return res;
}

std::vector<std::string> ParentT::getParentTRightArgLst(StmtIndex leftArg) {
	std::vector<std::string> res;
	std::unordered_set<StmtIndex> rightArgSet = parentTTable.contains(TableDirection::LEFTKEY, leftArg);
	for (auto& rightArg : rightArgSet) {
		res.push_back(std::to_string(rightArg));
	}
	return res;
}
