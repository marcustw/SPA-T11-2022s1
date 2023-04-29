#pragma once
#ifndef CALLSBASEEVALUATOR_H
#define CALLSBASEEVALUATOR_H

#include "RelationshipEvaluator.h"
#include "../../../Common/Types.h"


class CallsBaseEvaluator : public RelationshipEvaluator {
public:
    CallsBaseEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, RelationshipType rsType,
        const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator);
    QueryResult evaluate() override;

protected:
    QueryResult evaluateTwoProcNames();
    QueryResult evaluateWildCardsAndSynonyms();
    QueryResult evaluateProcName(std::string refString, std::string otherString,
        const PQLReferenceType& otherRef, const std::vector<std::string>& vector);
};

#endif
