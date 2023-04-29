#include "PQLRelationship.h"


// Constructor
PQLRelationship::PQLRelationship(
	RelationshipType relType,
	PQLReference lhsRef,
	PQLReference rhsRef)
	: relType(relType), lhsRef(lhsRef), rhsRef(rhsRef) {}


/* Getters */
RelationshipType PQLRelationship::getRelType() const {
	return relType;
}

PQLReference PQLRelationship::getLhsRef() const {
	return lhsRef;
}

PQLReference PQLRelationship::getRhsRef() const {
	return rhsRef;
}

/*
Verifies Uses / Modifies relationship with correct types
and reassign the RelationshipType to a more specific, eg. Uses -> Uses_S or Uses_P
*/
void PQLRelationship::verifyUM(PQLReferenceType lhsRefType, std::string lhsRefString,
	RelationshipType type, const DeclareMap& declareMap)
{
	if (lhsRefType == PQLReferenceType::WILDCARD) {
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
	if (lhsRefType == PQLReferenceType::IDENT) {
		PQLRelationship::relType = type == RelationshipType::MODIFIES
			? RelationshipType::MODIFIES_P
			: RelationshipType::USES_P;
	} else if (lhsRefType == PQLReferenceType::SYNONYM &&
		(declareMap.at(lhsRefString) == EntityType::PROCEDURE || declareMap.at(lhsRefString) == EntityType::CALL)) {
		PQLRelationship::relType = type == RelationshipType::MODIFIES
			? RelationshipType::MODIFIES_P
			: RelationshipType::USES_P;
	} else {
		PQLRelationship::relType = type == RelationshipType::MODIFIES
			? RelationshipType::MODIFIES_S
			: RelationshipType::USES_S;
	}
}

void PQLRelationship::verifySemantics(RelationshipType pqlRelType, PQLReferenceType lhsRefType,
	PQLReferenceType rhsRefType, const DeclareMap& declareMap)
{
	// Verify RHS Types
	if (rhsRefType == PQLReferenceType::SYNONYM &&
		PQLCommon::VALID_UM_RHS_ENTITY_TYPE.find(pqlRelType) != PQLCommon::VALID_UM_RHS_ENTITY_TYPE.end())
	{
		EntityType rhsEntType = declareMap.at(rhsRef.second);
		if (PQLCommon::VALID_UM_RHS_ENTITY_TYPE.at(pqlRelType).find(rhsEntType)
			== PQLCommon::VALID_UM_RHS_ENTITY_TYPE.at(pqlRelType).end())
		{
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
	}

	// Verify LHS Types
	if (lhsRefType == PQLReferenceType::SYNONYM &&
		PQLCommon::VALID_UM_LHS_ENTITY_TYPE.find(pqlRelType) != PQLCommon::VALID_UM_LHS_ENTITY_TYPE.end())
	{
		EntityType rhsEntType = declareMap.at(lhsRef.second);
		if (PQLCommon::VALID_UM_LHS_ENTITY_TYPE.at(pqlRelType).find(rhsEntType)
			== PQLCommon::VALID_UM_LHS_ENTITY_TYPE.at(pqlRelType).end()) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
	}
}

/*
Verify PQLRelationship and their arg types.
If RelType == Uses/Modifies, reassign them to a more specific type, eg. Uses -> Uses_S or Uses_P
*/
void PQLRelationship::verify(const DeclareMap& declareMap) {
	PQLReferenceType lhsRefType = lhsRef.first;
	std::string lhsRefString = lhsRef.second;
	PQLReferenceType rhsRefType = rhsRef.first;
	std::string rhsRefString = rhsRef.second;

	// check lhs args validity for all RelationshipType
	if (PQLCommon::VALID_REL_ARGS.at(relType).first.find(lhsRefType) ==
		PQLCommon::VALID_REL_ARGS.at(relType).first.end()) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}
	// check rhs args validity for all RelationshipType
	if (PQLCommon::VALID_REL_ARGS.at(relType).second.find(rhsRefType) ==
		PQLCommon::VALID_REL_ARGS.at(relType).second.end()) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	if (lhsRefType == PQLReferenceType::SYNONYM &&
		declareMap.find(lhsRefString) == declareMap.end()) {
		// throw error as lhs synonym does not exist in declarations
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
	if (rhsRefType == PQLReferenceType::SYNONYM &&
		declareMap.find(rhsRefString) == declareMap.end()) {
		// throw error as rhs synonym does not exist in declarations
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}

	// Verify and Reassign this.relType
	if (relType == RelationshipType::MODIFIES || relType == RelationshipType::USES) {
		verifyUM(lhsRefType, lhsRefString, relType, declareMap);
	}

	verifySemantics(relType, lhsRefType, rhsRefType, declareMap);
}
