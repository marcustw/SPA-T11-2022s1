#pragma once
#ifndef PATTERNEVALUATOR_H
#define PATTERNEVALUATOR_H

#include "../../../Common/SPAException.h"
#include "../../../PKB/PKBQueryAPI.h"
#include "../../Common/PQLCommon.h"
#include "../../Parser/PQLPattern.h"
#include "../QueryResult.h"
#include "../BaseEvaluator.h"

class PatternEvaluator : public BaseEvaluator {
protected:
	std::string synonym;
	PQLReference entRef;
	PQLExpression expressionSpec;
	PQLPatternType patternType;
public:
	PatternEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi);
	virtual QueryResult evaluate() = 0;
	std::unordered_set<std::string> getSynonyms() const override;

	std::string toString() const override;

	int priority() const override;
};

#endif
