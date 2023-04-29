#pragma once
#ifndef MODIFIESSEVALUATOR_H
#define MODIFIESSEVALUATOR_H

#include "UMSEvaluator.h"

class ModifiesSEvaluator : public UMSEvaluator {
public:
	ModifiesSEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator);

	QueryResult evaluate() override;
};

#endif
