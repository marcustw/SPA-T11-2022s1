#pragma once

#ifndef CONTAINERWHILE_H
#define CONTAINERWHILE_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class ContainerWhile {
private:
	// key: statementNum, value: list of ranges statement number is found in e.g.{{startNum, endNum}, {startNum1, endNum1}}
	std::unordered_map<StmtIndex, std::vector<std::vector<std::string>>> stmtToRangeWhileTable;

	// store all while containers startStmt
	std::unordered_set<std::string> whileContainers;

public:
	ContainerWhile();
	void insertWhileContainer(StmtIndex startStmtNum, StmtIndex endStmtNum);
	std::vector<std::vector<std::string>> getWhileContainerRangeFromStmtIdx(StmtIndex stmtNum);
	std::vector<std::vector<std::string>> getWhileContainerRangeClosed(StmtIndex stmtStart, StmtIndex stmtEnd);
	std::vector<std::string> getAllWhileContainers();
};

#endif
