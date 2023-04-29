#include "ModifiesPEvaluator.h"

ModifiesPEvaluator::ModifiesPEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	UMPEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::MODIFIES_P) {
}

/*
Modifies_P happens in the following procedure:
- procedure contains modifies(s, v)
- calls another procedure that contains modifies(s, v)
*/
QueryResult ModifiesPEvaluator::evaluate() {
	StringMap modifiesP = pkbQueryApi.getModifiesPTable();
	return UMPEvaluator::evaluate(modifiesP);
}
