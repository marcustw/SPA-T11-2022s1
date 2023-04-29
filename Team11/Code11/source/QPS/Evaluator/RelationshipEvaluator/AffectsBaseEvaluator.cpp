#include <unordered_map>
#include <vector>
#include <string>

#include "AffectsBaseEvaluator.h"

AffectsBaseEvaluator::AffectsBaseEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
    const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
    const GetAllEvaluator& generator, RelationshipType relType,
    AffectsBaseProcessor* processor) :
    RelationshipEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, relType) {
    AffectsBaseEvaluator::processor = processor;
}

bool AffectsBaseEvaluator::exceedArgsBounds() {
	int stmtLimit = (pkbQueryApi.getAllStmts()).size();
	if (lhsRef == PQLReferenceType::INTEGER &&
		(stmtLimit < std::stoi(lhsRefString) || std::stoi(lhsRefString) <= 0))
	{
		return true;
	}
	if (rhsRef == PQLReferenceType::INTEGER &&
		(stmtLimit < std::stoi(rhsRefString) || std::stoi(rhsRefString) <= 0))
	{
		return true;
	}
	return false;
}

QueryResult AffectsBaseEvaluator::evaluateLhsIntRhsInt() {
	bool res = processor->checkRs(lhsRefString, rhsRefString);
	return QueryResult(!res);
}

QueryResult AffectsBaseEvaluator::evaluateLhsInt() {
	std::unordered_map<std::string, std::vector<std::string>> map;
	if (rhsRef == PQLReferenceType::SYNONYM) {
		if (declareMap.at(rhsRefString) == EntityType::ASSIGN
			|| declareMap.at(rhsRefString) == EntityType::STMT) {
			map[rhsRefString] = processor->getAllRightStmt(lhsRefString);
			return QueryResult(map);
		}
		return QueryResult(true);
	} else {
		std::vector<std::string> allAffectedStmts =
			processor->getAllRightStmt(lhsRefString);
		return QueryResult(allAffectedStmts.empty());
	}
}

QueryResult AffectsBaseEvaluator::evaluateLhsSynRhsInt() {
	std::unordered_map<std::string, std::vector<std::string>> map;
	if (declareMap.at(lhsRefString) == EntityType::ASSIGN || declareMap.at(lhsRefString) == EntityType::STMT) {
		map[lhsRefString] = processor->getAllLeftStmt(rhsRefString);
		return QueryResult(map);
	}
	return QueryResult(true);
}

QueryResult AffectsBaseEvaluator::evaluateLhsSyn() {
	std::unordered_map<std::string, std::vector<std::string>> map;
	if (declareMap.at(lhsRefString) != EntityType::ASSIGN && declareMap.at(lhsRefString) != EntityType::STMT) {
		return QueryResult(true);
	}

	std::vector<std::string> tempAssignStmts;
	std::pair<std::vector<std::string>, std::vector<std::string>> allAffectsStmt =
		processor->getAllAffects();

	if (rhsRef == PQLReferenceType::SYNONYM) {
		if (rhsRefString == lhsRefString) {
			std::vector<std::string> tempLeft = allAffectsStmt.first;
			std::vector<std::string> tempRight = allAffectsStmt.second;

			for (size_t i = 0; i < tempLeft.size(); i++) {
				if (tempLeft[i] == tempRight[i]) {
					tempAssignStmts.push_back(tempLeft[i]);
				}
			}
			map[lhsRefString] = tempAssignStmts;
			return QueryResult(map);
		}
		map[rhsRefString] = allAffectsStmt.second;
	}
	map[lhsRefString] = allAffectsStmt.first;
	return QueryResult(map);
}

QueryResult AffectsBaseEvaluator::evaluateLhsWCRhsInt() {
	std::vector<std::string> allAffectsStmts =
		processor->getAllLeftStmt(rhsRefString);
	return QueryResult(allAffectsStmts.empty());
}

QueryResult AffectsBaseEvaluator::evaluateLhsWC() {
	std::unordered_map<std::string, std::vector<std::string>> map;
	std::pair<std::vector<std::string>, std::vector<std::string>> allAffectsStmt =
		processor->getAllAffects();

	if (rhsRef == PQLReferenceType::SYNONYM) {
		if (declareMap.at(rhsRefString) == EntityType::ASSIGN
			|| declareMap.at(rhsRefString) == EntityType::STMT) {
			if (allAffectsStmt.second.empty()) {
				return QueryResult(true);
			}
			map[rhsRefString] = allAffectsStmt.second;
			return QueryResult(map);
		}
		return QueryResult(true);
	} else {
		return QueryResult(allAffectsStmt.first.empty());
	}
}

QueryResult AffectsBaseEvaluator::evaluate() {
	if (lhsRef == PQLReferenceType::IDENT ||
		rhsRef == PQLReferenceType::IDENT) {
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
	if (AffectsBaseEvaluator::exceedArgsBounds()) {
		return QueryResult(true);
	}
	switch (lhsRef) {
	case PQLReferenceType::INTEGER:
		if (rhsRef == PQLReferenceType::INTEGER)
			return evaluateLhsIntRhsInt();
		return evaluateLhsInt();
	case PQLReferenceType::SYNONYM:
		if (rhsRef == PQLReferenceType::INTEGER)
			return evaluateLhsSynRhsInt();
		return evaluateLhsSyn();
	case PQLReferenceType::WILDCARD:
		if (rhsRef == PQLReferenceType::INTEGER)
			return evaluateLhsWCRhsInt();
		return evaluateLhsWC();
	default:
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		break;
	}
}
