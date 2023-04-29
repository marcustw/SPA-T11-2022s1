
#include "Next.h"

Next::Next() {}

void Next::insertNext(StmtIndex s1, std::vector<StmtIndex> s2Set) {
	std::unordered_set<std::string> rightArgSet;
	std::string leftArg = std::to_string(s1);
	rightArgSet = nextTable.contains(TableDirection::LEFTKEY, leftArg);
	for (auto& s2 : s2Set) {
		rightArgSet.insert(std::to_string(s2));
		std::unordered_set<std::string> leftArgSet;
		leftArgSet = nextTable.contains(TableDirection::RIGHTKEY, std::to_string(s2));
		leftArgSet.insert(leftArg);
		nextTable.insert(TableDirection::RIGHTKEY, std::to_string(s2), leftArgSet);
	}
	nextTable.insert(TableDirection::LEFTKEY, leftArg, rightArgSet);
}

std::vector<std::string> Next::getNextLeftArgLst(StmtIndex rightArg) {
	std::vector<std::string> res;
	std::unordered_set<std::string> leftArgSet = nextTable.contains(TableDirection::RIGHTKEY, std::to_string(rightArg));
	res = std::vector<std::string>(leftArgSet.begin(), leftArgSet.end());
	return res;
}

std::vector<std::string> Next::getNextRightArgLst(StmtIndex leftArg) {
	std::vector<std::string> res;
	std::unordered_set<std::string> rightArgSet = nextTable.contains(TableDirection::LEFTKEY, std::to_string(leftArg));
	res = std::vector<std::string>(rightArgSet.begin(), rightArgSet.end());
	return res;
}
