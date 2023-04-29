#include "UMPEvaluator.h"

UMPEvaluator::UMPEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
	const GetAllEvaluator& generator, const RelationshipType relationshipType) :
	RelationshipEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, relationshipType) {
}
/*
Modifies_P happens in the following procedure:
- procedure contains modifies(s, v)
- calls another procedure that contains modifies(s, v)
*/
QueryResult UMPEvaluator::evaluate(const StringMap& umPTable) {
	QueryResult result = QueryResult(true);
	switch (lhsRef) {
	case PQLReferenceType::SYNONYM:
		result = UMPEvaluator::evaluateLhsSynonym(umPTable);
		break;
	case PQLReferenceType::IDENT:
		result = UMPEvaluator::evaluateLhsIdent(umPTable);
		break;
	default:
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		break;
	}

	return result;
}

QueryResult UMPEvaluator::evaluateLhsSynonym(const std::vector<std::string>& stmts,
	const std::vector<std::string>& variables)
{
	StringMap resultsMap;
	std::vector<std::string> indexes = std::vector<std::string>();
	switch (rhsRef) {
	case PQLReferenceType::WILDCARD:
		resultsMap[lhsRefString] = stmts;
		break;
	case PQLReferenceType::SYNONYM:
		resultsMap[lhsRefString] = stmts;
		resultsMap[rhsRefString] = variables;
		break;
	case PQLReferenceType::IDENT:
		for (size_t i = 0; i < variables.size(); i++) {
			if (variables[i] == rhsRefString) {
				indexes.push_back(stmts[i]);
			}
		}
		resultsMap[lhsRefString] = indexes;
		break;
	default:
		break;
	}
	return QueryResult(resultsMap);
}


QueryResult UMPEvaluator::evaluateLhsSynonym(
	const StringMap& umPTable)
{
	std::vector<std::string> procNames = std::vector<std::string>();
	std::vector<std::string> variables = std::vector<std::string>();
	std::vector<std::string> callsIndexes = std::vector<std::string>();
	std::vector<std::string> callsVariables = std::vector<std::string>();
	EntityType synType = declareMap.at(lhsRefString);
	for (std::pair<std::string, std::vector<std::string>> keyValue : umPTable) {
		std::vector<std::string> calls = pkbQueryApi.getStmtLstFromProcCall(keyValue.first);
		for (std::string& val : keyValue.second) {
			procNames.push_back(keyValue.first);
			variables.push_back(val);
			for (std::string& c : calls) {
				callsIndexes.push_back(c);
				callsVariables.push_back(val);
			}
		}
	}
	if (procNames.empty()) {
		return QueryResult(true);
	}
	if (synType == EntityType::CALL) {
		return evaluateLhsSynonym(callsIndexes, callsVariables);
	} else {
		return evaluateLhsSynonym(procNames, variables);
	}
}

QueryResult UMPEvaluator::evaluateLhsIdent(
	const StringMap& umPTable)
{
	if (umPTable.find(lhsRefString) == umPTable.end()) {
		return QueryResult(true);
	}
	std::vector<std::string> modifiedVars = umPTable.at(lhsRefString);

	StringMap resultsMap;
	bool found = false;

	switch (rhsRef) {
	case PQLReferenceType::WILDCARD:
		return QueryResult(modifiedVars.empty());
	case PQLReferenceType::IDENT:
		for (std::string& var : modifiedVars) {
			if (var == rhsRefString) {
				found = true;
				break;
			}
		}
		if (!found) {
			// result not found, isNone = true
			return QueryResult(true);
		}
		resultsMap[rhsRefString] = modifiedVars;
		break;
	case PQLReferenceType::SYNONYM:
		resultsMap[rhsRefString] = modifiedVars;
		break;
	default:
		break;
	}

	return QueryResult(resultsMap);
}
