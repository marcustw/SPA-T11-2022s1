#include "CallsEvaluator.h"

CallsEvaluator::CallsEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	CallsBaseEvaluator(lhsRef, rhsRef, RelationshipType::CALL, declareMap, pkbQueryApi, generator) {}
