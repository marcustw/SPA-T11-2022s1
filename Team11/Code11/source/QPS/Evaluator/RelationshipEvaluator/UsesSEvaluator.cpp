#include "UsesSEvaluator.h"


UsesSEvaluator::UsesSEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	UMSEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::USES_S) {
}


/*
Uses_S happens in the following statements:
- assignment
- print
- if/while that contains Uses_S(s, v)
- calls another procedure that Uses_S(s, v)
*/
QueryResult UsesSEvaluator::evaluate() {
	return UMSEvaluator::evaluate(pkbQueryApi.getUsesSTable());
}
