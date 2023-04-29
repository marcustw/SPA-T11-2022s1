#include "RelationshipEvaluator.h"

RelationshipEvaluator::RelationshipEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
    const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
    const GetAllEvaluator& generator, const RelationshipType relType)
    : BaseEvaluator(pkbQueryApi), generator(generator)
{
    RelationshipEvaluator::declareMap = declareMap;
    RelationshipEvaluator::lhsRef = lhsRef.first;
    RelationshipEvaluator::rhsRef = rhsRef.first;
    RelationshipEvaluator::lhsRefString = lhsRef.second;
    RelationshipEvaluator::rhsRefString = rhsRef.second;
    RelationshipEvaluator::relationshipType = relType;
}

bool RelationshipEvaluator::isStatementSynonym(EntityType synonymEntityType) {
    return !(synonymEntityType == EntityType::VARIABLE ||
        synonymEntityType == EntityType::CONSTANT ||
        synonymEntityType == EntityType::PROCEDURE);
}

void RelationshipEvaluator::assertSynonymsAreStatement() {
    if (lhsRef == PQLReferenceType::SYNONYM) {
        if (!isStatementSynonym(declareMap.at(lhsRefString))) {
            throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
        }
    }

    if (rhsRef == PQLReferenceType::SYNONYM) {
        if (!isStatementSynonym(declareMap.at(rhsRefString))) {
            throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
        }
    }
}

std::unordered_set<std::string> RelationshipEvaluator::getSynonyms() const {
    std::unordered_set<std::string> syns;
    if (lhsRef == PQLReferenceType::SYNONYM) {
        syns.insert(lhsRefString);
    }
    if (rhsRef == PQLReferenceType::SYNONYM) {
        syns.insert(rhsRefString);
    }
    return syns;
}

std::string RelationshipEvaluator::toString() const {
    std::string relString = "";
    for (const auto& rel : PQLCommon::RELATIONSHIP_MAP) {
        if (rel.second == relationshipType) {
            relString = rel.first;
            break;
        }
    }
    return relString + PQLSyntax::LEFT_BRACKET + lhsRefString + PQLSyntax::COMMA
        + rhsRefString + PQLSyntax::RIGHT_BRACKET;
}

int RelationshipEvaluator::priority() const {
    switch (relationshipType) {
    case RelationshipType::FOLLOWS:
    case RelationshipType::MODIFIES:
        return PQLCommon::MODIFIES_FOLLOWS_BASE_PRIORITY + getSynonyms().size();
    case RelationshipType::AFFECTS:
        return PQLCommon::AFFECTS_PRIORITY;
    case RelationshipType::AFFECTS_T:
    case RelationshipType::NEXT_T:
        return PQLCommon::AFFECTST_NEXTT_PRIORITY;
    default:
        break;
    }
    return PQLCommon::PATTERN_WILDCARD_AND_REL_BASE_PRIORITY + getSynonyms().size();
}
