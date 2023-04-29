#include "UMSEvaluator.h"


UMSEvaluator::UMSEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
	const GetAllEvaluator& generator, RelationshipType relationshipType) :
	RelationshipEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, relationshipType) {
}


QueryResult UMSEvaluator::evaluate(const StringMap& umSTable) {
	QueryResult result = QueryResult(false);

	switch (lhsRef) {
	case PQLReferenceType::SYNONYM:
		result = UMSEvaluator::evaluateLhsSynonym(umSTable);
		break;
	case PQLReferenceType::INTEGER:
		result = UMSEvaluator::evaluateLhsInteger();
		break;
	default:
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		break;
	}
	return result;
}


QueryResult UMSEvaluator::evaluateLhsSynonym(const StringMap& umSTable)
{
	std::vector<std::string> stmtIndexes = std::vector<std::string>();
	std::vector<std::string> variables = std::vector<std::string>();
	EntityType synType = declareMap.at(lhsRefString);
	std::vector<std::string> allSynTypes = generator.getAllStmt(synType);
	std::unordered_set<std::string> allSynType;
	for (std::string& syns : allSynTypes) {
		allSynType.insert(syns);
	}
	for (std::pair<std::string, std::vector<std::string>> keyValue : umSTable) {
		if (allSynType.find(keyValue.first) != allSynType.end()) {
			for (std::string& val : keyValue.second) {
				stmtIndexes.push_back(keyValue.first);
				variables.push_back(val);
			}
		}
	}

	if (stmtIndexes.empty()) {
		return QueryResult(true);
	}
	StringMap resultsMap;
	std::vector<std::string> stmts = std::vector<std::string>();
	switch (rhsRef) {
		// All variables
	case PQLReferenceType::WILDCARD:
		resultsMap[lhsRefString] = stmtIndexes;
		break;
		// Specific variable
	case PQLReferenceType::SYNONYM:
		resultsMap[lhsRefString] = stmtIndexes;
		resultsMap[rhsRefString] = variables;
		break;
		// Specific variable
	case PQLReferenceType::IDENT:
		for (size_t i = 0; i < variables.size(); i++) {
			if (variables[i] == rhsRefString) {
				stmts.push_back(stmtIndexes[i]);
			}
		}
		resultsMap[lhsRefString] = stmts;
		break;
	default:
		break;
	}

	QueryResult res = QueryResult(resultsMap);
	return res;
}

QueryResult UMSEvaluator::evaluateLhsInteger() {
	std::vector<std::string> usedVars =
		pkbQueryApi.getRelationshipRightArg(relationshipType, stoi(lhsRefString));
	if (usedVars.empty()) {
		return QueryResult(true);
	}

	StringMap resultsMap;
	bool found = false;
	switch (rhsRef) {
	case PQLReferenceType::WILDCARD:
		return QueryResult(usedVars.empty());
	case PQLReferenceType::IDENT:
		for (std::string& var : usedVars) {
			if (var == rhsRefString) {
				found = true;
				break;
			}
		}
		if (!found) {
			// result not found, isNone = true
			return QueryResult(true);
		}
		resultsMap[rhsRefString] = usedVars;
		break;
	case PQLReferenceType::SYNONYM:
		resultsMap[rhsRefString] = usedVars;
		break;
	default:
		break;
	}

	QueryResult res = QueryResult(resultsMap);
	return res;
}
