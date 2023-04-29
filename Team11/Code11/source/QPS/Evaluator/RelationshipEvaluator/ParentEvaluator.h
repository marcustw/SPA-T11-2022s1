#pragma once
#ifndef PARENTEVALUATOR_H
#define PARENTEVALUATOR_H

#include "FPEvaluator.h"

class ParentEvaluator : public FPEvaluator {
public:
	ParentEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator);
};

#endif
