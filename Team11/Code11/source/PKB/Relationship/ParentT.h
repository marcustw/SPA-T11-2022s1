#pragma once

#ifndef PARENTT_H
#define PARENTT_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"
#include "../BidirectionalTable/SameSynonymBidirectionalTable.h"

class ParentT {
private:
	SameSynonymBidirectionalTable<StmtIndex> parentTTable;

public:
	ParentT();

	// store statement s0 and statements that is nested directly/indirectly in S0 in bidirectional tables
	void insertParentT(StmtIndex s0, std::vector<StmtIndex> children);

	std::vector<std::string> getParentTLeftArgLst(StmtIndex rightArg);
	std::vector<std::string> getParentTRightArgLst(StmtIndex leftArg);
};

#endif
