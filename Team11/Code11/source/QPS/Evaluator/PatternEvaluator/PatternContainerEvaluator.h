#pragma once
#ifndef PATTERNCONTAINEREVALUATOR_H
#define PATTERNCONTAINEREVALUATOR_H

#include "PatternEvaluator.h"

class PatternContainerEvaluator : public PatternEvaluator {
	QueryResult evaluateLhsIdent(const std::vector<std::string>& containers);
	QueryResult evaluateLhsSynonym(const std::vector<std::string>& containers);
	QueryResult evaluateLhsWildcard(const std::vector<std::string>& containers);

protected:
	QueryResult evaluate(const std::vector<std::string>& containers);
public:
	PatternContainerEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi);
	virtual QueryResult evaluate() = 0;
};

#endif
