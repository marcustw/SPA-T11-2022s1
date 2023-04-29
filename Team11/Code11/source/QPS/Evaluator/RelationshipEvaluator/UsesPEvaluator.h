#pragma once

#ifndef USESPEVALUATOR_H
#define USESPEVALUATOR_H

#include "UMPEvaluator.h"


class UsesPEvaluator : public UMPEvaluator {
public:
	UsesPEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
		const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
		const GetAllEvaluator& generator);

	QueryResult evaluate() override;
};

#endif
