#pragma once

#include <vector>

#include "../Common/PQLCommon.h"
#include "../Common/PQLSyntax.h"
#include "PQLPattern.h"
#include "PQLRelationship.h"
#include "PQLWith.h"

class PQLQueryObject {
	// declarations
	std::vector<PQLDeclaration> pqlDeclarations;

	// synonym(s)
	std::vector<PQLReference> pqlSynonym;

	// relationships (relRef) in select-cl, size() == 0 or 1
	std::vector<PQLRelationship> pqlRelationshipRef;

	// patterns in pattern-cl, size() == 0 or 1
	std::vector<PQLPattern> pqlPatternRef;

	// withs
	std::vector<PQLWith> pqlWithClauses;

	void verifyDeclarations(const DeclareMap& declareMap);
	void verifyRelationships(const DeclareMap& declareMap);
	void verifyWiths(const DeclareMap& declareMap);
	void verifyPatterns(const DeclareMap& declareMap);

public:
	// Constructor
	PQLQueryObject(
		std::vector<PQLDeclaration> pqlDeclarations,
		std::vector<PQLReference> pqlSynonym,
		std::vector<PQLRelationship> pqlRelationshipRef,
		std::vector<PQLPattern> pqlPatternRef,
		std::vector<PQLWith> pqlWithClauses);

	std::vector<PQLDeclaration> getPQLDeclaration();
	std::vector<PQLReference> getPQLSynonym();
	std::vector<PQLRelationship> getPQLRelationshipRef();
	std::vector<PQLPattern> getPQLPatternRef();
	std::vector<PQLWith> getPQLWithClauses();

	DeclareMap PQLQueryObject::makeDeclareMap();

	std::unordered_set<std::string> getUniqueSyns() const;
	void verify(const DeclareMap& declareMap);
	bool isSelectBoolean();
};
