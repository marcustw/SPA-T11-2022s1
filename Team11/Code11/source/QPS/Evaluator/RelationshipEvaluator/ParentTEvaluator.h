#pragma once
#ifndef PARENTTEVALUATOR_H
#define PARENTTEVALUATOR_H

#include "FPEvaluator.h"

class ParentTEvaluator : public FPEvaluator {
public:
	ParentTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator);
};

#endif
