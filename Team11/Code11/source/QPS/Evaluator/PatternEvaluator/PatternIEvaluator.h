#pragma once
#ifndef PATTERNIEVALUATOR_H
#define PATTERNIEVALUATOR_H

#include "PatternContainerEvaluator.h"

class PatternIEvaluator : public PatternContainerEvaluator {
public:
	PatternIEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi);
	QueryResult evaluate() override;
};

#endif
