#pragma once

#ifndef NEXT_H
#define NEXT_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"
#include "../BidirectionalTable/SameSynonymBidirectionalTable.h"

class Next {
private:
	SameSynonymBidirectionalTable<std::string> nextTable;

public:
	Next();

	// store statement s1 and statements that can be executed directly after s1 in bidirectional tables
	void insertNext(StmtIndex s1, std::vector<StmtIndex> s2Set);

	std::vector<std::string> getNextLeftArgLst(StmtIndex rightArg);
	std::vector<std::string> getNextRightArgLst(StmtIndex leftArg);
};

#endif
