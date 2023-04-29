#include <string>
#include <utility>
#include "AffectsEvaluator.h"

AffectsEvaluator::AffectsEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
	const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator, AffectsProcessor* processor) :
	AffectsBaseEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::AFFECTS,
		processor) {
}
