#pragma once
#ifndef FOLLOWSEVALUATOR_H
#define FOLLOWSEVALUATOR_H

#include "FPEvaluator.h"

class FollowsEvaluator : public FPEvaluator {
public:
	FollowsEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
		const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator);
};

#endif
