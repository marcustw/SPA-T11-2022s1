#include <string>
#include <utility>

#include "AffectsTEvaluator.h"

AffectsTEvaluator::AffectsTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
	const GetAllEvaluator& generator, AffectsTProcessor* processor) :
	AffectsBaseEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::AFFECTS_T,
		processor) {
}
