#pragma once
#ifndef UMPEVALUATOR_H
#define UMPEVALUATOR_H

#include "RelationshipEvaluator.h"

class UMPEvaluator : public RelationshipEvaluator {
private:
	QueryResult evaluateLhsSynonym(const StringMap& umP);
	QueryResult evaluateLhsIdent(const StringMap& umP);
	QueryResult evaluateLhsSynonym(const std::vector<std::string>& stmts, const std::vector<std::string>& variables);

protected:
	QueryResult evaluate(const StringMap& umPTable);

public:
	UMPEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, const DeclareMap& declareMap,
		const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator, RelationshipType pqlRelType);
};

#endif
