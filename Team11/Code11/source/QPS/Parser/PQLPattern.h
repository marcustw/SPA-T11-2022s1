#pragma once

#include "../Common/PQLCommon.h"
#include "../../Common/SPAException.h"

class PQLPattern {
	PQLSynonym pqlSynonym;
	PQLPatternType patternType;
	PQLReference entRef;
	PQLExpression expressionSpec;
	size_t numArgs;

	void assignPatternType(const DeclareMap& declareMap);

public:
	PQLPattern(PQLSynonym pqlSynonym,
		PQLPatternType patternType,
		PQLReference entRef,
		PQLExpression expressionSpec,
		size_t numArgs);

	PQLSynonym getSynonym() const;
	PQLPatternType getPatternType() const;
	PQLReference getEntRef() const;
	PQLExpression getExpressionSpec() const;

	void verify(const DeclareMap& declareMap);
};

