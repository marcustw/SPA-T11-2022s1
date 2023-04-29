#pragma once
#ifndef AFFECTSEVALUATOR_H
#define AFFECTSEVALUATOR_H

#include "AffectsBaseEvaluator.h"
#include "../Processor/AffectsProcessor.h"

class AffectsEvaluator : public AffectsBaseEvaluator {
public:
	AffectsEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
		const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator, AffectsProcessor* p);
};

#endif
