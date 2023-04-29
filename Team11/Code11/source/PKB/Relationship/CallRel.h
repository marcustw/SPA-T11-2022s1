#pragma once

#ifndef CALL_REL
#define CALL_REL

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"
#include "../BidirectionalTable/SameSynonymBidirectionalTable.h"

class CallRel {
private:
	SameSynonymBidirectionalTable<std::string> callTable;

public:
	CallRel();

	// store procedure p1 and set of procedures that calls p1 directly in bidirectional tables
	void insertCalls(std::string procName, std::unordered_set<std::string> procLst);

	std::vector<std::string> getCallsLeftArgLst(std::string rightArg);
	std::vector<std::string> getCallsRightArgLst(std::string leftArg);
};

#endif
