#include "CallsBaseEvaluator.h"

CallsBaseEvaluator::CallsBaseEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef, RelationshipType rsType,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi, const GetAllEvaluator& generator)
	: RelationshipEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator, rsType) {}

// verify if two procedures share a Calls/T relationship
QueryResult CallsBaseEvaluator::evaluateTwoProcNames() {
	// Procedures cannot call themselves
	if (lhsRefString == rhsRefString) {
		return QueryResult(true);
	}

	std::vector<std::string> vector = pkbQueryApi.getRelationshipLeftArg(relationshipType, rhsRefString);
	bool result = std::find(vector.begin(), vector.end(), lhsRefString) == vector.end();

	return QueryResult(result);
}

QueryResult CallsBaseEvaluator::evaluateWildCardsAndSynonyms() {
	// Procedures cannot call themselves
	if (lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::SYNONYM &&
		lhsRefString == rhsRefString) {
		return QueryResult(true);
	}

	std::unordered_map<std::string, std::vector<std::string>> map;
	std::vector<std::string> procedures = generator.getAll(EntityType::PROCEDURE);
	std::vector<std::string> leftVector;
	std::vector<std::string> rightVector;

	for (auto& it : procedures) {
		// gets all procedures that are called by lhs
		std::vector<std::string> vector = pkbQueryApi.getRelationshipRightArg(relationshipType, it);
		for (auto& it2 : vector) {
			if (lhsRef == PQLReferenceType::WILDCARD && rhsRef == PQLReferenceType::WILDCARD) {
				// Double wildcard, returns false as long as at least one vector is not empty
				return QueryResult(false);
			}
			leftVector.push_back(it);
			rightVector.push_back(it2);
		}
	}

	if ((leftVector.size() + rightVector.size()) == 0) {  // Both vectors are empty
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

/** Evaluate Calls/T query involving one procedure name string 
and one Wildcard or Synonym **/
QueryResult CallsBaseEvaluator::evaluateProcName(std::string refString, std::string otherString,
	const PQLReferenceType& otherRef, const std::vector<std::string>& vector) {
	std::unordered_map<std::string, std::vector<std::string>> map;

	if (vector.size() == 0) {
		return QueryResult(true);
	} else if (otherRef == PQLReferenceType::WILDCARD) {
		return QueryResult(false);
	}

	map[otherString] = vector;

	return QueryResult(map);
}

QueryResult CallsBaseEvaluator::evaluate() {
	if (lhsRef == PQLReferenceType::IDENT && rhsRef == PQLReferenceType::IDENT) {
		return evaluateTwoProcNames();
	} else if (lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::SYNONYM
		|| lhsRef == PQLReferenceType::WILDCARD && rhsRef == PQLReferenceType::SYNONYM
		|| lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::WILDCARD
		|| lhsRef == PQLReferenceType::WILDCARD && rhsRef == PQLReferenceType::WILDCARD) {
		return evaluateWildCardsAndSynonyms();
	} else if (lhsRef == PQLReferenceType::IDENT) {
		std::vector<std::string> vector = pkbQueryApi.getRelationshipRightArg(relationshipType, lhsRefString);
		return evaluateProcName(lhsRefString, rhsRefString, rhsRef, vector);
	} else if (rhsRef == PQLReferenceType::IDENT) {
		std::vector<std::string> vector = pkbQueryApi.getRelationshipLeftArg(relationshipType, rhsRefString);
		return evaluateProcName(rhsRefString, lhsRefString, lhsRef, vector);
	} else {
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
}


