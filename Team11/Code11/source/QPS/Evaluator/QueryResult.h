#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "../Common/PQLSyntax.h"
#include "../Common/PQLCommon.h"


class QueryResult {
	StringMap results;
	bool isNone;

	StringMap getPreMergerTable(const QueryResult& otherResult,
		const std::unordered_set<std::string>& sharedDeclarations,
		const std::vector<std::string>& thisUnsharedCol,
		const std::vector<std::string>& otherUnsharedCol);

	StringMap getMergedResults(const QueryResult& otherResult);
	StringMap getCrossJoinResults(const QueryResult& otherResult,
		const std::vector<std::string>& thisUnsharedSyns, const std::vector<std::string>& otherUnsharedSyns);

	std::vector<std::string> getUnsharedColumns(
		const StringMap& resMap,
		const std::unordered_set<std::string>& sharedDeclarations);

	std::unordered_map<std::string, std::unordered_set<std::string>> buildVectorHashRows(
		const StringMap& resMap,
		const std::vector<std::string>& sharedCols,
		const std::vector<std::string>& unsharedCols);

	StringMap getInnerJoinResults(
		const QueryResult& otherResult, const std::unordered_set<std::string>& sharedDeclarations,
		const std::vector<std::string>& thisUnsharedSyns, const std::vector<std::string>& otherUnsharedSyns);

public:
	// Constructors
	explicit QueryResult(const StringMap& results);
	explicit QueryResult(bool isNone);

	// Merging table
	QueryResult merge(const QueryResult& otherResult);

	// Filter table
	QueryResult filter(const std::unordered_set<std::string>& filterSyns);

	std::vector<std::string> getResult(std::string declaration) const;
	std::vector<std::string> getUnmodifiedResult(std::string declaration) const;
	std::vector<std::string> getColumn(std::string declaration) const;
	std::unordered_set<std::string> getSynonyms();
	bool hasNone();

	std::unordered_map<std::string, std::unordered_set<std::string>> getHashRows(
		const std::vector<std::string>& selectSyns);

	size_t getSize() const;
};
