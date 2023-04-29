
#include "Follows.h"

Follows::Follows() {}

void Follows::insertFollows(StmtIndex s0, StmtIndex s1) {
	fromS0ToS1FollowsTable.insert({ s0, s1 });
	fromS1ToS0FollowsTable.insert({ s1, s0 });
}

std::vector<std::string> Follows::getFollowLeftArg(StmtIndex rightArg) {
	std::unordered_map<StmtIndex, StmtIndex>::const_iterator argExist =
		fromS1ToS0FollowsTable.find(rightArg);
	std::vector<std::string> res;

	if (argExist != fromS1ToS0FollowsTable.end()) {
		StmtIndex stmtArg = argExist->second;
		res = { std::to_string(stmtArg)};
	}
	return res;
}

std::vector<std::string> Follows::getFollowRightArg(StmtIndex leftArg) {
	std::unordered_map<StmtIndex, StmtIndex>::const_iterator argExist =
		fromS0ToS1FollowsTable.find(leftArg);
	std::vector<std::string> res;

	if (argExist != fromS0ToS1FollowsTable.end()) {
		StmtIndex rightArg = argExist->second;
		res = { std::to_string(rightArg) };
	}
	return res;
}
