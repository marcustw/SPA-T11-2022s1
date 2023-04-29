#include "QPSEvaluator.h"

#include <algorithm>


QPSEvaluator::QPSEvaluator(const PQLQueryObject& query, const PKBQueryAPI& pkbQueryApi) :
	query(query), pkbQueryApi(pkbQueryApi), processors(new Processors(pkbQueryApi)) {
}

bool QPSEvaluator::findFirstResult(const std::vector<std::unordered_set<std::string>>& resultSyns,
	std::queue<size_t>* mergeQueue, std::unordered_set<size_t>* usedPos,
	std::unordered_set<std::string>* remainingSet)
{
	bool found = false;
	size_t size = resultSyns.size();
	for (size_t i = 1; i < size; i++) {
		if (usedPos->find(i) != usedPos->end()) {
			continue;
		}
		std::unordered_set<std::string> usedSyns = resultSyns.at(i);
		for (const std::string& usedSyn : usedSyns) {
			if (remainingSet->find(usedSyn) != remainingSet->end()) {
				found = true;
				remainingSet->insert(usedSyns.begin(), usedSyns.end());
				mergeQueue->push(i);
				usedPos->insert(i);
				break;
			}
		}
	}
	return found;
}

std::queue<size_t> QPSEvaluator::getMergeQueue(const std::vector<std::unordered_set<std::string>>& resultSyns) {
	std::queue<size_t> mergeQueue;
	std::unordered_set<size_t> usedPos;
	std::unordered_set<std::string> remainingSet = resultSyns.at(0);
	size_t size = resultSyns.size();
	while (usedPos.size() < size - 1) {
		if (findFirstResult(resultSyns, &mergeQueue, &usedPos, &remainingSet)) {
			continue;
		}
		for (size_t i = 1; i < size; i++) {
			if (usedPos.find(i) != usedPos.end()) {
				continue;
			}
			std::unordered_set<std::string> usedSyns = resultSyns.at(i);
			remainingSet.insert(usedSyns.begin(), usedSyns.end());
			usedPos.insert(i);
			mergeQueue.push(i);
			break;
		}
	}
	return mergeQueue;
}

QueryResult QPSEvaluator::mergeResults(std::vector<QueryResult>* results) {
	if (results->empty()) {
		return QueryResult(false);
	}
	std::sort(results->begin(), results->end(), [](const QueryResult& r1, const QueryResult& r2) {
		return r1.getSize() < r2.getSize();
		});
	std::vector<std::unordered_set<std::string>> resultSyns;
	for (auto& result = results->begin(); result != results->end(); result++) {
		resultSyns.push_back(result->getSynonyms());
	}
	std::queue<size_t> mergeQueue = getMergeQueue(resultSyns);
	QueryResult mergedResult = results->at(0);
	while (!mergeQueue.empty()) {
		int idx = mergeQueue.front();
		mergeQueue.pop();
		mergedResult = mergedResult.merge(results->at(idx));
	}
	return mergedResult;
}

std::unordered_map<std::string, std::vector<size_t>> QPSEvaluator::getSynonymAssignments(
	const std::vector<BaseEvaluator*>& evaluators)
{
	std::unordered_map<std::string, std::vector<size_t>> result;
	for (size_t i = 0; i < evaluators.size(); i++) {
		std::unordered_set<std::string> syns = evaluators[i]->getSynonyms();
		for (const std::string& syn : syns) {
			if (result.find(syn) == result.end()) {
				result[syn] = { i };
			} else {
				result[syn].push_back(i);
			}
		}
	}
	return result;
}

std::vector<std::string> QPSEvaluator::getConnectedSyns(const std::vector<size_t>& evaluatorIndices,
	std::unordered_set<std::string>* connections,
	std::unordered_set<std::string>* usedSynonyms,
	const std::vector<BaseEvaluator*>& evaluators)
{
	std::vector<std::string> connectedSynonyms;
	for (size_t evaluatorIdx : evaluatorIndices) {
		std::unordered_set<std::string> relatedSynonyms = evaluators[evaluatorIdx]->getSynonyms();
		for (const std::string& synonym : relatedSynonyms) {
			if (usedSynonyms->find(synonym) == usedSynonyms->end()) {
				usedSynonyms->insert(synonym);
				connectedSynonyms.push_back(synonym);
				connections->insert(synonym);
			}
		}
	}
	return connectedSynonyms;
}

