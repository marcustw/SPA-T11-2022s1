#include "PatternIEvaluator.h"

PatternIEvaluator::PatternIEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi) :
	PatternContainerEvaluator(pattern, pkbQueryApi) {
}

QueryResult PatternIEvaluator::evaluate() {
	std::vector<std::string> ifs = pkbQueryApi.getAllIfContainers();
	return PatternContainerEvaluator::evaluate(ifs);
}
