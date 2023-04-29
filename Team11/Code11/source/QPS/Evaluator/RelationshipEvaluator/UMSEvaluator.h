#pragma once
#ifndef UMSEVALUATOR_H
#define UMSEVALUATOR_H

#include "RelationshipEvaluator.h"


class UMSEvaluator : public RelationshipEvaluator {
private:
	QueryResult evaluateLhsSynonym(const StringMap& umS);
	QueryResult evaluateLhsInteger();

protected:
	QueryResult evaluate(const StringMap& umSTable);

public:
	UMSEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
		const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator, RelationshipType pqlRelType);
};

#endif
