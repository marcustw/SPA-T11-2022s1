#include "QueryResult.h"

QueryResult::QueryResult(bool isNone) : isNone(isNone), results(std::unordered_map<std::string,
	std::vector<std::string>>()) {}

QueryResult::QueryResult(const StringMap& results) :
	results(results), isNone(false) {
	if (!results.empty() && results.begin()->second.empty()) {
		QueryResult::isNone = true;
	}
}

StringMap QueryResult::getPreMergerTable(const QueryResult& otherResult,
	const std::unordered_set<std::string>& sharedDeclarations, const std::vector<std::string>& thisUnsharedCol,
	const std::vector<std::string>& otherUnsharedCol)
{
	StringMap mergedResults;
	for (const std::string& sharedKey : sharedDeclarations) {
		mergedResults[sharedKey] = std::vector<std::string>();
	}
	for (const std::string& unshared : thisUnsharedCol) {
		mergedResults[unshared] = std::vector<std::string>();
	}
	for (const std::string& unshared : otherUnsharedCol) {
		mergedResults[unshared] = std::vector<std::string>();
	}
	return mergedResults;
}

StringMap QueryResult::getCrossJoinResults(
	const QueryResult& otherResult,
	const std::vector<std::string>& thisUnsharedSyns, const std::vector<std::string>& otherUnsharedSyns)
{
	std::unordered_set<std::string> sharedSyns = std::unordered_set<std::string>();
	StringMap mergedResults = getPreMergerTable(otherResult,
		sharedSyns, thisUnsharedSyns, otherUnsharedSyns);
	size_t resSize = results.begin()->second.size();
	size_t otherResSize = otherResult.results.begin()->second.size();
	for (size_t i = 0; i < resSize; i++) {
		for (size_t j = 0; j < otherResSize; j++) {
			for (const std::string& unshared : thisUnsharedSyns) {
				mergedResults[unshared].push_back(results[unshared].at(i));
			}
			for (const std::string& unshared : otherUnsharedSyns) {
				mergedResults[unshared].push_back(otherResult.results.at(unshared).at(j));
			}
		}
	}
	return mergedResults;
}

std::unordered_map<std::string, std::unordered_set<std::string>> QueryResult::buildVectorHashRows(
	const StringMap& resMap, const std::vector<std::string>& sharedCols,
	const std::vector<std::string>& unsharedCols)
{
	std::unordered_map<std::string, std::unordered_set<std::string>> vectorHashRows;
	size_t resSize = resMap.begin()->second.size();
	for (size_t i = 0; i < resSize; i++) {
		std::string colVals = PQLCommon::vectorHash(i, resMap, sharedCols);
		std::string unsharedVals = PQLCommon::vectorHash(i, resMap, unsharedCols);
		if (vectorHashRows.find(colVals) == vectorHashRows.end()) {
			vectorHashRows[colVals] = std::unordered_set<std::string>();
		}
		vectorHashRows[colVals].insert(unsharedVals);
	}
	return vectorHashRows;
}

std::unordered_map<std::string, std::unordered_set<std::string>> QueryResult::getHashRows(
	const std::vector<std::string>& selectSyns)
{
	std::vector<std::string> unsharedCols = std::vector<std::string>();
	return buildVectorHashRows(results, selectSyns, unsharedCols);
}

void populate(StringMap* mergedResults, const std::vector<std::string>& sharedSyns,
	const std::vector<std::string>& thisUnsharedSyns, const std::vector<std::string>& otherUnsharedSyns,
	const std::pair<std::string, std::unordered_set<std::string>>& kv,
	const std::unordered_set<std::string>& otherVals)
{
	std::vector<std::string> sharedSynCols = PQLCommon::getSynonymVectorFromHash(kv.first);

	for (const std::string& thisValStr : kv.second) {
		std::vector<std::string> thisVal = PQLCommon::getSynonymVectorFromHash(thisValStr);
		for (const std::string& otherValStr : otherVals) {
			std::vector<std::string> otherVal = PQLCommon::getSynonymVectorFromHash(otherValStr);
			for (size_t i = 0; i < sharedSyns.size(); i++) {
				mergedResults->at(sharedSyns[i]).push_back(sharedSynCols[i]);
			}
			for (size_t i = 0; i < thisUnsharedSyns.size(); i++) {
				mergedResults->at(thisUnsharedSyns[i]).push_back(thisVal[i]);
			}
			for (size_t i = 0; i < otherUnsharedSyns.size(); i++) {
				mergedResults->at(otherUnsharedSyns[i]).push_back(otherVal[i]);
			}
		}
	}
}

