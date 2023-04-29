#include "PQLWith.h"


PQLWith::PQLWith(PQLReference lhs, PQLReference rhs): lhs(lhs), rhs(rhs) {}

PQLReference PQLWith::getLhsRef() const {
	return lhs;
}

PQLReference PQLWith::getRhsRef() const {
	return rhs;
}

PQLReferenceType PQLWith::getAttributeType(const PQLReference& pqlRef, const DeclareMap& declareMap) const {
	if (PQLCommon::WITH_ATTRIBUTE_TYPES.find(pqlRef.first) != PQLCommon::WITH_ATTRIBUTE_TYPES.end()) {
		if (declareMap.find(pqlRef.second) == declareMap.end()) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
		EntityType synEntType = declareMap.at(pqlRef.second);
		if (PQLCommon::VALID_WITH_ATTRIBUTES.find(synEntType) == PQLCommon::VALID_WITH_ATTRIBUTES.end()) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
		if (PQLCommon::VALID_WITH_ATTRIBUTES.at(synEntType).count(pqlRef.first) == 0) {
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
	}
	return PQLCommon::ATTRIBUTE_REF_TYPE.at(pqlRef.first);
}

void PQLWith::verify(const DeclareMap& declareMap) {
	PQLReferenceType lhsAttributeType = getAttributeType(lhs, declareMap);
	PQLReferenceType rhsAttributeType = getAttributeType(rhs, declareMap);
	if (lhsAttributeType != rhsAttributeType) {
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
}

