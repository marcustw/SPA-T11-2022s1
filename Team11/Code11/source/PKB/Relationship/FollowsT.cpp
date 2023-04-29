
#include "FollowsT.h"

FollowsT::FollowsT() {}

void FollowsT::insertFollowsT(StmtIndex s0, std::vector<StmtIndex> followers) {
	std::unordered_set<StmtIndex> s1S2Set;
	std::unordered_set<StmtIndex> followersSet = std::unordered_set<StmtIndex>(followers.begin(), followers.end());
	s1S2Set = followsTTable.contains(TableDirection::LEFTKEY, s0);
	for (auto& follower : followersSet) {
		s1S2Set.insert(follower);
		std::unordered_set<StmtIndex> s0S1Set;
		s0S1Set = followsTTable.contains(TableDirection::RIGHTKEY, follower);
		s0S1Set.insert(s0);
		followsTTable.insert(TableDirection::RIGHTKEY, follower, s0S1Set);
	}
	followsTTable.insert(TableDirection::LEFTKEY, s0, s1S2Set);
}

std::vector<std::string> FollowsT::getFollowsTLeftArgLst(StmtIndex rightArg) {
	std::vector<std::string> res;
	std::unordered_set<StmtIndex> leftArgSet = followsTTable.contains(TableDirection::RIGHTKEY, rightArg);
	for (StmtIndex leftArg : leftArgSet) {
		res.push_back(std::to_string(leftArg));
	}
	return res;
}

std::vector<std::string> FollowsT::getFollowsTRightArgLst(StmtIndex leftArg) {
	std::vector<std::string> res;
	std::unordered_set<StmtIndex> rightArgSet = followsTTable.contains(TableDirection::LEFTKEY, leftArg);
	for (StmtIndex rightArg : rightArgSet) {
		res.push_back(std::to_string(rightArg));
	}
	return res;
}
