#include "PatternAEvaluator.h"

PatternAEvaluator::PatternAEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi) :
	PatternEvaluator(pattern, pkbQueryApi) {
}

std::pair<std::vector<std::string>, std::vector<std::string>> PatternAEvaluator::getPossibleMixedAssigns(
	const std::vector<std::string>& assignments, const std::string& actualString)
{
	std::vector<std::string> variableVector;
	std::vector<std::string> filteredAssigns;
	for (std::string s : assignments) {
		int assignStmtNum = stoi(s);
		std::vector<std::string> expressionVars = pkbQueryApi.getExpressionLstFromStmtIdx(assignStmtNum);
		if (std::find(expressionVars.begin(), expressionVars.end(), actualString) != expressionVars.end()) {
			std::vector<std::string> lhsAssign = pkbQueryApi.getAssignmentFromStmtIdx(assignStmtNum);
			filteredAssigns.push_back(s);
			variableVector.push_back(lhsAssign.at(0));
		}
	}
	return std::make_pair(filteredAssigns, variableVector);
}

std::pair<std::vector<std::string>, std::vector<std::string>> PatternAEvaluator::getPossibleFullAssigns(
	const std::vector<std::string>& assignments, const std::string& actualString)
{
	std::vector<std::string> variableVector;
	std::vector<std::string> filteredAssigns;
	std::vector<std::string> fullExpressionStmts = pkbQueryApi.getStmtLstFromExactExpression(actualString);
	for (std::string s : assignments) {
		if (std::find(fullExpressionStmts.begin(), fullExpressionStmts.end(), s) != fullExpressionStmts.end()) {
			int assignStmtNum = stoi(s);
			std::vector<std::string> lhsAssign = pkbQueryApi.getAssignmentFromStmtIdx(assignStmtNum);
			filteredAssigns.push_back(s);
			variableVector.push_back(lhsAssign.at(0));
		}
	}
	return std::make_pair(filteredAssigns, variableVector);
}

QueryResult PatternAEvaluator::evaluatePossibleAssignments(const std::vector<std::string> assignments) {
	std::vector<std::string> filteredAssigns;
	StringMap map;
	std::string actualString = expressionSpec.second;
	std::pair<std::vector<std::string>, std::vector<std::string>> resPair;
	if (expressionSpec.first == PQLExpressionType::WILDCARD) {
		filteredAssigns = assignments;
	} else {
		resPair = expressionSpec.first == PQLExpressionType::MIXED
				? getPossibleMixedAssigns(assignments, actualString)
				: getPossibleFullAssigns(assignments, actualString);
		filteredAssigns = resPair.first;
	}

	if (filteredAssigns.empty()) {
		return QueryResult(true);
	}

	map[synonym] = filteredAssigns;
	return QueryResult(map);
}

QueryResult PatternAEvaluator::evaluateLhsIdent(const std::vector<std::string>& assignments) {
	std::vector<std::string> possibleAssigns;
	std::string actualString = expressionSpec.second;

	for (std::string s : assignments) {
		int assignStmtNum = stoi(s);
		std::vector<std::string> lhsAssign = pkbQueryApi.getAssignmentFromStmtIdx(assignStmtNum);
		if (lhsAssign.at(0) == entRef.second) {
			possibleAssigns.push_back(s);
		}
	}

	if (possibleAssigns.empty()) {
		return QueryResult(true);
	}

	return evaluatePossibleAssignments(possibleAssigns);
}

QueryResult PatternAEvaluator::evaluateLhsSynonym(const std::vector<std::string>& assignments) {
	StringMap map;
	std::string actualString = expressionSpec.second;
	std::pair<std::vector<std::string>, std::vector<std::string>> resPair;
	if (expressionSpec.first == PQLExpressionType::WILDCARD) {
		std::vector<std::string> variableVector;
		for (std::string s : assignments) {
			int assignStmtNum = stoi(s);
			std::vector<std::string> lhsAssign = pkbQueryApi.getAssignmentFromStmtIdx(assignStmtNum);
			variableVector.push_back(lhsAssign.at(0));
		}
		resPair = std::make_pair(assignments, variableVector);
	} else {
		resPair = expressionSpec.first == PQLExpressionType::MIXED
			? getPossibleMixedAssigns(assignments, actualString)
			: getPossibleFullAssigns(assignments, actualString);
	}
	std::vector<std::string> possibleAssigns = resPair.first;
	if (possibleAssigns.empty()) {
		return QueryResult(true);
	}

	map[synonym] = possibleAssigns;
	map[entRef.second] = resPair.second;
	return QueryResult(map);
}


QueryResult PatternAEvaluator::evaluate() {
	std::vector<std::string> assignments = pkbQueryApi.getAllAssignments();
	if (assignments.size() == 0) {
		return QueryResult(true);
	}

	switch (entRef.first) {
	case PQLReferenceType::IDENT:
		return evaluateLhsIdent(assignments);
	case PQLReferenceType::SYNONYM:
		return evaluateLhsSynonym(assignments);
	case PQLReferenceType::WILDCARD:
		return evaluatePossibleAssignments(assignments);
	default:
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		break;
	}
}
