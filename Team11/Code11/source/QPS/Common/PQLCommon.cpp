#include "PQLCommon.h"

const std::unordered_set<PQLReferenceType> PQLCommon::STMT_REF = {
	PQLReferenceType::SYNONYM,
	PQLReferenceType::WILDCARD,
	PQLReferenceType::INTEGER
};
const std::unordered_set<PQLReferenceType> PQLCommon::ENT_REF = {
	PQLReferenceType::SYNONYM,
	PQLReferenceType::WILDCARD,
	PQLReferenceType::IDENT
};

const std::unordered_set<PQLReferenceType> PQLCommon::UM_LHS = {
	PQLReferenceType::SYNONYM,
	PQLReferenceType::INTEGER,
	PQLReferenceType::IDENT,
	PQLReferenceType::WILDCARD
};

const std::unordered_set<PQLReferenceType> PQLCommon::PROC_REF = {
	PQLReferenceType::IDENT,
	PQLReferenceType::SYNONYM,
	PQLReferenceType::WILDCARD,
};


const std::unordered_map<RelationshipType,
		std::pair<std::unordered_set<PQLReferenceType>, std::unordered_set<PQLReferenceType>>> PQLCommon::VALID_REL_ARGS = {
	// PQL Relationship Type		  :				lhs type			 rhs type
	{ RelationshipType::FOLLOWS,		{ PQLCommon::STMT_REF, PQLCommon::STMT_REF } },
	{ RelationshipType::FOLLOWS_T,	{ PQLCommon::STMT_REF, PQLCommon::STMT_REF } },
	{ RelationshipType::PARENT,		{ PQLCommon::STMT_REF, PQLCommon::STMT_REF } },
	{ RelationshipType::PARENT_T,	{ PQLCommon::STMT_REF, PQLCommon::STMT_REF } },
	{ RelationshipType::USES_S,		{ PQLCommon::STMT_REF, PQLCommon::ENT_REF } },
	{ RelationshipType::MODIFIES_S,	{ PQLCommon::STMT_REF, PQLCommon::ENT_REF } },
	{ RelationshipType::USES_P,		{ PQLCommon::ENT_REF, PQLCommon::ENT_REF } },
	{ RelationshipType::MODIFIES_P,	{ PQLCommon::ENT_REF, PQLCommon::ENT_REF } },
	{ RelationshipType::CALL,	    { PQLCommon::PROC_REF, PQLCommon::PROC_REF } },
	{ RelationshipType::CALL_T,	    { PQLCommon::PROC_REF, PQLCommon::PROC_REF } },
	{ RelationshipType::NEXT,	    { PQLCommon::STMT_REF, PQLCommon::STMT_REF } },
	{ RelationshipType::NEXT_T,	    { PQLCommon::STMT_REF, PQLCommon::STMT_REF } },
	{ RelationshipType::AFFECTS,    { PQLCommon::STMT_REF, PQLCommon::STMT_REF } },
	{ RelationshipType::AFFECTS_T,    { PQLCommon::STMT_REF, PQLCommon::STMT_REF } },
	{ RelationshipType::USES,		{ PQLCommon::UM_LHS, PQLCommon::ENT_REF } },
	{ RelationshipType::MODIFIES,	{ PQLCommon::UM_LHS, PQLCommon::ENT_REF } },
};

const std::unordered_map<RelationshipType, std::unordered_set<EntityType>> PQLCommon::VALID_UM_LHS_ENTITY_TYPE = {
	{
		RelationshipType::MODIFIES_S, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::READ,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::PRINT,
		}
	},
	{
		RelationshipType::MODIFIES_P, {
			EntityType::PROCEDURE,
			EntityType::CALL
		}
	},
	{
		RelationshipType::USES_S, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::READ,
		}
	},
	{
		RelationshipType::USES_P, {
			EntityType::PROCEDURE,
			EntityType::CALL
		}
	},
	{
		RelationshipType::CALL, {
			EntityType::PROCEDURE,
		}
	},
	{
		RelationshipType::CALL_T, {
			EntityType::PROCEDURE,
		}
	},
	{
		RelationshipType::NEXT, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::READ,
			EntityType::CALL,
		}
	},
	{
		RelationshipType::NEXT_T, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::READ,
			EntityType::CALL,
		}
	},
	{
		RelationshipType::AFFECTS, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::READ,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::PRINT,
			EntityType::CALL,
		}
	},
		{
		RelationshipType::AFFECTS_T, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::READ,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::PRINT,
			EntityType::CALL,
		}
	}
};

