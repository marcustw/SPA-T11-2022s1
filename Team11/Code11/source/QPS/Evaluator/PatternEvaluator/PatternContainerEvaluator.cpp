#include "PatternContainerEvaluator.h"

PatternContainerEvaluator::PatternContainerEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi) :
	PatternEvaluator(pattern, pkbQueryApi) {
}

QueryResult PatternContainerEvaluator::evaluateLhsIdent(const std::vector<std::string>& containers) {
	std::vector<std::string> possibleContainers;

	for (std::string s : containers) {
		int stmtNum = stoi(s);
		std::vector<std::string> condVars = pkbQueryApi.getVarLstFromStmtIdx(stmtNum);

		if (std::find(condVars.begin(), condVars.end(), entRef.second) != condVars.end()) {
			possibleContainers.push_back(s);
		}
	}

	if (possibleContainers.size() == 0) {
		return QueryResult(true);
	}

	StringMap map;
	map[synonym] = possibleContainers;
	return QueryResult(map);
}

QueryResult PatternContainerEvaluator::evaluateLhsSynonym(const std::vector<std::string>& containers) {
	std::vector<std::string> condVars;
	std::vector<std::string> possibleContainers;

	for (std::string s : containers) {
		int stmtNum = stoi(s);
		std::vector<std::string> tempVars = pkbQueryApi.getVarLstFromStmtIdx(stmtNum);

		for (std::string vars : tempVars) {
			condVars.push_back(vars);
			possibleContainers.push_back(s);
		}
	}

	if (condVars.size() == 0) {
		return QueryResult(true);
	}

	StringMap map;
	map[synonym] = possibleContainers;
	map[entRef.second] = condVars;
	return QueryResult(map);
}

QueryResult PatternContainerEvaluator::evaluateLhsWildcard(const std::vector<std::string>& containers) {
	std::vector<std::string> possibleContainers;

	for (std::string s : containers) {
		int stmtNum = stoi(s);
		std::vector<std::string> condVars = pkbQueryApi.getVarLstFromStmtIdx(stmtNum);

		if (condVars.size() > 0) {
			possibleContainers.push_back(s);
		}
	}

	StringMap map;
	map[synonym] = possibleContainers;
	return QueryResult(map);
}

QueryResult PatternContainerEvaluator::evaluate(const std::vector<std::string>& containers) {
	if (containers.size() == 0) {
		return QueryResult(true);
	}

	switch (entRef.first) {
	case PQLReferenceType::IDENT:
		return evaluateLhsIdent(containers);
	case PQLReferenceType::SYNONYM:
		return evaluateLhsSynonym(containers);
	case PQLReferenceType::WILDCARD:
		return evaluateLhsWildcard(containers);
	default:
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		break;
	}
}
