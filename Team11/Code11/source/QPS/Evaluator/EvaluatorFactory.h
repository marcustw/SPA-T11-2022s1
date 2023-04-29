#pragma once
#ifndef EVALUATORFACTORY_H
#define EVALUATORFACTORY_H

#include "../../Common/SPAException.h"
#include "../../PKB/PKBQueryAPI.h"
#include "../Common/PQLCommon.h"
#include "../../Common/Types.h"
#include "../Parser/PQLQueryObject.h"
#include "PatternEvaluator/PatternAEvaluator.h"
#include "PatternEvaluator/PatternIEvaluator.h"
#include "PatternEvaluator/PatternWEvaluator.h"
#include "PatternEvaluator/PatternEvaluator.h"
#include "WithEvaluator.h"
#include "RelationshipEvaluator/ModifiesSEvaluator.h"
#include "RelationshipEvaluator/ModifiesPEvaluator.h"
#include "RelationshipEvaluator/FollowsEvaluator.h"
#include "RelationshipEvaluator/FollowsTEvaluator.h"
#include "RelationshipEvaluator/ParentEvaluator.h"
#include "RelationshipEvaluator/ParentTEvaluator.h"
#include "RelationshipEvaluator/RelationshipEvaluator.h"
#include "RelationshipEvaluator/UsesSEvaluator.h"
#include "RelationshipEvaluator/UsesPEvaluator.h"
#include "RelationshipEvaluator/CallsEvaluator.h"
#include "RelationshipEvaluator/CallsTEvaluator.h"
#include "RelationshipEvaluator/NextEvaluator.h"
#include "RelationshipEvaluator/NextTEvaluator.h"
#include "RelationshipEvaluator/AffectsEvaluator.h"
#include "RelationshipEvaluator/AffectsTEvaluator.h"
#include "Processor/Processors.h"

class EvaluatorFactory {
	PKBQueryAPI pkbQueryApi;
	Processors* processors;
	std::vector<BaseEvaluator*> generateRelationshipEvaluators(
		const std::vector<PQLRelationship>& relationships,
		const DeclareMap& declareMap, const GetAllEvaluator& getAllEvaluator);

	std::vector<BaseEvaluator*> generatePatternEvaluators(
		const std::vector<PQLPattern>& patterns, const DeclareMap& declareMap);

	std::vector<BaseEvaluator*> generateWithEvaluators(
		const std::vector<PQLWith>& withs, const DeclareMap& declareMap);

	RelationshipEvaluator* generate(const PQLRelationship& relationship, const DeclareMap& declareMap,
		const GetAllEvaluator& generator) const;
	PatternEvaluator* generatePattern(const PQLPattern& pattern, const DeclareMap& declareMap) const;
	WithEvaluator* generateWith(const PQLWith& with, const DeclareMap& declareMap) const;

public:
	EvaluatorFactory(const PKBQueryAPI& pkbQueryApi, Processors* processors);

	std::vector<BaseEvaluator*> generateEvaluators(PQLQueryObject query, const std::vector<PQLReference>& pqlRefs,
		const DeclareMap& declareMap, const GetAllEvaluator& getAllEvaluator);
};

#endif
