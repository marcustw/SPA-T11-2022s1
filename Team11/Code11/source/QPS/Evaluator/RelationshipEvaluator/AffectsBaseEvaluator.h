#pragma once
#ifndef AFFECTSBASEEVALUATOR_H
#define AFFECTSBASEEVALUATOR_H

#include "RelationshipEvaluator.h"
#include "../../Common/QPSCache.h"
#include "../Processor/AffectsBaseProcessor.h"

class AffectsBaseEvaluator : public RelationshipEvaluator {
public:
	AffectsBaseEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
		const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator, RelationshipType relType,
		AffectsBaseProcessor* processor);
	QueryResult evaluate() override;

private:
	AffectsBaseProcessor* processor;
	QueryResult evaluateLhsIntRhsInt();
	QueryResult evaluateLhsSynRhsInt();
	QueryResult evaluateLhsWCRhsInt();
	QueryResult evaluateLhsInt();
	QueryResult evaluateLhsSyn();
	QueryResult evaluateLhsWC();
	bool exceedArgsBounds();
};

#endif
