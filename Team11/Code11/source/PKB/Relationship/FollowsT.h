#pragma once

#ifndef FOLLOWST_H
#define FOLLOWST_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

#include "../../Common/Types.h"
#include "../BidirectionalTable/SameSynonymBidirectionalTable.h"

class FollowsT {
private:
	SameSynonymBidirectionalTable<StmtIndex> followsTTable;

public:
	FollowsT();

	// store statement s0 and possible statements that follow S0 on same nesting level in bidirectional tables
	void insertFollowsT(StmtIndex s0, std::vector<StmtIndex> followers);

	std::vector<std::string> getFollowsTLeftArgLst(StmtIndex rightArg);
	std::vector<std::string> getFollowsTRightArgLst(StmtIndex leftArg);
};

#endif
