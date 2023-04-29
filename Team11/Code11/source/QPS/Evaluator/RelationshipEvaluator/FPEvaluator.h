#pragma once
#ifndef FPEVALUATOR_H
#define FPEVALUATOR_H

#include "RelationshipEvaluator.h"

class FPEvaluator : public RelationshipEvaluator {
	QueryResult evaluateLhsIntRhsInt();
	QueryResult evaluateLhsSynRhsSyn();
	QueryResult evaluateLhsWCRhsWC();
	QueryResult evaluateLhsInt();
	QueryResult evaluateLhsSyn();
	QueryResult evaluateLhsWC();

public:
	FPEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
		const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator, RelationshipType relationshipType);

	QueryResult evaluate() override;
};

#endif
