#include "PQLParser.h"


// Constructor
PQLParser::PQLParser() {}

const std::vector<std::pair<std::string, EntityType>> PQLParser::designEntityMap = {
	{ "stmt",		EntityType::STMT },
	{ "read",		EntityType::READ },
	{ "print",		EntityType::PRINT },
	{ "call",		EntityType::CALL },
	{ "while",		EntityType::WHILE },
	{ "if",			EntityType::IF },
	{ "assign",		EntityType::ASSIGN },
	{ "variable",	EntityType::VARIABLE },
	{ "constant",	EntityType::CONSTANT },
	{ "procedure",	EntityType::PROCEDURE }
};


const std::unordered_map<std::string, PQLReferenceType> PQLParser::attrRefMap = {
	{ "procName",	PQLReferenceType::PROC_NAME },
	{ "varName",	PQLReferenceType::VAR_NAME },
	{ "value",		PQLReferenceType::VALUE },
	{ "stmt#",		PQLReferenceType::STMT_NO }
};


std::vector<PQLDeclaration> PQLParser::parseOneDeclaration() {
	std::vector<PQLDeclaration> declaration;

	if (pqlLexer->nextName() == PQLSyntax::SELECT) {
		return declaration;
	}

	std::string entityTypeString = pqlLexer->getName();
	EntityType actualEntityType;

	// Finding Design Entity Type
	bool entityFound = false;
	for (auto& designEntity : PQLParser::designEntityMap) {
		if (entityTypeString == designEntity.first) {
			entityFound = true;
			actualEntityType = designEntity.second;
			break;
		}
	}
	if (!entityFound) {
		return declaration;
	}

	// Get entity synonym
	std::string name = pqlLexer->getName();
	if (name.empty()) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}
	declaration.push_back({ actualEntityType, name });

	// Parse every other synonym
	while (pqlLexer->isNextChar(PQLSyntax::COMMA)) {
		name = pqlLexer->getName();
		if (name.empty()) {
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
		declaration.push_back({ actualEntityType, name });
	}

	if (!pqlLexer->isNextChar(PQLSyntax::SEMICOLON)) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	return declaration;
}

std::vector<PQLDeclaration> PQLParser::parseDeclarations() {
	std::vector<PQLDeclaration> result;
	std::vector<std::string> names;

	std::vector<PQLDeclaration> itr = parseOneDeclaration();
	while (!itr.empty()) {
		for (const PQLDeclaration& declaration : itr) {
			result.push_back(declaration);
		}
		itr = parseOneDeclaration();
	}
	return result;
}



std::vector<PQLReference> PQLParser::parseSelects(const std::vector<PQLDeclaration>& pqlDeclarations) {
	// Check for 'Select'
	std::string selectString = pqlLexer->getName();
	if (selectString != PQLSyntax::SELECT) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}
	std::vector<PQLReference> result;
	if (pqlLexer->isNextChar(PQLSyntax::LEFT_ANGLE_BRACKET)) {
		while (!pqlLexer->reachedEnd()) {
			PQLReference elem = parseElement();
			result.push_back(elem);
			if (pqlLexer->isNextChar(PQLSyntax::RIGHT_ANGLE_BRACKET)) {
				break;
			} else if (pqlLexer->isNextChar(PQLSyntax::COMMA)) {
				continue;
			} else {
				throw QPSException(QPSException::QPS_SYNTAX_ERROR);
			}
		}
		// Check for syntax error, eg: Select <>
		if (result.empty()) {
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
	} else if (pqlLexer->nextName() == PQLSyntax::BOOLEAN_SYN) {
		for (const PQLDeclaration& decl : pqlDeclarations) {
			if (decl.second == PQLSyntax::BOOLEAN_SYN) {
				PQLReference elem = parseElement();
				result.push_back(elem);
				return result;
				break;
			}
		}
		pqlLexer->getName();
		PQLReference elem = PQLReference(PQLReferenceType::BOOLEAN, PQLSyntax::BOOLEAN_SYN);
		result.push_back(elem);
		return result;
	} else {
		PQLReference elem = parseElement();
		result.push_back(elem);
	}

	return result;
}

