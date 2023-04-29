#pragma once

#ifndef FOLLOWS_H
#define FOLLOWS_H

#include <unordered_map>
#include <string>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class Follows {
private:
	// key: s0 stmt number , value: s1 stmt number that directly follows S0 on same nesting level
	std::unordered_map<StmtIndex, StmtIndex> fromS0ToS1FollowsTable;

	// key: s1 stmt number, value: s0 stmt number that directly comes before s1 on same nesting level
	std::unordered_map<StmtIndex, StmtIndex> fromS1ToS0FollowsTable;

public:
	Follows();
	void insertFollows(StmtIndex s0, StmtIndex s1);
	std::vector<std::string> getFollowLeftArg(StmtIndex rightArg);
	std::vector<std::string> getFollowRightArg(StmtIndex leftArg);
};

#endif
