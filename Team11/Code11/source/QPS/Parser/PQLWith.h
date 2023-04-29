#pragma once

#include "../Common/PQLCommon.h"
#include "../../Common/SPAException.h"

class PQLWith {
	PQLReference lhs;
	PQLReference rhs;

	PQLReferenceType getAttributeType(const PQLReference& pqlRef,
		const DeclareMap& declareMap) const;
public:
	PQLWith(PQLReference lhs, PQLReference rhs);

	PQLReference getLhsRef() const;
	PQLReference getRhsRef() const;

	void verify(const DeclareMap& declareMap);
};
