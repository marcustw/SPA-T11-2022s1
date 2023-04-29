#pragma once
#ifndef CALLSEVALUATOR_H
#define CALLSEVALUATOR_H

#include "CallsBaseEvaluator.h"

class CallsEvaluator : public CallsBaseEvaluator {
public:
	CallsEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator);
};

#endif
