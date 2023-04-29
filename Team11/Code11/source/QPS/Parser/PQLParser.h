#pragma once

#include <map>
#include <vector>
#include <string>
#include <optional>

#include "PQLQueryObject.h"
#include "../../Common/Lexer.h"
#include "../../Common/SPAException.h"
#include "../../Common/ExpressionParser.h"
#include "../../SP/Extractors/ExtractorUtils.h"

class PQLParser {
	/* Class Variables : Static Map References */

	// [stmt, read, print, call, while, if, assign, variable, constant, procedure]
	static const std::vector<std::pair<std::string, EntityType>> designEntityMap;

	// [Follows, Follows*, Parent, Parent*, Uses (Uses_S, Uses_P), Modifies (Modifies_S, Modifies_P)]
	static const std::unordered_map<std::string, PQLReferenceType> attrRefMap;

	/* Class Fields */
	Lexer* pqlLexer;

	/* Functions */
	std::vector<PQLDeclaration> parseOneDeclaration();
	std::vector<PQLDeclaration> parseDeclarations();

	std::vector<PQLReference> parseSelects(const std::vector<PQLDeclaration>& declarations);

	PQLReference parseReference();

	PQLRelationship parseRelationship();
	std::vector<PQLRelationship> parseRelationships();

	std::string getExpressionSpecString();
	PQLExpression parseExpressionSpec();

	PQLPattern parsePattern(const std::vector<PQLDeclaration>& declarations);
	std::vector<PQLPattern> parsePatterns(const std::vector<PQLDeclaration>& declarations);

	PQLWith parseWith();
	std::vector<PQLWith> parseWithClauses();

	PQLReference parseElement();
	PQLReference parseAttribute();

	PQLPatternType getPatternType(std::string assignSyn, const std::vector<PQLDeclaration>& declarations);

public:
	// Constructor
	PQLParser();

	PQLQueryObject parseQuery(std::string queryString);
};
