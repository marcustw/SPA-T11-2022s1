#pragma once

#include <unordered_map>
#include <unordered_set>
#include "../Common/PQLCommon.h"
#include "../../Common/SPAException.h"
#include "../../Common/Types.h"

class PQLRelationship {
    RelationshipType relType;
    PQLReference lhsRef;
    PQLReference rhsRef;

    void verifyUM(PQLReferenceType lhsRefType, std::string lhsRefString, RelationshipType type,
        const DeclareMap& declareMap);

    void verifySemantics(RelationshipType relType, PQLReferenceType lhsRefType,
        PQLReferenceType rhsRefType, const DeclareMap& declareMap);

public:
    // Declare methods, PQLRef can refer to either 'stmtRef' or 'entRef'
    PQLRelationship(RelationshipType relType,
        PQLReference lhsRef, PQLReference rhsRef);

    RelationshipType getRelType() const;
    PQLReference getLhsRef() const;
    PQLReference getRhsRef() const;

    void verify(const DeclareMap& declareMap);
};
