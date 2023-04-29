#include "FPEvaluator.h"

FPEvaluator::FPEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
	const GetAllEvaluator& generator, RelationshipType relationshipType) :
	RelationshipEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, relationshipType) {
}

QueryResult FPEvaluator::evaluateLhsIntRhsInt() {
	int lhsInt = stoi(lhsRefString);
	int rhsInt = stoi(rhsRefString);
	std::vector<std::string> stmtVector = pkbQueryApi.getRelationshipRightArg(relationshipType, lhsInt);
	return QueryResult(std::find(stmtVector.begin(), stmtVector.end(), rhsRefString) == stmtVector.end());
}

QueryResult FPEvaluator::evaluateLhsSynRhsSyn() {
	if (lhsRefString == rhsRefString) {
		return QueryResult(true);
	}

	std::vector<std::string> stmtVector = generator.getAllStmt(declareMap.at(lhsRefString));

	std::unordered_set<std::string> rhsValues;

	for (std::string i : generator.getAllStmt(declareMap.at(rhsRefString))) {
		rhsValues.insert(i);
	}

	std::vector<std::string> lhsVector;
	std::vector<std::string> rhsVector;

	for (std::string i : stmtVector) {
		std::vector<std::string> tempVector = pkbQueryApi.getRelationshipRightArg(relationshipType, stoi(i));
		for (std::string j : tempVector) {
			if (rhsValues.find(j) != rhsValues.end()) {
				lhsVector.push_back(i);
				rhsVector.push_back(j);
			}
		}
	}

	if (lhsVector.size() == 0) {
		return QueryResult(true);
	}

	StringMap map;
	map[lhsRefString] = lhsVector;
	map[rhsRefString] = rhsVector;
	return QueryResult(map);
}

QueryResult FPEvaluator::evaluateLhsWCRhsWC() {
	std::vector<std::string> stmtVector = pkbQueryApi.getAllStmts();

	for (std::string i : stmtVector) {
		if (pkbQueryApi.getRelationshipRightArg(relationshipType, stoi(i)).size() > 0) {
			return QueryResult(false);
		}
	}

	return QueryResult(true);
}

QueryResult FPEvaluator::evaluateLhsInt() {
	int lhsInt = stoi(lhsRefString);

	std::vector<std::string> stmtVector = pkbQueryApi.getRelationshipRightArg(relationshipType, lhsInt);
	if (stmtVector.size() == 0) {
		return QueryResult(true);
	}

	if (rhsRef == PQLReferenceType::SYNONYM) {
		std::unordered_set<std::string> rhsValues;

		for (std::string i : generator.getAllStmt(declareMap.at(rhsRefString))) {
			rhsValues.insert(i);
		}

		std::vector<std::string> result;

		for (std::string i : stmtVector) {
			if (rhsValues.find(i) != rhsValues.end()) {
				result.push_back(i);
			}
		}

		if (result.size() == 0) {
			return QueryResult(true);
		}

		StringMap map;
		map[rhsRefString] = result;

		return QueryResult(map);
	} else {
		return QueryResult(stmtVector.size() == 0);
	}
}

QueryResult FPEvaluator::evaluateLhsSyn() {
	std::vector<std::string> lhsVector = generator.getAllStmt(declareMap.at(lhsRefString));
	std::unordered_set<std::string> lhsValues;

	for (std::string i : lhsVector) {
		lhsValues.insert(i);
	}

	std::vector<std::string> result;

	if (rhsRef == PQLReferenceType::INTEGER) {
		int rhsInt = stoi(rhsRefString);
		std::vector<std::string> stmtVector = pkbQueryApi.getRelationshipLeftArg(relationshipType, rhsInt);

		for (std::string i : stmtVector) {
			if (lhsValues.find(i) != lhsValues.end()) {
				result.push_back(i);
			}
		}

		if (result.size() == 0) {
			return QueryResult(true);
		}

		StringMap map;
		map[lhsRefString] = result;
		return QueryResult(map);
	} else {
		for (std::string i : lhsVector) {
			std::vector<std::string> tempVector = pkbQueryApi.getRelationshipRightArg(relationshipType, stoi(i));

			if (tempVector.size() > 0) {
				result.push_back(i);
			}
		}

		if (result.size() == 0) {
			return QueryResult(true);
		}

		StringMap map;
		map[lhsRefString] = result;
		return QueryResult(map);
	}
}

QueryResult FPEvaluator::evaluateLhsWC() {
	if (rhsRef == PQLReferenceType::INTEGER) {
		int rhsInt = stoi(rhsRefString);
		std::vector<std::string> stmtVector = pkbQueryApi.getRelationshipLeftArg(relationshipType, rhsInt);
		return QueryResult(stmtVector.size() == 0);
	} else {
		std::vector<std::string> rhsValues;
		std::vector<std::string> rhsVector = generator.getAllStmt(declareMap.at(rhsRefString));

		for (std::string i : rhsVector) {
			std::vector<std::string> tempVector = pkbQueryApi.getRelationshipLeftArg(relationshipType, stoi(i));
			if (tempVector.size() > 0) {
				rhsValues.push_back(i);
			}
		}

		if (rhsValues.size() == 0) {
			return QueryResult(true);
		}

		StringMap map;
		map[rhsRefString] = rhsValues;
		return QueryResult(map);
	}
}

QueryResult FPEvaluator::evaluate() {
	assertSynonymsAreStatement();

	if (lhsRef == PQLReferenceType::IDENT || rhsRef == PQLReferenceType::IDENT) {
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}

	switch (lhsRef) {
	case PQLReferenceType::INTEGER:
		if (rhsRef == PQLReferenceType::INTEGER)
			return evaluateLhsIntRhsInt();
		return evaluateLhsInt();
	case PQLReferenceType::SYNONYM:
		if (rhsRef == PQLReferenceType::SYNONYM)
			return evaluateLhsSynRhsSyn();
		return evaluateLhsSyn();
	case PQLReferenceType::WILDCARD:
		if (rhsRef == PQLReferenceType::WILDCARD)
			return evaluateLhsWCRhsWC();
		return evaluateLhsWC();
	default:
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		break;
	}
}
