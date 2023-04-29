#pragma once
#ifndef QPSEVALUATOR_H
#define QPSEVALUATOR_H

#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

#include "../../PKB/PKBQueryAPI.h"
#include "../../Common/SPAException.h"
#include "../../Common/Types.h"
#include "../Common/QPSCache.h"
#include "../Common/PQLCommon.h"
#include "../Parser/PQLQueryObject.h"
#include "GetAllEvaluator.h"
#include "QueryResult.h"
#include "EvaluatorFactory.h"
#include "Processor/Processors.h"

class QPSEvaluator {
	PQLQueryObject query;
	PKBQueryAPI pkbQueryApi;
	Processors* processors;

private:
	std::vector<BaseEvaluator*> getComponentEvaluators(
		const std::unordered_map<std::string, std::vector<size_t>>& synonymAssignments,
		const std::unordered_set<std::string>& connections, const std::vector<BaseEvaluator*>& evaluators);

	std::vector<std::string> getConnectedSyns(const std::vector<size_t>& evaluatorIndices,
		std::unordered_set<std::string>* connections, std::unordered_set<std::string>* usedSynonyms,
		const std::vector<BaseEvaluator*>& evaluators);

	std::vector<BaseEvaluator*> getComponent(std::string assignment,
		const std::unordered_map<std::string, std::vector<size_t>>& synonymAssignments,
		std::unordered_set<std::string>* usedSynonyms,
		const std::vector<BaseEvaluator*>& evaluators);

	QueryResult evaluateNoSyns(const std::vector<BaseEvaluator*>& evaluators);
	bool findFirstResult(const std::vector<std::unordered_set<std::string>>& resultSyns,
		std::queue<size_t>* mergeQueue, std::unordered_set<size_t>* usedPos,
		std::unordered_set<std::string>* remainingSet);
	std::queue<size_t> getMergeQueue(const std::vector<std::unordered_set<std::string>>& resultSyns);

	QueryResult evaluate(
		const std::vector<BaseEvaluator*>& evaluators,
		const std::unordered_set<std::string>& filterSyns);

	StringMap getAllSynMap(
		const std::vector<PQLReference>& pqlRefs,
		const std::unordered_set<std::string>& resultSynonyms,
		const DeclareMap& declareMap,
		const GetAllEvaluator& getAllEvaluator);

	std::pair<StringMap, std::vector<PQLReference>> getRelevantMap(
		const std::vector<PQLReference>& pqlRefs,
		const std::unordered_set<std::string>& resultSynonyms,
		const QueryResult& result,
		const DeclareMap& declareMap);

	QueryResult handleNotFoundSynonyms(const StringMap& newResult,
		const std::vector<PQLReference>& notFoundSynonyms, const GetAllEvaluator& getAllEvaluator,
		const DeclareMap& declareMap);

	 QueryResult mergeResults(std::vector<QueryResult>* results);

	std::unordered_map<std::string, std::vector<size_t>> getSynonymAssignments(
		const std::vector<BaseEvaluator*>& evaluators);

	std::vector<std::vector<BaseEvaluator*>> getGroupsByConnection(
		const std::unordered_map<std::string, std::vector<size_t>>& synonymAssignments,
		const std::vector<BaseEvaluator*>& evaluators);

	std::vector<std::vector<BaseEvaluator*>> getSortedClausesGroups(
		const std::unordered_map<std::string, std::vector<size_t>>& synonymAssignments,
		const std::vector<BaseEvaluator*>& evaluators);

public:
	QPSEvaluator(const PQLQueryObject& query, const PKBQueryAPI& pkbQueryApi);
	QueryResult initialiseEvaluate();
};

#endif
