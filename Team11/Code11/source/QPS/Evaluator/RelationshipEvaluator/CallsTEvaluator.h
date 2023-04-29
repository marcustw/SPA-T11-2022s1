#pragma once
#ifndef CALLSTEVALUATOR_H
#define CALLSTEVALUATOR_H

#include "CallsBaseEvaluator.h"

class CallsTEvaluator : public CallsBaseEvaluator {
public:
	CallsTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator);
};

#endif
