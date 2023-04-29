#include "PQLPattern.h"

// Constructor
PQLPattern::PQLPattern(PQLSynonym pqlSynonym,
	PQLPatternType patternType,
	PQLReference entRef,
	PQLExpression expressionSpec, size_t numArgs):
	pqlSynonym(pqlSynonym), patternType(patternType), entRef(entRef), expressionSpec(expressionSpec),
	numArgs(numArgs) {}


/* Getters */
PQLSynonym PQLPattern::getSynonym() const {
	return pqlSynonym;
}

PQLPatternType PQLPattern::getPatternType() const {
	return patternType;
}

PQLReference PQLPattern::getEntRef() const {
	return entRef;
}

PQLExpression PQLPattern::getExpressionSpec() const {
	return expressionSpec;
}

void PQLPattern::assignPatternType(const DeclareMap& declareMap) {
	if (declareMap.find(pqlSynonym) == declareMap.end()) {
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
	EntityType patternEntityType = declareMap.at(pqlSynonym);
	switch (patternEntityType) {
	case EntityType::ASSIGN:
		PQLPattern::patternType = PQLPatternType::PATTERN_A;
		if (numArgs == 3) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
		break;
	case EntityType::WHILE:
		PQLPattern::patternType = PQLPatternType::PATTERN_W;
		if (numArgs == 3) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
		break;
	case EntityType::IF:
		PQLPattern::patternType = PQLPatternType::PATTERN_I;
		if (numArgs != 3) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
		break;
	default:
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
}

void PQLPattern::verify(const DeclareMap& declareMap) {
	assignPatternType(declareMap);

	if (declareMap.find(pqlSynonym) == declareMap.end() ||
		declareMap.at(pqlSynonym) !=
		PQLCommon::VALID_PATTERN_ENTITY_TYPE.at(patternType))
	{
		// throw error as synonym does not exist in declarations or is of wrong type
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}

	if (entRef.first == PQLReferenceType::SYNONYM &&
		declareMap.find(entRef.second) == declareMap.end())
	{
		// throw error as entRef synonym does not exist in declarations
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}

	if (PQLPattern::patternType != PQLPatternType::PATTERN_A &&
		expressionSpec.first != PQLExpressionType::WILDCARD) {	  // only in Pattern_A, 2nd arg can be expr
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}

	if (entRef.first == PQLReferenceType::SYNONYM) {
		if (declareMap.find(entRef.second) == declareMap.end()) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
		if (declareMap.at(entRef.second) != EntityType::VARIABLE) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
	}
}
