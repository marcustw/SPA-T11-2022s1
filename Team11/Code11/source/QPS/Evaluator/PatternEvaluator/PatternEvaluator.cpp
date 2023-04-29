#include "PatternEvaluator.h"

PatternEvaluator::PatternEvaluator(const PQLPattern& pattern, const PKBQueryAPI& pkbQueryApi)
	: BaseEvaluator(pkbQueryApi) {
	PatternEvaluator::synonym = pattern.getSynonym();
	PatternEvaluator::entRef = pattern.getEntRef();
	PatternEvaluator::expressionSpec = pattern.getExpressionSpec();
	PatternEvaluator::patternType = pattern.getPatternType();
}

std::unordered_set<std::string> PatternEvaluator::getSynonyms() const {
	if (entRef.first == PQLReferenceType::SYNONYM) {
		return { synonym, entRef.second };
	}
	return { synonym };
}

std::string PatternEvaluator::toString() const {
	return PQLSyntax::PATTERN + std::string(" ") + synonym + PQLSyntax::LEFT_BRACKET + entRef.second
		+ PQLSyntax::COMMA + expressionSpec.second + PQLSyntax::RIGHT_BRACKET;
}

int PatternEvaluator::priority() const {
	switch (patternType) {
	case PQLPatternType::PATTERN_A:
		if (expressionSpec.first == PQLExpressionType::FULL) {
			return PQLCommon::PATTERN_BASE_PRIORITY;
		} else if (expressionSpec.first == PQLExpressionType::MIXED) {
			return PQLCommon::PATTERN_BASE_PRIORITY + 1;
		}
		break;
	default:
		break;
	}
	return PQLCommon::PATTERN_WILDCARD_AND_REL_BASE_PRIORITY;
}