const std::unordered_map<RelationshipType, std::unordered_set<EntityType>> PQLCommon::VALID_UM_RHS_ENTITY_TYPE = {
	{
		RelationshipType::MODIFIES_S, {
			EntityType::VARIABLE
		}
	},
	{
		RelationshipType::MODIFIES_P, {
			EntityType::VARIABLE
		}
	},
	{
		RelationshipType::USES_S, {
			EntityType::VARIABLE
		}
	},
	{
		RelationshipType::USES_P, {
			EntityType::VARIABLE
		}
	},
	{
		RelationshipType::CALL, {
			EntityType::PROCEDURE,
		}
	},
	{
		RelationshipType::CALL_T, {
			EntityType::PROCEDURE,
		}
	},
	{
		RelationshipType::NEXT, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::READ,
			EntityType::CALL,
		}
	},
	{
		RelationshipType::NEXT_T, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::READ,
			EntityType::CALL,
		}
	},
	{
		RelationshipType::AFFECTS, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::READ,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::PRINT,
			EntityType::CALL,
		}
	},
		{
		RelationshipType::AFFECTS_T, {
			EntityType::STMT,
			EntityType::ASSIGN,
			EntityType::PRINT,
			EntityType::READ,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::PRINT,
			EntityType::CALL,
		}
	}
};

const std::unordered_map<PQLPatternType, EntityType> PQLCommon::VALID_PATTERN_ENTITY_TYPE = {
	{PQLPatternType::PATTERN_A, EntityType::ASSIGN},
	{PQLPatternType::PATTERN_I, EntityType::IF},
	{PQLPatternType::PATTERN_W, EntityType::WHILE}
};

const std::unordered_map<EntityType, std::unordered_set<PQLReferenceType>> PQLCommon::VALID_WITH_ATTRIBUTES = {
	{ EntityType::STMT,			{ PQLReferenceType::STMT_NO } },
	{ EntityType::ASSIGN,		{ PQLReferenceType::STMT_NO } },
	{ EntityType::WHILE,		{ PQLReferenceType::STMT_NO } },
	{ EntityType::IF,			{ PQLReferenceType::STMT_NO } },
	{ EntityType::PROCEDURE,	{ PQLReferenceType::PROC_NAME } },
	{ EntityType::CALL,			{ PQLReferenceType::PROC_NAME, PQLReferenceType::STMT_NO } },
	{ EntityType::VARIABLE,		{ PQLReferenceType::VAR_NAME } },
	{ EntityType::READ,			{ PQLReferenceType::VAR_NAME, PQLReferenceType::STMT_NO } },
	{ EntityType::PRINT,		{ PQLReferenceType::VAR_NAME, PQLReferenceType::STMT_NO } },
	{ EntityType::CONSTANT,		{ PQLReferenceType::VALUE } }
};

const std::unordered_set<PQLReferenceType> PQLCommon::WITH_ATTRIBUTE_TYPES = {
	PQLReferenceType::PROC_NAME,
	PQLReferenceType::VAR_NAME,
	PQLReferenceType::VALUE,
	PQLReferenceType::STMT_NO
};

const std::unordered_map<PQLReferenceType, PQLReferenceType> PQLCommon::ATTRIBUTE_REF_TYPE = {
	{ PQLReferenceType::IDENT,		PQLReferenceType::IDENT },
	{ PQLReferenceType::PROC_NAME,	PQLReferenceType::IDENT },
	{ PQLReferenceType::VAR_NAME,	PQLReferenceType::IDENT },
	{ PQLReferenceType::VALUE,		PQLReferenceType::INTEGER },
	{ PQLReferenceType::STMT_NO,	PQLReferenceType::INTEGER },
	{ PQLReferenceType::INTEGER,	PQLReferenceType::INTEGER },
	// NO WILDCARD
	// NO BOOLEAN
	// NO SYNONYM
};

