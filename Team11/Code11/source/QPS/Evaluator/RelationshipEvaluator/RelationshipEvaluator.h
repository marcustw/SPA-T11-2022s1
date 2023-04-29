#pragma once
#ifndef RELATIONSHIPEVALUATOR_H
#define RELATIONSHIPEVALUATOR_H

#include <string>
#include <unordered_set>

#include "../../../Common/SPAException.h"
#include "../../../PKB/PKBQueryAPI.h"
#include "../../Common/PQLCommon.h"
#include "../../Parser/PQLQueryObject.h"
#include "../GetAllEvaluator.h"
#include "../QueryResult.h"
#include "../BaseEvaluator.h"

class RelationshipEvaluator : public BaseEvaluator {
protected:
    PQLReferenceType lhsRef;
    std::string lhsRefString;
    PQLReferenceType rhsRef;
    std::string rhsRefString;
    DeclareMap declareMap;
    GetAllEvaluator generator;
    RelationshipType relationshipType;

public:
    RelationshipEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
        const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator, RelationshipType relType);

    bool isStatementSynonym(EntityType synonymEntityType);
    void assertSynonymsAreStatement();

    std::unordered_set<std::string> getSynonyms() const override;

    virtual std::string toString() const;

    int priority() const override;
};

#endif
