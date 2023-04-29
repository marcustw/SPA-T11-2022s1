#include "ModifiesSEvaluator.h"

ModifiesSEvaluator::ModifiesSEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	UMSEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::MODIFIES_S) {
}

/*
Modifies_S happens in the following statements:
- assignment
- read
- if/while block with assignment
- calls another procedure that Modifies_S(v)
*/
QueryResult ModifiesSEvaluator::evaluate() {
	return UMSEvaluator::evaluate(pkbQueryApi.getModifiesSTable());
}
