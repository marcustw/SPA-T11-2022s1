#pragma once
#ifndef FOLLOWSTEVALUATOR_H
#define FOLLOWSTEVALUATOR_H

#include "FPEvaluator.h"

class FollowsTEvaluator : public FPEvaluator {
public:
	FollowsTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator);
};

#endif