PQLReference PQLParser::parseReference() {
	PQLReferenceType actualRefType;
	std::string refString;
	if (pqlLexer->isNextChar(PQLSyntax::UNDERSCORE)) {
		actualRefType = PQLReferenceType::WILDCARD;
		refString = PQLSyntax::UNDERSCORE;
	} else if (pqlLexer->isNextChar(PQLSyntax::QUOTE)) {
		refString = pqlLexer->getName();
		if (refString.empty()) {
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
		if (!pqlLexer->isNextChar(PQLSyntax::QUOTE)) {
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
		actualRefType = PQLReferenceType::IDENT;
	} else {
		refString = pqlLexer->getInteger();
		if (!refString.empty()) {
			actualRefType = PQLReferenceType::INTEGER;
		} else {
			refString = pqlLexer->getName();
			if (refString.empty()) {
				throw QPSException(QPSException::QPS_SYNTAX_ERROR);
			} else {
				actualRefType = PQLReferenceType::SYNONYM;
			}
		}
	}

	return PQLReference(actualRefType, refString);
}

PQLRelationship PQLParser::parseRelationship() {
	std::string pqlRelTypeString = pqlLexer->getName();
	if (pqlLexer->isNextChar(PQLSyntax::STAR)) {
		pqlRelTypeString += PQLSyntax::STAR;
	}

	if (PQLCommon::RELATIONSHIP_MAP.find(pqlRelTypeString) == PQLCommon::RELATIONSHIP_MAP.end()) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}
	RelationshipType actualRelType = PQLCommon::RELATIONSHIP_MAP.at(pqlRelTypeString);

	if (!pqlLexer->isNextChar(PQLSyntax::LEFT_BRACKET)) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	PQLReference lhsRef = parseReference();

	if (!pqlLexer->isNextChar(PQLSyntax::COMMA)) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	PQLReference rhsRef = parseReference();

	if (!pqlLexer->isNextChar(PQLSyntax::RIGHT_BRACKET)) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	return PQLRelationship(actualRelType, lhsRef, rhsRef);
}


std::vector<PQLRelationship> PQLParser::parseRelationships() {
	std::string suchString = pqlLexer->getName();
	if (suchString != PQLSyntax::SUCH) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}
	std::string thatString = pqlLexer->getName();
	if (thatString != PQLSyntax::THAT) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	std::vector<PQLRelationship> result;
	result.push_back(parseRelationship());

	while (pqlLexer->nextName() == PQLSyntax::AND) {
		pqlLexer->getName();  // AND
		result.push_back(parseRelationship());
	}

	return result;
}


std::string PQLParser::getExpressionSpecString() {
	std::string expressionString = "";

	while (!pqlLexer->isNextChar(PQLSyntax::QUOTE)) {
		expressionString += pqlLexer->getNextChar();
		if (pqlLexer->reachedEnd()) {
			// Reached end of pqlLexer when expr not parsed, eg. pattern a (_, "1)
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
	}
	if (expressionString.empty()) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}
	std::string result;
	try {
		ExpressionParser exprParser = ExpressionParser(new Lexer(expressionString));
		ExpressionNode* exprNode = exprParser.extractExpressionNode(0);
		result = flatten(exprNode);
	} catch (SyntaxError e) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	return result;
}


