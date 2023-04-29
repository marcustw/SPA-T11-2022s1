#include "CallsTEvaluator.h"

CallsTEvaluator::CallsTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	CallsBaseEvaluator(lhsRef, rhsRef, RelationshipType::CALL_T, declareMap, pkbQueryApi, generator) {}
