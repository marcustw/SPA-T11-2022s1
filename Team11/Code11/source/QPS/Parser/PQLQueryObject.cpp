#include "PQLQueryObject.h"

// Constructor
PQLQueryObject::PQLQueryObject(
	std::vector<PQLDeclaration> pqlDeclarations,
	std::vector<PQLReference> pqlSynonym,
	std::vector<PQLRelationship> pqlRelationshipRef,
	std::vector<PQLPattern> pqlPatternRef,
	std::vector<PQLWith> pqlWithClauses) :
	pqlDeclarations(pqlDeclarations), pqlSynonym(pqlSynonym),
	pqlRelationshipRef(pqlRelationshipRef), pqlPatternRef(pqlPatternRef),
	pqlWithClauses(pqlWithClauses) {}

/* Getters */
std::vector<PQLDeclaration> PQLQueryObject::getPQLDeclaration() {
	return pqlDeclarations;
}

std::vector<PQLReference> PQLQueryObject::getPQLSynonym() {
	return pqlSynonym;
}

std::vector<PQLRelationship> PQLQueryObject::getPQLRelationshipRef() {
	return pqlRelationshipRef;
}

std::vector<PQLPattern> PQLQueryObject::getPQLPatternRef() {
	return pqlPatternRef;
}

std::vector<PQLWith> PQLQueryObject::getPQLWithClauses() {
	return pqlWithClauses;
}

bool PQLQueryObject::isSelectBoolean() {
	if (pqlSynonym.size() == 1 && pqlSynonym.front().first == PQLReferenceType::BOOLEAN) {
		return true;
	}
	return false;
}

DeclareMap PQLQueryObject::makeDeclareMap() {
	std::vector<PQLDeclaration> declarations = pqlDeclarations;
	DeclareMap declareMap;
	for (PQLDeclaration& pair : declarations) {
		if (declareMap.find(pair.second) != declareMap.end()) {
			// throw error as multiple declarations with same name
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}
		declareMap.insert({ pair.second, pair.first });
	}
	return declareMap;
}

void PQLQueryObject::verifyDeclarations(const DeclareMap& declareMap) {
	for (const PQLReference& pqlRef : pqlSynonym) {
		// if (pqlRef.first == PQLReferenceType::BOOLEAN) continue;
		if (declareMap.find(pqlRef.second) == declareMap.end()) {
			// throw error as synonym doesn't exist in declarations
			throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
		}

		if (pqlRef.first != PQLReferenceType::SYNONYM) {
			std::unordered_set<EntityType> validAttributes = PQLCommon::VALID_ATTRIBUTES.at(pqlRef.first);
			EntityType synonymEntityType = declareMap.at(pqlRef.second);
			if (validAttributes.find(synonymEntityType) == validAttributes.end()) {
				// throw error as attribute not valid
				throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
			}
		}
	}
}

void PQLQueryObject::verifyRelationships(const DeclareMap& declareMap) {
	for (auto relation = pqlRelationshipRef.begin(); relation != pqlRelationshipRef.end();
		relation++) {
		relation->verify(declareMap);
	}
}


void PQLQueryObject::verifyPatterns(const DeclareMap& declareMap) {
	for (auto pattern = pqlPatternRef.begin(); pattern != pqlPatternRef.end(); pattern++) {
		pattern->verify(declareMap);
	}
}

void PQLQueryObject::verifyWiths(const DeclareMap& declareMap) {
	for (PQLWith wif : pqlWithClauses) {
		wif.verify(declareMap);
	}
}

void PQLQueryObject::verify(const DeclareMap& declareMap) {
	verifyRelationships(declareMap);
	if (!isSelectBoolean()) {
		verifyDeclarations(declareMap);
	}
	verifyPatterns(declareMap);
	verifyWiths(declareMap);
}

std::unordered_set<std::string> PQLQueryObject::getUniqueSyns() const {
	std::unordered_set<std::string> filterSyns;
	for (const PQLReference& pqlRef : pqlSynonym) {
		filterSyns.insert(pqlRef.second);
	}
	return filterSyns;
}
