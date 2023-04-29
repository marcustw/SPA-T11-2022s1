#pragma once

#ifndef PARENT_H
#define PARENT_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class Parent {
private:
	// key: s0 stmt number , value: s1 stmt number that is directly nested in S0
	std::unordered_map<StmtIndex, std::unordered_set<StmtIndex>> fromS0ToS1LstParentTable;

	// key: s1 stmt number, value: s0 stmt number that is direct parent of s1
	std::unordered_map<StmtIndex, StmtIndex> fromS1ToS0ParentTable;

public:
	Parent();
	void insertParent(StmtIndex s0, std::vector<StmtIndex> s1Lst);
	std::vector<std::string> getParentLeftArgLst(StmtIndex rightArg);
	std::vector<std::string> getParentRightArgLst(StmtIndex leftArg);
};

#endif
