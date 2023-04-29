#pragma once
#ifndef PATTERNAEVALUATOR_H
#define PATTERNAEVALUATOR_H

#include "PatternEvaluator.h"

class PatternAEvaluator : public PatternEvaluator {
	QueryResult evaluateLhsIdent(const std::vector<std::string>& assignments);
	QueryResult evaluateLhsSynonym(const std::vector<std::string>& assignments);
	QueryResult evaluatePossibleAssignments(const std::vector<std::string> assignments);

	std::pair<std::vector<std::string>, std::vector<std::string>> getPossibleMixedAssigns(
		const std::vector<std::string>& assignments, const std::string& actualString);
	std::pair<std::vector<std::string>, std::vector<std::string>> getPossibleFullAssigns(
		const std::vector<std::string>& assignments, const std::string& actualString);

public:
	PatternAEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi);
	QueryResult evaluate() override;
};

#endif
