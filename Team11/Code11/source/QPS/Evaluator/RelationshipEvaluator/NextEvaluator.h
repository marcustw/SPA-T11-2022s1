#pragma once
#ifndef NEXTEVALUATOR_H
#define NEXTEVALUATOR_H


#include "RelationshipEvaluator.h"

class NextEvaluator : public RelationshipEvaluator {
public:
    NextEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
        const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
        const GetAllEvaluator& generator);

    QueryResult evaluate() override;
private:
    QueryResult evaluateDoubleInteger();
    QueryResult evaluateWildCardsAndSynonyms();
    QueryResult evaluateInteger(const std::string& refString, const std::string& otherString,
        const PQLReferenceType& otherRef, const std::vector<std::string>& vector);
};

#endif
