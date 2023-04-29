#include "WithEvaluator.h"


WithEvaluator::WithEvaluator(const PQLWith& with, EntityType lhsEntityType, EntityType rhsEntityType,
	const PKBQueryAPI& pkbQueryApi) : BaseEvaluator(pkbQueryApi), lhsRef(with.getLhsRef()),
	rhsRef(with.getRhsRef()), lhsEntityType(lhsEntityType), rhsEntityType(rhsEntityType) {
}

QueryResult WithEvaluator::evaluateInt(const GetAllEvaluator& getAllEval, EntityType entType,
	const std::string& entString, const std::string& refString) {
	std::vector<std::string> allSyns = getAllEval.getAll(entType);
	std::unordered_set<std::string> allSynsUset = std::unordered_set<std::string>(allSyns.begin(), allSyns.end());

	if (allSynsUset.find(refString) == allSynsUset.end()) {
		return QueryResult(true);
	}
	StringMap resultsMap;
	resultsMap[entString] = { refString };

	return QueryResult(resultsMap);
}


QueryResult WithEvaluator::evaluateIdent(const GetAllEvaluator& getAllEval, EntityType entType,
	const std::string& entString, const std::string& refString) {
	std::pair<std::vector<std::string>, std::vector<std::string>> allSyns = pkbQueryApi.getAttributeNames(entType);
	std::vector<std::string> synNames = allSyns.first;
	std::vector<std::string> synIndexes = allSyns.second;
	std::unordered_set<std::string> allSynsUset = std::unordered_set<std::string>(synNames.begin(), synNames.end());

	if (allSynsUset.find(refString) == allSynsUset.end()) {
		return QueryResult(true);
	}

	StringMap resultsMap;
	std::unordered_set<std::string> uset = std::unordered_set<std::string>();
	for (size_t i = 0; i < synNames.size(); i++) {
		if (uset.find(synIndexes[i]) == uset.end()) {
			if (synNames[i] == refString) {
				uset.insert(synIndexes.at(i));
			}
		}
	}
	std::vector<std::string> res = std::vector<std::string>(uset.begin(), uset.end());
	resultsMap[entString] = res;

	return QueryResult(resultsMap);
}

QueryResult WithEvaluator::evaluateSide(const GetAllEvaluator& getAllEval, EntityType entType,
	const std::string& entString, const std::string& refString, PQLReferenceType pqlRefType) {
	if (pqlRefType == PQLReferenceType::INTEGER) {
		return evaluateInt(getAllEval, entType, entString, refString);
	}
	return evaluateIdent(getAllEval, entType, entString, refString);
}

StringMap WithEvaluator::getMapNameToIndices() {
	std::pair<std::vector<std::string>, std::vector<std::string>> allLhsSyns
		= pkbQueryApi.getAttributeNames(lhsEntityType);
	std::vector<std::string> lhsSynNames = allLhsSyns.first;
	std::vector<std::string> lhsSynIndexes = allLhsSyns.second;
	StringMap mapNameToIndices;
	for (size_t i = 0; i < lhsSynNames.size(); i++) {
		if (mapNameToIndices.find(lhsSynNames[i]) == mapNameToIndices.end()) {
			mapNameToIndices[lhsSynNames[i]] = std::vector<std::string>();
		}
		mapNameToIndices[lhsSynNames[i]].push_back(lhsSynIndexes[i]);
	}
	return mapNameToIndices;
}

void WithEvaluator::getIndicesResult(const StringMap& mapNameToIndices, std::unordered_set<std::string>* sameValsUset,
	std::vector<std::string>* sameVals, std::vector<std::string>* lhsIndices,
	std::vector<std::string>* rhsIndices)
{
	std::pair<std::vector<std::string>, std::vector<std::string>> allRhsSyns
		= pkbQueryApi.getAttributeNames(rhsEntityType);
	std::vector<std::string> synNames = allRhsSyns.first;
	std::vector<std::string> synIndexes = allRhsSyns.second;
	std::unordered_set<std::string> uset;
	for (size_t i = 0; i < synNames.size(); i++) {
		if (mapNameToIndices.find(synNames[i]) == mapNameToIndices.end()) {
			continue;
		}
		sameValsUset->insert(synNames[i]);
		for (const std::string& lhsIndex : mapNameToIndices.at(synNames[i])) {
			std::string key = lhsIndex + " " + synIndexes[i];
			if (uset.find(key) == uset.end()) {
				lhsIndices->push_back(lhsIndex);
				rhsIndices->push_back(synIndexes[i]);
				sameVals->push_back(synNames[i]);
				uset.insert(key);
			}
		}
	}
}

