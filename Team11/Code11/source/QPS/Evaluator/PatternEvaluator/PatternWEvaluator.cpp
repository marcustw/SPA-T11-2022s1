#include "PatternWEvaluator.h"

PatternWEvaluator::PatternWEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi) :
	PatternContainerEvaluator(pattern, pkbQueryApi) {
}

QueryResult PatternWEvaluator::evaluate() {
	std::vector<std::string> whiles = pkbQueryApi.getAllWhileContainers();
	return PatternContainerEvaluator::evaluate(whiles);
}
