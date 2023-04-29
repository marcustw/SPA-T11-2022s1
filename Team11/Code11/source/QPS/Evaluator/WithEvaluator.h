#pragma once
#ifndef WITHEVALUATOR_H
#define WITHEVALUATOR_H

#include "../../Common/SPAException.h"
#include "../../PKB/PKBQueryAPI.h"
#include "../../Common/Types.h"
#include "../Parser/PQLWith.h"
#include "QueryResult.h"
#include "GetAllEvaluator.h"
#include "BaseEvaluator.h"

class WithEvaluator : public BaseEvaluator {
	PQLReference lhsRef;
	PQLReference rhsRef;
	EntityType lhsEntityType;
	EntityType rhsEntityType;

	QueryResult evaluateSide(const GetAllEvaluator& getAllEval, EntityType entType, const std::string& entString,
		const std::string& refString, PQLReferenceType pqlRefType);
	QueryResult evaluateIdent(const GetAllEvaluator& getAllEval, EntityType entType, const std::string& entString,
		const std::string& refString);
	QueryResult evaluateInt(const GetAllEvaluator& getAllEval, EntityType entType, const std::string& entString,
		const std::string& refString);
	QueryResult evaluateBothName(const GetAllEvaluator& getAllEval);
	QueryResult evaluateBothValue(const GetAllEvaluator& getAllEval);

	StringMap getMapNameToIndices();
	void WithEvaluator::getIndicesResult(const StringMap& mapNameToIndices,
		std::unordered_set<std::string>* sameValsUset, std::vector<std::string>* sameVals,
		std::vector<std::string>* lhsIndices, std::vector<std::string>* rhsIndices);

public:
	WithEvaluator(const PQLWith& with, EntityType lhsEntityType, EntityType rhsEntityType, const PKBQueryAPI& pkbQueryApi);

	QueryResult evaluate() override;

	std::unordered_set<std::string> getSynonyms() const override;

	std::string toString() const override;

	int priority() const override;
};

#endif
