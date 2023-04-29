#pragma once
#ifndef NEXTTEVALUATOR_H
#define NEXTTEVALUATOR_H
#include <stack>

#include "RelationshipEvaluator.h"
#include "../../Common/QPSCache.h"
#include "../Processor/NextTProcessor.h"

class PKBQueryAPI;

class NextTEvaluator : public RelationshipEvaluator {
public:
	NextTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator, NextTProcessor* processor);

	QueryResult evaluate() override;
private:
	QPSCache* cache;
	NextTProcessor* processor;

	QueryResult evaluateDoubleInteger();
	QueryResult evaluateSameSynonym();
	QueryResult evaluateWildCardsAndSynonyms();
	QueryResult evaluateLeftIntegerRightWildcardOrSynonym();
	QueryResult evaluateLeftWildcardOrSynonymRightInteger();
	QueryResult evaluateDoubleWildcard();
};

#endif
