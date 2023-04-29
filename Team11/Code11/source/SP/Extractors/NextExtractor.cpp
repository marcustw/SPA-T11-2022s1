#include "NextExtractor.h"

NextExtractor::NextExtractor(std::unordered_map<int, std::unordered_set<int>>* cfgMap, PKBStorageAPI pkbStorageApi)
	: cfgMap(cfgMap), pkbStorageApi(pkbStorageApi) {}

void NextExtractor::extractNext() {
	for (auto& it : *cfgMap) {
		std::vector<int> vector = std::vector<int>();
		for (auto& it2 : it.second) {
			vector.push_back(it2);
		}
		pkbStorageApi.setRelationship(RelationshipType::NEXT, it.first, vector);
	}
}
