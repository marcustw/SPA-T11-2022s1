#pragma once
#ifndef PATTERNWEVALUATOR_H
#define PATTERNWEVALUATOR_H

#include "PatternContainerEvaluator.h"

class PatternWEvaluator : public PatternContainerEvaluator {
public:
	PatternWEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi);
	QueryResult evaluate() override;
};

#endif
