#include <stack>
#include "CallsExtractor.h"

CallsExtractor::CallsExtractor(const std::unordered_map<std::string,
	std::unordered_set<std::string>> &procMapping,
	PKBStorageAPI pkbStorageApi) : procMapping(procMapping),
	pkbStorageApi(pkbStorageApi) {}

void CallsExtractor::extractCalls() {
	for (auto& it : procMapping) {
		pkbStorageApi.setRelationship(RelationshipType::CALL, it.first, it.second);
	}
}

void CallsExtractor::extractCallsT() {
	std::stack<std::string> procs = std::stack<std::string>();
	std::unordered_set<std::string> currSet = std::unordered_set<std::string>();

	for (auto& it : procMapping) {
		currSet.clear();

		procs.push(it.first);

		while (!procs.empty()) {
			std::string curr = procs.top();
			procs.pop();

			if (procMapping.find(curr) == procMapping.end()) continue;

			for (std::string calledProc : procMapping.at(curr)) {
				currSet.insert(calledProc);
				procs.push(calledProc);
			}
		}
		pkbStorageApi.setRelationship(RelationshipType::CALL_T, it.first, currSet);
	}
}