StringMap QueryResult::getInnerJoinResults(
	const QueryResult& otherResult, const std::unordered_set<std::string>& sharedDeclarations,
	const std::vector<std::string>& thisUnsharedSyns, const std::vector<std::string>& otherUnsharedSyns)
{
	std::vector<std::string> sharedSyns = std::vector<std::string>(
		sharedDeclarations.begin(), sharedDeclarations.end());
	std::unordered_map<std::string, std::unordered_set<std::string>> uniqueRowMap =
		buildVectorHashRows(results, sharedSyns, thisUnsharedSyns);

	std::unordered_map<std::string, std::unordered_set<std::string>> uniqueOtherRowMap =
		buildVectorHashRows(otherResult.results, sharedSyns, otherUnsharedSyns);

	StringMap mergedResults =
		getPreMergerTable(otherResult, sharedDeclarations, thisUnsharedSyns, otherUnsharedSyns);

	for (auto& kv : uniqueRowMap) {
		if (uniqueOtherRowMap.find(kv.first) == uniqueOtherRowMap.end()) {
			continue;
		}
		std::unordered_set<std::string> otherVals = uniqueOtherRowMap.at(kv.first);
		populate(&mergedResults, sharedSyns, thisUnsharedSyns, otherUnsharedSyns, kv, otherVals);
	}

	return mergedResults;
}


StringMap QueryResult::getMergedResults(const QueryResult& otherResult)
{
	std::unordered_set<std::string> sharedDeclarations;
	for (std::pair<std::string, std::vector<std::string>> keyValue : results) {
		if (otherResult.results.find(keyValue.first) != otherResult.results.end()) {
			sharedDeclarations.insert(keyValue.first);
		}
	}

	std::vector<std::string> thisUnsharedSyns = getUnsharedColumns(results, sharedDeclarations);
	std::vector<std::string> otherUnsharedSyns = getUnsharedColumns(otherResult.results, sharedDeclarations);

	if (sharedDeclarations.empty()) {
		return getCrossJoinResults(otherResult, thisUnsharedSyns, otherUnsharedSyns);
	}

	return getInnerJoinResults(otherResult, sharedDeclarations, thisUnsharedSyns, otherUnsharedSyns);
}

QueryResult QueryResult::merge(const QueryResult& otherResult) {
	if (isNone || otherResult.isNone) {
		return QueryResult(true);  // failed result
	} else if (otherResult.results.empty()) {
		return QueryResult(results);  // merge with result with a success(bool) i.e Follows(1,2)
	} else if (results.empty()) {
		return QueryResult(otherResult.results);  // merge as a result with a success(bool)
	}
	// There are results in both QueryResults
	StringMap mergedResults = getMergedResults(otherResult);
	if (mergedResults.begin()->second.empty()) {
		return QueryResult(true);
	}
	return QueryResult(mergedResults);
}

std::vector<std::string> QueryResult::getUnsharedColumns(
	const StringMap& resMap,
	const std::unordered_set<std::string>& sharedDeclarations)
{
	std::vector<std::string> res = std::vector<std::string>();
	for (std::pair<std::string, std::vector<std::string>> keyValue : resMap) {
		if (sharedDeclarations.find(keyValue.first) == sharedDeclarations.end()) {
			res.push_back(keyValue.first);
		}
	}
	return res;
}

bool QueryResult::hasNone() {
	return isNone;
}

std::vector<std::string> QueryResult::getResult(std::string declaration) const {
	if (results.find(declaration) == results.end()) {
		return std::vector<std::string>();
	}
	std::unordered_set<std::string> uset;
	std::vector<std::string> finalResult;
	for (const std::string& s : results.at(declaration)) {
		if (uset.find(s) == uset.end()) {
			uset.insert(s);
			finalResult.push_back(s);
		}
	}
	return finalResult;
}


std::vector<std::string> QueryResult::getUnmodifiedResult(std::string declaration) const {
	if (results.find(declaration) != results.end()) {
		return results.at(declaration);
	} else {
		return std::vector<std::string>();
	}
}

std::vector<std::string> QueryResult::getColumn(std::string declaration) const {
	std::vector<std::string> unmodified = getUnmodifiedResult(declaration);
	std::vector<std::string> finalResult;
	for (std::string s : unmodified) {
		finalResult.push_back(s);
	}
	return finalResult;
}

std::unordered_set<std::string> QueryResult::getSynonyms() {
	std::unordered_set<std::string> synonyms;
	for (const auto& keyValue : results) {
		synonyms.insert(keyValue.first);
	}

	return synonyms;
}

QueryResult QueryResult::filter(const std::unordered_set<std::string>& filterSyns) {
	if (isNone) {
		return QueryResult(true);
	}
	if (filterSyns.empty()) {
		return QueryResult(isNone);
	}
	StringMap newResult;
	for (const std::string& syn : filterSyns) {
		if (results.find(syn) != results.end()) {
			newResult[syn] = results.at(syn);
		}
	}
	return QueryResult(newResult);
}

size_t QueryResult::getSize() const {
	if (isNone || results.empty()) {
		return 0;
	}
	return results.begin()->second.size();
}
