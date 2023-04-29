#pragma once

#ifndef CONTAINERIF_H
#define CONTAINERIF_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include "../../Common/Types.h"

struct ContainerInformation {
	StmtIndex lastStmt;
	std::vector<ContainerBlockIndex> containerBlockIdxLst;  // list of block start numbers
};

class ContainerIf {
private:
	// key: startNum_of_container, value: endNum_of_container & containerBlockIdxLst(list of blocks startNum)
	std::unordered_map<StmtIndex, ContainerInformation> stmtContainerifTable;

	// key: startNum_of_block, value: endNum_of_block
	std::unordered_map<ContainerBlockIndex, StmtIndex> ifBlockTable;

	// stores start statement number of if containers e.g. 2 if-containers -> {"1","5"}
	std::unordered_set<std::string> ifContainers;

public:
	ContainerIf();
	void insertIfContainer(std::vector<std::vector<StmtIndex>> containerBlockStmtLst);
	std::vector<std::vector<std::string>> getIfContainerRangeFromStmtIdx(StmtIndex stmtNum);
	std::vector<std::vector<std::string>> getIfContainerRangeClosed(StmtIndex stmtStart, StmtIndex stmtEnd);
	std::vector<std::string> getAllIfContainers();
};

#endif
