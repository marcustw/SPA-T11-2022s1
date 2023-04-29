#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>
#include <queue>

#include "AffectsTProcessor.h"

AffectsTProcessor::AffectsTProcessor(AffectsProcessor* affectsProcessor, PKBQueryAPI pkbQueryApi)
	: AffectsProcessor(pkbQueryApi)
{
	AffectsTProcessor::affectsTcache = affectsProcessor->getCache();
	AffectsTProcessor::affectsProcessor = affectsProcessor;
}



AffectsTProcessor::~AffectsTProcessor() {
	delete AffectsTProcessor::cache;
}


bool AffectsTProcessor::checkRs(const std::string& leftIndex, const std::string& rightIndex) {
	StmtIndex left = std::stoi(leftIndex);
	StmtIndex right = std::stoi(rightIndex);
	if (isInvalid(left, right)) {
		return false;
	}
	if (this->affectsProcessor->contains(left, right)) {
		return true;
	}
	if (this->cache->hasComputedPred(left) || this->cache->hasComputedSuc(right)) {
		return false;
	}
	std::unordered_set<StmtIndex> explored;
	std::queue<StmtIndex> frontier;
	frontier.push(left);

	while (!frontier.empty()) {
		StmtIndex idx = frontier.front();
		frontier.pop();

		std::vector<std::string> affected = this->affectsProcessor->getAllRightStmt(std::to_string(idx));
		for (auto& affect : affected) {
			StmtIndex a = std::stoi(affect);
			if (a == right) {
				return true;
			}
			if (explored.find(a) == explored.end()) {
				explored.insert(a);
				frontier.push(a);
			}
		}
		explored.insert(idx);
	}
	return false;
}

AffectsProcessor* AffectsTProcessor::getAffectsProcessor() {
	return this->affectsProcessor;
}
