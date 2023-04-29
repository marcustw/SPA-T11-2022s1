#include "UsesPEvaluator.h"

UsesPEvaluator::UsesPEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	UMPEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::USES_P) {
}

QueryResult UsesPEvaluator::evaluate() {
	StringMap usesP = pkbQueryApi.getUsesPTable();
	return UMPEvaluator::evaluate(usesP);
}
