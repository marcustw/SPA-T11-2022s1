
#include "ContainerIf.h"

ContainerIf::ContainerIf() {}

void ContainerIf::insertIfContainer(std::vector<std::vector<StmtIndex>> containerBlockStmtLst) {
	StmtIndex firstStmt = containerBlockStmtLst.front().front();
	StmtIndex lastStmt = containerBlockStmtLst.back().back();
	ifContainers.insert(std::to_string(firstStmt));
	std::vector<ContainerBlockIndex> containerBlockIdxLst;
	for (auto& containerBlock : containerBlockStmtLst) {
		ifBlockTable.insert({ containerBlock.front(), containerBlock.back() });  // { startNum_of_block, endNum_of_block }
		containerBlockIdxLst.push_back(containerBlock.front());
	}
	struct ContainerInformation containerInformation = { lastStmt, containerBlockIdxLst };
	stmtContainerifTable.insert({ firstStmt, containerInformation });
}

std::vector<std::vector<std::string>> ContainerIf::getIfContainerRangeFromStmtIdx(StmtIndex stmtNum) {
	std::vector<std::vector<std::string>> res;
	for (auto& container : stmtContainerifTable) {
		// need to go through all if Containers incase there are nested containers
		StmtIndex start = container.first;
		StmtIndex end = container.second.lastStmt;
		if (stmtNum >= start && stmtNum <= end) {
			res.push_back({ std::to_string(start), std::to_string(end) });
		}
	}
	return res;
}

std::vector<std::vector<std::string>> ContainerIf::getIfContainerRangeClosed(StmtIndex stmtStart, StmtIndex stmtEnd) {
	std::vector<std::vector<std::string>> res;
	for (auto& container : stmtContainerifTable) {
		// need to go through all if Containers incase there are nested containers
		StmtIndex start = container.first;
		StmtIndex end = container.second.lastStmt;
		if (stmtStart >= start && stmtEnd <= end) {
			res.push_back({ std::to_string(start), std::to_string(end) });
		}
	}
	return res;
}

std::vector<std::string> ContainerIf::getAllIfContainers() {
	std::vector<std::string> res = std::vector<std::string>(ifContainers.begin(), ifContainers.end());
	return res;
}