QueryResult WithEvaluator::evaluateBothName(const GetAllEvaluator& getAllEval) {
	StringMap mapNameToIndices = getMapNameToIndices();
	std::unordered_set<std::string> sameValsUset;
	StringMap resultsMap;
	std::vector<std::string> sameVals;
	std::vector<std::string> lhsIndices;
	std::vector<std::string> rhsIndices;
	getIndicesResult(mapNameToIndices, &sameValsUset, &sameVals, &lhsIndices, &rhsIndices);
	if (lhsEntityType == EntityType::VARIABLE && rhsEntityType == EntityType::VARIABLE) {
		std::vector<std::string> sameValsVector = std::vector<std::string>(sameValsUset.begin(), sameValsUset.end());
		resultsMap[lhsRef.second] = sameValsVector;
		resultsMap[rhsRef.second] = sameValsVector;
		return QueryResult(resultsMap);
	}
	resultsMap[lhsRef.second] = ((lhsEntityType == EntityType::VARIABLE) ? sameVals : lhsIndices);
	resultsMap[rhsRef.second] = ((rhsEntityType == EntityType::VARIABLE) ? sameVals : rhsIndices);
	return QueryResult(resultsMap);
}

QueryResult WithEvaluator::evaluateBothValue(const GetAllEvaluator& getAllEval) {
	std::vector<std::string> lhsIndices = getAllEval.getAllStmt(lhsEntityType);
	std::vector<std::string> rhsIndices = getAllEval.getAllStmt(rhsEntityType);
	std::vector<std::string> sameVals;
	std::unordered_set<std::string> lhsIndicesUset = std::unordered_set<std::string>(lhsIndices.begin(), lhsIndices.end());
	for (std::string& rhsIndex : rhsIndices) {
		if (lhsIndicesUset.find(rhsIndex) != lhsIndicesUset.end()) {
			sameVals.push_back(rhsIndex);
		}
	}
	StringMap resultsMap;
	resultsMap[lhsRef.second] = sameVals;
	resultsMap[rhsRef.second] = sameVals;
	return QueryResult(resultsMap);
}


QueryResult WithEvaluator::evaluate() {
	if ((lhsRef.first == PQLReferenceType::IDENT && rhsRef.first == PQLReferenceType::IDENT) ||
		(lhsRef.first == PQLReferenceType::INTEGER && rhsRef.first == PQLReferenceType::INTEGER)) {
		return QueryResult(lhsRef.second != rhsRef.second);
	}

	GetAllEvaluator getAllEval = GetAllEvaluator(pkbQueryApi);

	if (lhsRef.first == PQLReferenceType::INTEGER || lhsRef.first == PQLReferenceType::IDENT) {
		return evaluateSide(getAllEval, rhsEntityType, rhsRef.second, lhsRef.second, lhsRef.first);
	} else if (rhsRef.first == PQLReferenceType::INTEGER || rhsRef.first == PQLReferenceType::IDENT) {
		return evaluateSide(getAllEval, lhsEntityType, lhsRef.second, rhsRef.second, rhsRef.first);
	}

	if (lhsEntityType == rhsEntityType && lhsRef.second == rhsRef.second
		&& lhsRef.first == rhsRef.first) {
		return QueryResult(false);
	}

	PQLReferenceType evaluatedType = PQLCommon::ATTRIBUTE_REF_TYPE.at(lhsRef.first);
	if (evaluatedType == PQLReferenceType::INTEGER) {
		return evaluateBothValue(getAllEval);
	}
	return evaluateBothName(getAllEval);
}

std::unordered_set<std::string> WithEvaluator::getSynonyms() const {
	std::unordered_set<std::string> syns;
	if (PQLCommon::WITH_ATTRIBUTE_TYPES.find(lhsRef.first) != PQLCommon::WITH_ATTRIBUTE_TYPES.end()) {
		syns.insert(lhsRef.second);
	} else if (lhsRef.first == PQLReferenceType::SYNONYM) {
		syns.insert(lhsRef.second);
	}
	if (PQLCommon::WITH_ATTRIBUTE_TYPES.find(rhsRef.first) != PQLCommon::WITH_ATTRIBUTE_TYPES.end()) {
		syns.insert(rhsRef.second);
	} else if (rhsRef.first == PQLReferenceType::SYNONYM) {
		syns.insert(rhsRef.second);
	}
	return syns;
}

std::string WithEvaluator::toString() const {
	std::string str = PQLSyntax::WITH;
	return str + PQLSyntax::LEFT_BRACKET + lhsRef.second
		+ PQLSyntax::COMMA + rhsRef.second + PQLSyntax::RIGHT_BRACKET;
}

int WithEvaluator::priority() const {
	return PQLCommon::WITH_BASE_PRIORITY + getSynonyms().size();
}
