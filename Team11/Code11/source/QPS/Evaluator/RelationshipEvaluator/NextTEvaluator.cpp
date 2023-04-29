#include "NextTEvaluator.h"

NextTEvaluator::NextTEvaluator(const PQLReference& lhsRef, const PQLReference& rhsRef,
	const DeclareMap& declareMap, const PKBQueryAPI& pkbQueryApi,
	const GetAllEvaluator& generator, NextTProcessor* processor)
	: RelationshipEvaluator(lhsRef, rhsRef, declareMap, pkbQueryApi, generator,
		RelationshipType::NEXT_T), processor(processor) {}

QueryResult NextTEvaluator::evaluateDoubleInteger() {
	bool hasANextTRelationship = processor->checkSpecificNextTPair(lhsRefString, rhsRefString);

	bool resultIsNone = !hasANextTRelationship;

	return QueryResult(resultIsNone);
}

QueryResult NextTEvaluator::evaluateSameSynonym() {
	std::unordered_map<std::string, std::vector<std::string>> map;
	EntityType EntityType = declareMap.at(lhsRefString);
	std::vector<std::string>* allStmts = new std::vector<std::string>();
	*allStmts = generator.getAllStmt(EntityType);
	std::vector<std::string>* finalVector = new std::vector<std::string>();

	processor->findSameStmtNextTPair(allStmts, finalVector);

	if (finalVector->empty()) {
		return QueryResult(true);
	} else {
		map[lhsRefString] = *finalVector;
		return QueryResult(map);
	}
}

QueryResult NextTEvaluator::evaluateWildCardsAndSynonyms() {
	std::vector<std::string>* lhsStmts = new std::vector<std::string>();
	std::vector<std::string>* rhsStmts = new std::vector<std::string>();

	std::unordered_map<std::string, std::vector<std::string>> map;

	// find all LHS stmts that are of the correct EntityType
	if (lhsRef == PQLReferenceType::WILDCARD) {
		*lhsStmts = generator.getAllStmt(EntityType::STMT);
	} else {
		EntityType lhsEntityType = declareMap.at(lhsRefString);
		*lhsStmts = generator.getAllStmt(lhsEntityType);
	}

	// find all RHS stmts that are of the correct EntityType
	if (rhsRef == PQLReferenceType::WILDCARD) {
		*rhsStmts = generator.getAllStmt(EntityType::STMT);
	} else {
		EntityType rhsEntityType = declareMap.at(rhsRefString);
		*rhsStmts = generator.getAllStmt(rhsEntityType);
	}

	// Vectors that will contain all possible values of lhs and rhs
	std::vector<std::string>* leftVector = new std::vector<std::string>();
	std::vector<std::string>* rightVector = new std::vector<std::string>();

	processor->findAllNextTPairs(leftVector, rightVector, lhsStmts, rhsStmts, lhsRef, rhsRef);

	if (leftVector->empty()) {
		return QueryResult(true);
	}

	if (lhsRef == PQLReferenceType::SYNONYM) {
		map[lhsRefString] = *leftVector;
	}

	if (rhsRef == PQLReferenceType::SYNONYM) {
		map[rhsRefString] = *rightVector;
	}

	return QueryResult(map);
}

QueryResult NextTEvaluator::evaluateDoubleWildcard() {
	std::vector<std::string>* allStmts = new std::vector<std::string>();
	*allStmts = generator.getAllStmt(EntityType::STMT);

	bool nextTPairExists = processor->checkForAnyNextTPair(allStmts, allStmts);
	bool resultIsNone = !nextTPairExists;

	return QueryResult(resultIsNone);
}

QueryResult NextTEvaluator::evaluateLeftIntegerRightWildcardOrSynonym() {
	std::vector<std::string>* lhsStmt = new std::vector<std::string>();
	*lhsStmt = { lhsRefString };
	std::vector<std::string>* rhsStmts = new std::vector<std::string>();
	std::vector<std::string>* leftVector = new std::vector<std::string>();
	std::vector<std::string>* finalVector = new std::vector<std::string>();
	std::unordered_map<std::string, std::vector<std::string>> map;

	if (rhsRef == PQLReferenceType::WILDCARD) {
		*rhsStmts = generator.getAllStmt(EntityType::STMT);

		// finding any NextT of lhsRefString will satisfy the clause
		bool nextTPairExists = processor->checkForAnyNextTPair(lhsStmt, rhsStmts);
		bool resultIsNone = !nextTPairExists;

		return QueryResult(resultIsNone);
	} else {
		EntityType rhsEntityType = declareMap.at(rhsRefString);
		*rhsStmts = generator.getAllStmt(rhsEntityType);
		// finding every NextT of lhsRefString and store it in the finalVector
		processor->findAllNextTPairs(leftVector, finalVector, lhsStmt, rhsStmts, lhsRef, rhsRef);

		if (finalVector->empty()) {
			return QueryResult(true);
		}

		map[rhsRefString] = *finalVector;

		return QueryResult(map);
	}
}

QueryResult NextTEvaluator::evaluateLeftWildcardOrSynonymRightInteger() {
	std::vector<std::string>* lhsStmts = new std::vector<std::string>();
	std::vector<std::string>* rhsStmt = new std::vector<std::string>();
	*rhsStmt = { rhsRefString };
	std::vector<std::string>* rightVector = new std::vector<std::string>();
	std::vector<std::string>* finalVector = new std::vector<std::string>();
	std::unordered_map<std::string, std::vector<std::string>> map;

	if (lhsRef == PQLReferenceType::WILDCARD) {
		*lhsStmts = generator.getAllStmt(EntityType::STMT);

		// finding any NextT of rhsRefString will satisfy the clause
		bool nextTPairExists = processor->checkForAnyNextTPair(lhsStmts, rhsStmt);
		bool resultIsNone = !nextTPairExists;

		return QueryResult(resultIsNone);
	} else {
		EntityType lhsEntityType = declareMap.at(lhsRefString);
		*lhsStmts = generator.getAllStmt(lhsEntityType);

		// finding every NextT of rhsRefString and store it in the finalVector
		processor->findAllNextTPairs(finalVector, rightVector, lhsStmts, rhsStmt, lhsRef, rhsRef);

		if (finalVector->empty()) {
			return QueryResult(true);
		}

		map[lhsRefString] = *finalVector;

		return QueryResult(map);
	}
}

QueryResult NextTEvaluator::evaluate() {
	if (lhsRef == PQLReferenceType::INTEGER && rhsRef == PQLReferenceType::INTEGER) {  // two numbers
		return evaluateDoubleInteger();
	} else if (lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::SYNONYM
		&& lhsRefString == rhsRefString) {  // Both arguments are the same synonym
		return evaluateSameSynonym();
	} else if (lhsRef == PQLReferenceType::WILDCARD && rhsRef == PQLReferenceType::WILDCARD) {
		return evaluateDoubleWildcard();
	} else if (lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::SYNONYM
		|| lhsRef == PQLReferenceType::WILDCARD && rhsRef == PQLReferenceType::SYNONYM
		|| lhsRef == PQLReferenceType::SYNONYM && rhsRef == PQLReferenceType::WILDCARD) {
		return evaluateWildCardsAndSynonyms();
	} else if (lhsRef == PQLReferenceType::INTEGER) {
		return evaluateLeftIntegerRightWildcardOrSynonym();
	} else if (rhsRef == PQLReferenceType::INTEGER) {
		return evaluateLeftWildcardOrSynonymRightInteger();
	} else {
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
}
