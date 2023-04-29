#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../PKB/PKBStorageAPI.h"

#ifndef TEAM11_CODE11_SOURCE_SP_EXTRACTORS_CALLSEXTRACTOR_H_
#define TEAM11_CODE11_SOURCE_SP_EXTRACTORS_CALLSEXTRACTOR_H_

class CallsExtractor {
private:
	PKBStorageAPI pkbStorageApi;
	const std::unordered_map<std::string, std::unordered_set<std::string>> &procMapping;

public:
	CallsExtractor(const std::unordered_map<std::string,
		std::unordered_set<std::string>> &procMapping,
		PKBStorageAPI pkbStorageApi);

	void extractCalls();

	void extractCallsT();
};

#endif  // TEAM11_CODE11_SOURCE_SP_EXTRACTORS_CALLSEXTRACTOR_H_
