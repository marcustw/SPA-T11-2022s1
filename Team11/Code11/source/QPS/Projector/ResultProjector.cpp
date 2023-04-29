#include "ResultProjector.h"

ResultProjector::ResultProjector(PKBQueryAPI* pkbQueryApi,
	const DeclareMap& declareMap):
	pkbQueryApi(pkbQueryApi), declareMap(declareMap) {}

std::list<std::string> ResultProjector::projectResult(QueryResult* queryResult,
	std::vector<PQLReference> pqlRefs, bool isSelectBoolean)
{
	if (isSelectBoolean) {
		std::string value = queryResult->hasNone() ? "FALSE" : "TRUE";
		std::list<std::string> result;
		result.push_back(value);
		return result;
	}

	if (queryResult->hasNone() || queryResult->getSize() == 0) {
		return std::list<std::string>();
	}

	std::vector<std::string> selectSynonym;
	for (PQLReference& pqlRef : pqlRefs) {
		// handles for duplicated output
		selectSynonym.push_back(pqlRef.second);
	}

	std::unordered_map<std::string, std::unordered_set<std::string>> hashRows =
		queryResult->getHashRows(selectSynonym);

	std::unordered_set<std::string> result;

	// The keys of hashRows are the results
	for (const auto& row : hashRows) {
		std::vector<std::string> r = PQLCommon::getSynonymVectorFromHash(row.first);
		std::string rowStr = "";
		for (size_t i = 0; i < pqlRefs.size(); i++) {
			rowStr += (i == 0 ? "" : PQLSyntax::SPACE) +
				project(pqlRefs[i], r[i]);
		}
		result.insert(rowStr);
	}

	return std::list<std::string>(result.begin(), result.end());
}


std::string ResultProjector::getProcedureName(PQLReference attr, const std::string& syn) {
	std::string var;
	EntityType attrEntType = declareMap.at(attr.second);
	switch (attrEntType) {
	case EntityType::PROCEDURE:
		var = syn;
		break;
	case EntityType::CALL:
		var = pkbQueryApi->getAttributeName(attrEntType, stoi(syn));
		break;
	}
	if (var.empty()) {
		return syn;
	}
	return var;
}

std::string ResultProjector::getVariableName(PQLReference attr, const std::string& syn) {
	std::string var;
	EntityType attrEntType = declareMap.at(attr.second);
	switch (attrEntType) {
	case EntityType::PRINT:
		var = pkbQueryApi->getAttributeName(attrEntType, stoi(syn));
		break;
	case EntityType::READ:
		var = pkbQueryApi->getAttributeName(attrEntType, stoi(syn));
		break;
	case EntityType::VARIABLE:
		var = syn;
		break;
	}
	if (var.empty()) {
		return syn;
	}
	return var;
}

std::string ResultProjector::project(PQLReference attr,
	const std::string& syn) {
	switch (attr.first) {
	case PQLReferenceType::VAR_NAME:
		return getVariableName(attr, syn);
	case PQLReferenceType::PROC_NAME:
		return getProcedureName(attr, syn);
	default:
		return syn;
	}
}