const std::unordered_map<PQLReferenceType, std::unordered_set<EntityType>> PQLCommon::VALID_ATTRIBUTES = {
	{
		PQLReferenceType::PROC_NAME, {
			EntityType::PROCEDURE,
			EntityType::CALL
		}
	},
	{
		PQLReferenceType::VAR_NAME, {
			EntityType::PRINT,
			EntityType::VARIABLE,
			EntityType::READ
		}
	},
	{
		PQLReferenceType::STMT_NO, {
			EntityType::ASSIGN,
			EntityType::CALL,
			EntityType::IF,
			EntityType::WHILE,
			EntityType::PRINT,
			EntityType::READ,
			EntityType::STMT
		}
	},
	{
		PQLReferenceType::VALUE, {
			EntityType::CONSTANT
		}
	}
};


std::string PQLCommon::entTypeToString(EntityType entType) {
	switch (entType) {
	case EntityType::ASSIGN:
		return "ASSIGN";
	case EntityType::PROCEDURE:
		return "PROCEDURE";
	case EntityType::STMT:
		return "STMT";
	case EntityType::CALL:
		return "CALL";
	case EntityType::READ:
		return "READ";
	case EntityType::PRINT:
		return "PRINT";
	case EntityType::CONSTANT:
		return "CONSTANT";
	case EntityType::WHILE:
		return "WHILE";
	case EntityType::IF:
		return "IF";
	case EntityType::VARIABLE:
		return "VAR";
	default:
		return "??";
	}
}

const std::unordered_map<std::string, RelationshipType> PQLCommon::RELATIONSHIP_MAP = {
	{ "Follows",	RelationshipType::FOLLOWS },
	{ "Follows*",	RelationshipType::FOLLOWS_T },
	{ "Parent",		RelationshipType::PARENT },
	{ "Parent*",	RelationshipType::PARENT_T },
	{ "Uses",		RelationshipType::USES },
	{ "Modifies",	RelationshipType::MODIFIES },
	{ "Calls",		RelationshipType::CALL },
	{ "Calls*",		RelationshipType::CALL_T },
	{ "Next",		RelationshipType::NEXT },
	{ "Next*",		RelationshipType::NEXT_T },
	{ "Affects",	RelationshipType::AFFECTS },
	{ "Affects*",	RelationshipType::AFFECTS_T },

	{ "Uses_P",		RelationshipType::USES_P },
	{ "Modifies_P",	RelationshipType::MODIFIES_P },
	{ "Uses_S",		RelationshipType::USES_S },
	{ "Modifies_S",	RelationshipType::MODIFIES_S },
};


std::string PQLCommon::vectorHash(size_t index,
	const StringMap& resMap,
	const std::vector<std::string>& vectorToHash)
{
	std::string colVals = "";
	for (size_t j = 0; j < vectorToHash.size(); j++) {
		colVals += (j == 0 ? "" : PQLSyntax::SPACE);
		colVals += resMap.at(vectorToHash[j]).at(index);
	}
	return colVals;
}

std::vector<std::string> PQLCommon::getSynonymVectorFromHash(std::string hashString) {
	std::vector<std::string> sharedSynCols;
	std::string key = hashString;
	size_t pos = 0;
	std::string token;
	while ((pos = key.find(PQLSyntax::SPACE)) != std::string::npos) {
		token = key.substr(0, pos);
		sharedSynCols.push_back(token);
		key.erase(0, pos + 1);
	}
	sharedSynCols.push_back(key);
	return sharedSynCols;
}

std::string PQLCommon::vectorHash(const std::vector<std::string>& vectorToHash) {
	std::string colVals = "";
	for (size_t j = 0; j < vectorToHash.size(); j++) {
		colVals += (j == 0 ? "" : PQLSyntax::SPACE);
		colVals += vectorToHash[j];
	}
	return colVals;
}

const int PQLCommon::WITH_BASE_PRIORITY = 0;
const int PQLCommon::PATTERN_BASE_PRIORITY = 5;
const int PQLCommon::MODIFIES_FOLLOWS_BASE_PRIORITY = 2;
const int PQLCommon::PATTERN_WILDCARD_AND_REL_BASE_PRIORITY = 7;
const int PQLCommon::AFFECTS_PRIORITY = 10;
const int PQLCommon::AFFECTST_NEXTT_PRIORITY = 11;
