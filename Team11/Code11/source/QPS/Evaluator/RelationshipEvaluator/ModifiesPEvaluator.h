#pragma once
#ifndef MODIFIESPEVALUATOR_H
#define MODIFIESPEVALUATOR_H

#include "UMPEvaluator.h"

class ModifiesPEvaluator : public UMPEvaluator {
public:
	ModifiesPEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator);

	QueryResult evaluate() override;
};

#endif
