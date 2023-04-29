#pragma once

#ifndef CALLS_T
#define CALLS_T

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"
#include "../BidirectionalTable/SameSynonymBidirectionalTable.h"

class CallsT {
private:
	SameSynonymBidirectionalTable<std::string> callTTable;

public:
	CallsT();

	// store procedure p1 and set of procedures that calls p1 indirectly/directly in bidirectional tables
	void insertCallsT(std::string procName, std::unordered_set<std::string> procLst);

	std::vector<std::string> getCallsTLeftArgLst(std::string rightArg);
	std::vector<std::string> getCallsTRightArgLst(std::string leftArg);
};

#endif
