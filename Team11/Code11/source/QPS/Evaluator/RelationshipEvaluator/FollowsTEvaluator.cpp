#include "FollowsTEvaluator.h"

FollowsTEvaluator::FollowsTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	FPEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::FOLLOWS_T) {
}
