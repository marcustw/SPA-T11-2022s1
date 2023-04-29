#pragma once
#ifndef USESSEVALUATOR_H
#define USESSEVALUATOR_H

#include "UMSEvaluator.h"


class UsesSEvaluator : public UMSEvaluator {
public:
	UsesSEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator);

	QueryResult evaluate() override;
};

#endif
