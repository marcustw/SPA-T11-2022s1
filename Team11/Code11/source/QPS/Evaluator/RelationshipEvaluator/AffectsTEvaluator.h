#pragma once
#ifndef AFFECTSTEVALUATOR_H
#define AFFECTSTEVALUATOR_H

#include "AffectsBaseEvaluator.h"
#include "../Processor/AffectsTProcessor.h"

class AffectsTEvaluator : public AffectsBaseEvaluator {
public:
	AffectsTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
		const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator, AffectsTProcessor* p);
};

#endif
