#pragma once

#include <unordered_map>
#include <unordered_set>

#include "../../PKB/PKBStorageAPI.h"

class NextExtractor {
private:
	std::unordered_map<int, std::unordered_set<int>>* cfgMap;
	PKBStorageAPI pkbStorageApi;

public:
	NextExtractor(std::unordered_map<int, std::unordered_set<int>>* cfgMap, PKBStorageAPI pkbStorageApi);
	void extractNext();
};