PQLExpression PQLParser::parseExpressionSpec() {
	PQLExpressionType pqlExpressionType;
	std::string pqlExpressionSpec;
	if (pqlLexer->isNextChar(PQLSyntax::UNDERSCORE)) {
		if (pqlLexer->isNextChar(PQLSyntax::QUOTE)) {
			pqlExpressionType = PQLExpressionType::MIXED;
			pqlExpressionSpec = getExpressionSpecString();
			if (!pqlLexer->isNextChar(PQLSyntax::UNDERSCORE)) {
				throw QPSException(QPSException::QPS_SYNTAX_ERROR);
			}
		} else {
			pqlExpressionType = PQLExpressionType::WILDCARD;
			pqlExpressionSpec = PQLSyntax::UNDERSCORE;
		}
	} else if (pqlLexer->isNextChar(PQLSyntax::QUOTE)) {
		pqlExpressionType = PQLExpressionType::FULL;
		pqlExpressionSpec = getExpressionSpecString();
	} else {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	return PQLExpression(pqlExpressionType, pqlExpressionSpec);
}

PQLPatternType PQLParser::getPatternType(std::string assignSyn, const std::vector<PQLDeclaration>& declarations) {
	for (const PQLDeclaration& declaration : declarations) {
		if (declaration.second == assignSyn) {
			switch (declaration.first) {
			case EntityType::ASSIGN:
				return PQLPatternType::PATTERN_A;
			case EntityType::WHILE:
				return PQLPatternType::PATTERN_W;
			case EntityType::IF:
				return PQLPatternType::PATTERN_I;
			default:
				break;
			}
			break;  // break from while for loop
		}
	}

	return PQLPatternType::PATTERN_UNKNOWN;
}

PQLPattern PQLParser::parsePattern(const std::vector<PQLDeclaration>& declarations) {
	std::string assignSyn = pqlLexer->getName();
	PQLPatternType patternType = getPatternType(assignSyn, declarations);

	if (!pqlLexer->isNextChar(PQLSyntax::LEFT_BRACKET)) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}
	PQLReference entRef = parseReference();

	if (PQLCommon::ENT_REF.find(entRef.first) == PQLCommon::ENT_REF.end()) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	if (!pqlLexer->isNextChar(PQLSyntax::COMMA)) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	PQLExpression expr = parseExpressionSpec();
	size_t numArgs = 2;

	if (pqlLexer->isNextChar(PQLSyntax::COMMA)) {
		PQLExpression expr2 = parseExpressionSpec();
		if (expr.first != PQLExpressionType::WILDCARD ||
			expr2.first != PQLExpressionType::WILDCARD)
		{
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
		numArgs++;
	}

	if (!pqlLexer->isNextChar(PQLSyntax::RIGHT_BRACKET)) {  // check for ')'
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	return PQLPattern(assignSyn, patternType, entRef, expr, numArgs);
}

std::vector<PQLPattern> PQLParser::parsePatterns(const std::vector<PQLDeclaration>& declarations) {
	if (pqlLexer->getName() != PQLSyntax::PATTERN) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	std::vector<PQLPattern> result;

	result.push_back(parsePattern(declarations));

	while (pqlLexer->nextName() == PQLSyntax::AND) {
		pqlLexer->getName();  // AND
		result.push_back(parsePattern(declarations));
	}

	return result;
}

PQLWith PQLParser::parseWith() {
	PQLReference lhs = parseAttribute();

	if (!pqlLexer->isNextChar(PQLSyntax::EQUAL)) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	PQLReference rhs = parseAttribute();

	return PQLWith(lhs, rhs);
}


std::vector<PQLWith> PQLParser::parseWithClauses() {
	if (pqlLexer->getName() != PQLSyntax::WITH) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	std::vector<PQLWith> result;
	result.push_back(parseWith());
	while (pqlLexer->nextName() == PQLSyntax::AND) {
		pqlLexer->getName();  // AND
		result.push_back(parseWith());
	}
	return result;
}

/*
Advanced SPA page 37, tuple: elem | '<' elem (',' elem)* '>'
*/
PQLReference PQLParser::parseElement() {
	PQLReferenceType refType = PQLReferenceType::SYNONYM;
	std::string syn = pqlLexer->getName();
	if (syn.empty()) {
		throw QPSException(QPSException::QPS_SYNTAX_ERROR);
	}

	if (pqlLexer->isNextChar(PQLSyntax::DOT)) {
		std::string attr = pqlLexer->getName();
		if (pqlLexer->isNextChar(PQLSyntax::HASH)) {
			attr += PQLSyntax::HASH;  // covers stmt#
		}
		if (attrRefMap.find(attr) == attrRefMap.end()) {
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
		refType = attrRefMap.at(attr);
	}

	return PQLReference(refType, syn);
}

PQLReference PQLParser::parseAttribute() {
	PQLReferenceType actualRefType;
	std::string refString;

	if (pqlLexer->isNextChar(PQLSyntax::QUOTE)) {
		refString = pqlLexer->getName();
		if (refString.empty()) {
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
		if (!pqlLexer->isNextChar(PQLSyntax::QUOTE)) {
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
		actualRefType = PQLReferenceType::IDENT;
	} else {
		refString = pqlLexer->getInteger();
		if (!refString.empty()) {
			actualRefType = PQLReferenceType::INTEGER;
		} else {
			refString = pqlLexer->getName();
			if (refString.empty()) {
				throw QPSException(QPSException::QPS_SYNTAX_ERROR);
			}
			if (!pqlLexer->isNextChar(PQLSyntax::DOT)) {
				throw QPSException(QPSException::QPS_SYNTAX_ERROR);
			}
			std::string attrRef = pqlLexer->getName();
			if (pqlLexer->isNextChar(PQLSyntax::HASH)) {
				attrRef += PQLSyntax::HASH;  // covers stmt#
			}
			if (attrRefMap.find(attrRef) == attrRefMap.end()) {
				throw QPSException(QPSException::QPS_SYNTAX_ERROR);
			}
			actualRefType = attrRefMap.at(attrRef);
		}
	}
	return PQLReference(actualRefType, refString);
}


/*
Parses the PQL Query into a QueryObject (intermediate representation)
*/
PQLQueryObject PQLParser::parseQuery(std::string queryString) {
	pqlLexer = new Lexer(queryString);
	std::vector<PQLDeclaration> pqlDeclarations = parseDeclarations();
	std::vector<PQLReference> pqlSynonym = parseSelects(pqlDeclarations);
	std::vector<PQLRelationship> pqlRelationship;
	std::vector<PQLPattern> pqlPattern;
	std::vector<PQLWith> pqlWithClauses;

	while (!pqlLexer->reachedEnd()) {
		if (pqlLexer->nextName() == PQLSyntax::SUCH) {
			// Parse Relationships
			std::vector<PQLRelationship> rels = parseRelationships();
			pqlRelationship.insert(pqlRelationship.end(), rels.begin(), rels.end());
		} else if (pqlLexer->nextName() == PQLSyntax::PATTERN) {
			// Parse Patterns
			std::vector<PQLPattern> pats = parsePatterns(pqlDeclarations);
			pqlPattern.insert(pqlPattern.end(), pats.begin(), pats.end());
		} else if (pqlLexer->nextName() == PQLSyntax::WITH) {
			// Parse With clauses
			std::vector<PQLWith> withs = parseWithClauses();
			pqlWithClauses.insert(pqlWithClauses.end(), withs.begin(), withs.end());
		} else {
			// Unexpected string
			throw QPSException(QPSException::QPS_SYNTAX_ERROR);
		}
	}

	return PQLQueryObject(pqlDeclarations, pqlSynonym, pqlRelationship, pqlPattern, pqlWithClauses);
}

