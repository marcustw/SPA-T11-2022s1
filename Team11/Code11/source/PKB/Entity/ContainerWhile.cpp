
#include "ContainerWhile.h"

ContainerWhile::ContainerWhile() {}

// alternative implementation
void ContainerWhile::insertWhileContainer(StmtIndex startStmtNum, StmtIndex endStmtNum) {
	whileContainers.insert(std::to_string(startStmtNum));
	for (StmtIndex i = startStmtNum; i <= endStmtNum; ++i) {
		std::unordered_map<StmtIndex, std::vector<std::vector<std::string>>>::const_iterator stmtExist =
			stmtToRangeWhileTable.find(i);
		std::vector<std::vector<std::string>> rangeLst;
		if (stmtExist != stmtToRangeWhileTable.end()) {
			rangeLst = stmtExist->second;
		}
		rangeLst.push_back({ std::to_string(startStmtNum), std::to_string(endStmtNum) });
		stmtToRangeWhileTable[i] = rangeLst;
	}
}

std::vector<std::vector<std::string>> ContainerWhile::getWhileContainerRangeFromStmtIdx(StmtIndex stmtNum) {
	std::unordered_map<StmtIndex, std::vector<std::vector<std::string>>>::const_iterator stmtExist =
		stmtToRangeWhileTable.find(stmtNum);
	std::vector<std::vector<std::string>> res;

	if (stmtExist != stmtToRangeWhileTable.end()) {
		res = stmtExist->second;
	}
	return res;
}

std::vector<std::vector<std::string>> ContainerWhile::getWhileContainerRangeClosed(
	StmtIndex stmtStart, StmtIndex stmtEnd)
{
	std::unordered_map<StmtIndex, std::vector<std::vector<std::string>>>::const_iterator stmtExist =
		stmtToRangeWhileTable.find(stmtStart);
	std::vector<std::vector<std::string>> res;

	if (stmtExist == stmtToRangeWhileTable.end()) {
		return res;
	}

	std::vector<std::vector<std::string>> rangeLst = stmtExist->second;
	for (auto& range : rangeLst) {
		if (stmtStart >= std::stoi(range.front()) && stmtEnd <= std::stoi(range.back())) {
			res.push_back(range);
		}
	}

	return res;
}

std::vector<std::string> ContainerWhile::getAllWhileContainers() {
	std::vector<std::string> res = std::vector<std::string>(whileContainers.begin(),
		whileContainers.end());
	return res;
}
