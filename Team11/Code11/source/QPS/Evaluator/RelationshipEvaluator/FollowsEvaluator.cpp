#include "FollowsEvaluator.h"

FollowsEvaluator::FollowsEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	FPEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::FOLLOWS) {
}