std::vector<BaseEvaluator*> QPSEvaluator::getComponentEvaluators(
	const std::unordered_map<std::string, std::vector<size_t>>& synonymAssignments,
	const std::unordered_set<std::string>& connections, const std::vector<BaseEvaluator*>& evaluators)
{
	std::unordered_set<size_t> evals;
	std::vector<BaseEvaluator*> componentEvaluators;
	for (const std::string& connect : connections) {
		if (synonymAssignments.find(connect) == synonymAssignments.end()) {
			continue;
		}
		std::vector<size_t> evaluatorIdxs = synonymAssignments.at(connect);
		for (const size_t& evaluatorIdx : evaluatorIdxs) {
			if (evals.find(evaluatorIdx) == evals.end()) {
				evals.insert(evaluatorIdx);
				componentEvaluators.push_back(evaluators[evaluatorIdx]);
			}
		}
	}
	return componentEvaluators;
}

std::vector<BaseEvaluator*> QPSEvaluator::getComponent(std::string assignment,
	const std::unordered_map<std::string, std::vector<size_t>>& synonymAssignments,
	std::unordered_set<std::string>* usedSynonyms,
	const std::vector<BaseEvaluator*>& evaluators)
{
	std::unordered_set<std::string> connections;
	std::queue<std::string> connectedSynonyms;
	connections.insert(assignment);
	connectedSynonyms.push(assignment);
	usedSynonyms->insert(assignment);
	while (!connectedSynonyms.empty()) {
		std::string currentSynonym = connectedSynonyms.front();
		connectedSynonyms.pop();
		if (synonymAssignments.find(currentSynonym) == synonymAssignments.end()) {
			continue;
		}
		std::vector<std::string> connectedSyns = getConnectedSyns(
			synonymAssignments.at(currentSynonym), &connections, usedSynonyms, evaluators);
		for (const std::string& s : connectedSyns) {
			connectedSynonyms.push(s);
		}
	}
	return getComponentEvaluators(synonymAssignments, connections, evaluators);
}

std::vector<std::vector<BaseEvaluator*>> QPSEvaluator::getGroupsByConnection(
	const std::unordered_map<std::string, std::vector<size_t>>& synonymAssignments,
	const std::vector<BaseEvaluator*>& evaluators)
{
	std::unordered_set<std::string> usedSynonyms;
	std::vector<std::vector<BaseEvaluator*>> components;

	for (std::pair<std::string, std::vector<size_t>> assignment : synonymAssignments) {
		if (usedSynonyms.find(assignment.first) == usedSynonyms.end()) {
			std::vector<BaseEvaluator*> componentEvaluators =
				getComponent(assignment.first, synonymAssignments,
					&usedSynonyms, evaluators);
			components.push_back(componentEvaluators);
		}
	}
	return components;
}

std::vector<std::vector<BaseEvaluator*>> QPSEvaluator::getSortedClausesGroups(
	const std::unordered_map<std::string, std::vector<size_t>>& synonymAssignments,
	const std::vector<BaseEvaluator*>& evaluators)
{
	std::vector<std::vector<BaseEvaluator*>> components
		= getGroupsByConnection(synonymAssignments, evaluators);

	// sort groups according to number of synonyms
	std::sort(components.begin(), components.end(),
		[](const std::vector<BaseEvaluator*>& c1, const std::vector<BaseEvaluator*>& c2) {
				return c1.size() < c2.size();
		});

	// for each group, sort evaluators according to priority
	for (auto& component : components) {
		std::sort(component.begin(), component.end(),
			[](BaseEvaluator* e1, BaseEvaluator* e2) {
				return e1->priority() < e2->priority();
			});
	}

	return components;
}

QueryResult QPSEvaluator::evaluateNoSyns(const std::vector<BaseEvaluator*>& evaluators) {
	QueryResult result(false);
	for (BaseEvaluator* evaluator : evaluators) {
		if (evaluator->getSynonyms().empty()) {
			QueryResult res = evaluator->evaluate();
			if (res.hasNone()) {
				return QueryResult(true);
			}
			result = result.merge(res);
		}
	}
	return result;
}

