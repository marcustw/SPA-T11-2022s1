#include "NextEvaluator.h"

NextEvaluator::NextEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator) :
	RelationshipEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, RelationshipType::NEXT) {
}

QueryResult NextEvaluator::evaluateDoubleInteger() {
	if (lhsRefString == rhsRefString) {  // Impossible for stmt to be Next of itself
		return QueryResult(true);
	}

	std::vector<std::string> vector = pkbQueryApi.getRelationshipLeftArg(RelationshipType::NEXT, stoi(rhsRefString));
	bool result = std::find(vector.begin(), vector.end(), lhsRefString) == vector.end();
	return QueryResult(result);
}

QueryResult NextEvaluator::evaluateWildCardsAndSynonyms() {
	if (lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::SYNONYM
		&& lhsRefString == rhsRefString) {  // Impossible for synonym to be Next of itself
		return QueryResult(true);
	}

	std::unordered_map<std::string, std::vector<std::string>> map;
	std::vector<std::string> leftVector;
	std::vector<std::string> rightVector;

	std::vector<std::string> lhsStmts;
	std::vector<std::string> rhsStmts;

	// find all LHS stmts that are of the correct EntityType
	if (lhsRef == PQLReferenceType::WILDCARD) {
		lhsStmts = generator.getAllStmt(EntityType::STMT);
	} else {
		EntityType lhsEntityType = declareMap.at(lhsRefString);
		lhsStmts = generator.getAllStmt(lhsEntityType);
	}

	// find all RHS stmts that are of the correct EntityType
	if (rhsRef == PQLReferenceType::WILDCARD) {
		rhsStmts = generator.getAllStmt(EntityType::STMT);
	} else {
		EntityType rhsEntityType = declareMap.at(rhsRefString);
		rhsStmts = generator.getAllStmt(rhsEntityType);
	}

	for (auto& it : lhsStmts) {
		std::vector<std::string> vector =
			pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, stoi(it));
		for (auto& it2 : vector) {
			if (std::find(rhsStmts.begin(), rhsStmts.end(), it2) != rhsStmts.end()) {
				if (lhsRef == PQLReferenceType::WILDCARD && rhsRef == PQLReferenceType::WILDCARD) {
					return QueryResult(false);
				}
				leftVector.push_back(it);
				rightVector.push_back(it2);
			}
		}
	}

	if (leftVector.empty()) {
		return QueryResult(true);
	}

	if (lhsRef == PQLReferenceType::SYNONYM) {
		map[lhsRefString] = leftVector;
	}

	if (rhsRef == PQLReferenceType::SYNONYM) {
		map[rhsRefString] = rightVector;
	}

	return QueryResult(map);
}

QueryResult NextEvaluator::evaluateInteger(const std::string& refString, const std::string& otherString,
	const PQLReferenceType& otherRef, const std::vector<std::string>& vector)
{
	std::vector<std::string> finalVector;
	std::vector<std::string> otherVector;

	if (otherRef == PQLReferenceType::WILDCARD) {
		otherVector = generator.getAllStmt(EntityType::STMT);
	} else {
		EntityType entityType = declareMap.at(otherString);
		otherVector = generator.getAllStmt(entityType);
	}

	for (auto& it : vector) {
		if (std::find(otherVector.begin(), otherVector.end(), it) != otherVector.end()) {
			finalVector.push_back(it);
		}
	}

	std::unordered_map<std::string, std::vector<std::string>> map;

	if (finalVector.empty()) {
		return QueryResult(true);
	} else if (otherRef == PQLReferenceType::WILDCARD) {
		return QueryResult(false);
	}

	map[otherString] = finalVector;

	return QueryResult(map);
}

QueryResult NextEvaluator::evaluate() {
	if (lhsRef == PQLReferenceType::INTEGER && rhsRef == PQLReferenceType::INTEGER) {  // two numbers
		return evaluateDoubleInteger();
	} else if (lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::SYNONYM
		|| lhsRef == PQLReferenceType::WILDCARD && rhsRef == PQLReferenceType::SYNONYM
		|| lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::WILDCARD
		|| lhsRef == PQLReferenceType::WILDCARD && rhsRef == PQLReferenceType::WILDCARD) {
		return evaluateWildCardsAndSynonyms();
	} else if (lhsRef == PQLReferenceType::INTEGER) {
		std::vector<std::string> vector = pkbQueryApi.getRelationshipRightArg(RelationshipType::NEXT, stoi(lhsRefString));
		return evaluateInteger(lhsRefString, rhsRefString, rhsRef, vector);
	} else if (rhsRef == PQLReferenceType::INTEGER) {
		std::vector<std::string> vector = pkbQueryApi.getRelationshipLeftArg(RelationshipType::NEXT, stoi(rhsRefString));
		return evaluateInteger(rhsRefString, lhsRefString, lhsRef, vector);
	} else {
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
}
