#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include "../../Common/Types.h"
#include "PQLSyntax.h"

enum class PQLPatternType
{
	PATTERN_UNKNOWN,
	PATTERN_A,  // assign
	PATTERN_W,  // while
	PATTERN_I,  // If
};

/* 1/9/2022
Reference to LectureNotes - BASIC_SPA pg 64
stmtRef: SYNONYM | WILDCARD | INTEGER
entRef: SYNONYM | WILDCARD | IDENT ("IDENT")
*/
enum class PQLReferenceType
{
	SYNONYM,
	WILDCARD,   // _
	INTEGER,
	IDENT,	    // "IDENT"

	PROC_NAME,  // procName
	VAR_NAME,   // varName
	VALUE,      // value
	STMT_NO,    // stmt#

	BOOLEAN	    // BOOLEAN
};

enum class PQLExpressionType
{
	FULL,		// expr
	MIXED,		// _ expr _
	WILDCARD    // _
};


// declaration
typedef std::pair<EntityType, std::string> PQLDeclaration;

// synonym
typedef std::string PQLSynonym;

// syn-assign in pattern-cl
typedef std::pair<PQLPatternType, std::string> PQLSynAssign;

// [stmtRef | entRef, name], eg. [PQLReferenceType.SYNONYM, "a"] as lhs of Uses (a, _)
typedef std::pair<PQLReferenceType, std::string> PQLReference;

// expression-spec
typedef std::pair<PQLExpressionType, std::string> PQLExpression;

typedef std::unordered_map<std::string, EntityType> DeclareMap;

typedef std::unordered_map<std::string, std::vector<std::string>> StringMap;

class PQLCommon {
public:
	static const std::unordered_set<PQLReferenceType> STMT_REF;
	static const std::unordered_set<PQLReferenceType> ENT_REF;
	static const std::unordered_set<PQLReferenceType> UM_LHS;

	static const std::unordered_set<PQLReferenceType> PROC_REF;

	static const std::unordered_map <RelationshipType,
		std::pair<std::unordered_set<PQLReferenceType>, std::unordered_set<PQLReferenceType>>> VALID_REL_ARGS;

	static const std::unordered_map<RelationshipType, std::unordered_set<EntityType>> VALID_UM_LHS_ENTITY_TYPE;
	static const std::unordered_map<RelationshipType, std::unordered_set<EntityType>> VALID_UM_RHS_ENTITY_TYPE;
	static const std::unordered_map<PQLPatternType, EntityType> VALID_PATTERN_ENTITY_TYPE;
	static const std::unordered_map<EntityType, std::unordered_set<PQLReferenceType>> VALID_WITH_ATTRIBUTES;
	static const std::unordered_set<PQLReferenceType> WITH_ATTRIBUTE_TYPES;
	static const std::unordered_map<PQLReferenceType, PQLReferenceType> ATTRIBUTE_REF_TYPE;
	static const std::unordered_map<PQLReferenceType, std::unordered_set<EntityType>> VALID_ATTRIBUTES;

	// [Follows, Follows*, Parent, Parent*, Uses (Uses_S, Uses_P), Modifies (Modifies_S, Modifies_P)]
	static const std::unordered_map<std::string, RelationshipType> RELATIONSHIP_MAP;

	static std::string entTypeToString(EntityType entType);

	static std::string vectorHash(size_t index,
		const StringMap& resMap,
		const std::vector<std::string>& vectorToHash);

	static std::vector<std::string> getSynonymVectorFromHash(std::string hashString);

	static std::string vectorHash(const std::vector<std::string>& vectorToHash);

	static const int WITH_BASE_PRIORITY;
	static const int PATTERN_BASE_PRIORITY;
	static const int MODIFIES_FOLLOWS_BASE_PRIORITY;
	static const int PATTERN_WILDCARD_AND_REL_BASE_PRIORITY;
	static const int AFFECTS_PRIORITY;
	static const int AFFECTST_NEXTT_PRIORITY;
};