QueryResult QPSEvaluator::evaluate(const std::vector<BaseEvaluator*>& evaluators,
	const std::unordered_set<std::string>& filterSyns)
{
	QueryResult result = evaluateNoSyns(evaluators).filter(filterSyns);
	std::unordered_map<std::string, std::vector<size_t>> synonymAssignments
		= getSynonymAssignments(evaluators);

	std::vector<std::vector<BaseEvaluator*>> groups
		= getSortedClausesGroups(synonymAssignments, evaluators);

	for (auto& group : groups) {
		std::vector<QueryResult> queryResults;
		for (BaseEvaluator* evaluator : group) {
			QueryResult res = evaluator->evaluate();
			if (res.hasNone()) {
				return QueryResult(true);
			}
			queryResults.push_back(res);
		}
		result = result.merge(mergeResults(&queryResults).filter(filterSyns));
	}

	return result;
}


StringMap QPSEvaluator::getAllSynMap(
	const std::vector<PQLReference>& pqlRefs,
	const std::unordered_set<std::string>& resultSynonyms,
	const DeclareMap& declareMap,
	const GetAllEvaluator& getAllEvaluator) {
	StringMap resMap;

	for (const PQLReference& pqlRef : pqlRefs) {
		switch (pqlRef.first) {
		case PQLReferenceType::SYNONYM:
		case PQLReferenceType::PROC_NAME:
		case PQLReferenceType::STMT_NO:
		case PQLReferenceType::VAR_NAME:
		case PQLReferenceType::VALUE:
			if (resultSynonyms.find(pqlRef.second) == resultSynonyms.end()) {
				resMap[pqlRef.second] = getAllEvaluator.getAll(declareMap.at(pqlRef.second));
			}
			break;
		default:
			break;
		}
	}

	return resMap;
}

std::pair<StringMap, std::vector<PQLReference>> QPSEvaluator::getRelevantMap(
	const std::vector<PQLReference>& pqlRefs,
	const std::unordered_set<std::string>& resultSynonyms,
	const QueryResult& result, const DeclareMap& declareMap) {
	StringMap relevantMap;

	std::vector<std::string> synonyms;
	std::vector<PQLReference> notFoundSynonyms;
	for (PQLReference pqlRef : pqlRefs) {
		synonyms.push_back(pqlRef.second);
	}

	for (PQLReference pqlRef : pqlRefs) {
		if (resultSynonyms.find(pqlRef.second) == resultSynonyms.end()) {
			notFoundSynonyms.push_back(pqlRef);
		} else {
			std::vector<std::string> column = result.getColumn(pqlRef.second);
			relevantMap[pqlRef.second] = column;
		}
	}
	return { relevantMap, notFoundSynonyms };
}

QueryResult QPSEvaluator::handleNotFoundSynonyms(const StringMap& relevantMap,
	const std::vector<PQLReference>& notFoundSynonyms,
	const GetAllEvaluator& getAllEvaluator, const DeclareMap& declareMap)
{
	QueryResult newResult = relevantMap.empty() ? QueryResult(false) : QueryResult(relevantMap);

	for (PQLReference pqlRef : notFoundSynonyms) {
		std::string s = pqlRef.second;
		StringMap map;
		std::vector<std::string> modifiedVector = getAllEvaluator.getAll(declareMap.at(s));
		map[s] = modifiedVector;
		newResult = newResult.merge(QueryResult(map));
	}

	return newResult;
}

QueryResult QPSEvaluator::initialiseEvaluate() {
	DeclareMap declareMap = query.makeDeclareMap();
	query.verify(declareMap);
	std::vector<PQLReference> pqlRefs = query.getPQLSynonym();
	GetAllEvaluator getAllEvaluator(pkbQueryApi);
	EvaluatorFactory evalFactory = EvaluatorFactory(pkbQueryApi, processors);
	std::vector<BaseEvaluator*> evaluators = evalFactory.generateEvaluators(query,
		pqlRefs, declareMap, getAllEvaluator);
	std::unordered_set<std::string> filterSyns = query.getUniqueSyns();
	QueryResult result = evaluate(evaluators, filterSyns);

	if (result.hasNone()) {
		return QueryResult(true);
	}

	if (query.isSelectBoolean()) {
		return QueryResult(result.hasNone());
	}

	std::unordered_set<std::string> resultSynonyms = result.getSynonyms();
	std::pair<StringMap, std::vector<PQLReference>> relevantMapping = getRelevantMap(pqlRefs, resultSynonyms,
		result, declareMap);
	StringMap relevantMap = relevantMapping.first;
	std::vector<PQLReference> notFoundSynonyms = relevantMapping.second;

	return handleNotFoundSynonyms(relevantMap, notFoundSynonyms, getAllEvaluator, declareMap);
}
