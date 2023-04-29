#include "EvaluatorFactory.h"

EvaluatorFactory::EvaluatorFactory(const PKBQueryAPI& pkbQueryApi, Processors* processors)
	: pkbQueryApi(pkbQueryApi), processors(processors) {
}

RelationshipEvaluator* EvaluatorFactory::generate(const PQLRelationship& relationship, const DeclareMap& declareMap,
	const GetAllEvaluator& generator) const
{
	PQLReference lhs = relationship.getLhsRef();
	PQLReference rhs = relationship.getRhsRef();
	RelationshipType relationshipType = relationship.getRelType();

	switch(relationshipType) {
	case RelationshipType::FOLLOWS:
		return new FollowsEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::FOLLOWS_T:
		return new FollowsTEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::PARENT:
		return new ParentEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::PARENT_T:
		return new ParentTEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::USES_S:
		return new UsesSEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::USES_P:
		return new UsesPEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::MODIFIES_S:
		return new ModifiesSEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::MODIFIES_P:
		return new ModifiesPEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::CALL:
		return new CallsEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::CALL_T:
		return new CallsTEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::NEXT:
		return new NextEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator);
	case RelationshipType::NEXT_T:
		return new NextTEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator, processors->getNextTProcessor());
	case RelationshipType::AFFECTS:
		return new AffectsEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator, processors->getAffectsProcessor());
	case RelationshipType::AFFECTS_T:
		return new AffectsTEvaluator(lhs, rhs, declareMap, pkbQueryApi, generator, processors->getAffectsTProcessor());
	default:
		break;
	}
	throw QPSException(QPSException::NO_IMPLEMENTATION);
}

PatternEvaluator* EvaluatorFactory::generatePattern(const PQLPattern& pattern, const DeclareMap& declareMap) const {
	PQLPatternType patternType = pattern.getPatternType();

	switch (patternType) {
	case PQLPatternType::PATTERN_A:
		return new PatternAEvaluator(pattern, pkbQueryApi);
		break;
	case PQLPatternType::PATTERN_W:
		return new PatternWEvaluator(pattern, pkbQueryApi);
		break;
	case PQLPatternType::PATTERN_I:
		return new PatternIEvaluator(pattern, pkbQueryApi);
		break;
	default:
		break;
	}
	throw QPSException(QPSException::NO_IMPLEMENTATION);
}

WithEvaluator* EvaluatorFactory::generateWith(const PQLWith& with, const DeclareMap& declareMap) const {
	PQLReference lhsRef = with.getLhsRef();
	PQLReference rhsRef = with.getRhsRef();
	EntityType lhsEntType = EntityType::CONSTANT;
	EntityType rhsEntType = EntityType::CONSTANT;

	if (declareMap.find(lhsRef.second) != declareMap.end()) {
		lhsEntType = declareMap.at(lhsRef.second);
	}

	if (declareMap.find(rhsRef.second) != declareMap.end()) {
		rhsEntType = declareMap.at(rhsRef.second);
	}

	return new WithEvaluator(with, lhsEntType, rhsEntType, pkbQueryApi);
}

std::vector<BaseEvaluator*> EvaluatorFactory::generateRelationshipEvaluators(
	const std::vector<PQLRelationship>& relationships,
	const DeclareMap& declareMap,
	const GetAllEvaluator& getAllEvaluator) {
	std::vector<BaseEvaluator*> evaluators;
	for (const PQLRelationship& relation : relationships) {
		RelationshipEvaluator* evaluator = generate(relation, declareMap, getAllEvaluator);
		evaluators.push_back(evaluator);
	}
	return evaluators;
}

std::vector<BaseEvaluator*> EvaluatorFactory::generatePatternEvaluators(
	const std::vector<PQLPattern>& patterns, const DeclareMap& declareMap) {
	std::vector<BaseEvaluator*> evaluators;
	for (const PQLPattern& pattern : patterns) {
		PatternEvaluator* evaluator = generatePattern(pattern, declareMap);
		evaluators.push_back(evaluator);
	}
	return evaluators;
}

std::vector<BaseEvaluator*> EvaluatorFactory::generateWithEvaluators(
	const std::vector<PQLWith>& withs, const DeclareMap& declareMap) {
	std::vector<BaseEvaluator*> evaluators;
	for (const PQLWith& with : withs) {
		WithEvaluator* evaluator = generateWith(with, declareMap);
		evaluators.push_back(evaluator);
	}
	return evaluators;
}


std::vector<BaseEvaluator*> EvaluatorFactory::generateEvaluators(PQLQueryObject query,
	const std::vector<PQLReference>& pqlRefs, const DeclareMap& declareMap,
	const GetAllEvaluator& getAllEvaluator)
{
	std::vector<PQLRelationship> relationships = query.getPQLRelationshipRef();
	std::vector<PQLPattern> patterns = query.getPQLPatternRef();
	std::vector<PQLWith> withs = query.getPQLWithClauses();
	std::vector<BaseEvaluator*> evaluators;
	std::vector<BaseEvaluator*> withEvaluators = generateWithEvaluators(withs, declareMap);
	std::vector<BaseEvaluator*> patternEvaluators = generatePatternEvaluators(patterns, declareMap);
	std::vector<BaseEvaluator*> relEvaluators =
		generateRelationshipEvaluators(relationships, declareMap, getAllEvaluator);
	evaluators.insert(evaluators.end(), withEvaluators.begin(), withEvaluators.end());
	evaluators.insert(evaluators.end(), patternEvaluators.begin(), patternEvaluators.end());
	evaluators.insert(evaluators.end(), relEvaluators.begin(), relEvaluators.end());
	return evaluators;
}
