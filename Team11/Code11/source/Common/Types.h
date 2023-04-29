#pragma once

enum class StatementType {
	READ_STMT, PRINT_STMT, ASSIGN_STMT, CALL_STMT, WHILE_STMT, IF_STMT
};

enum class EntityType {
	PROCEDURE, STMT, READ, PRINT, ASSIGN, CALL, WHILE, IF, VARIABLE, CONSTANT
};

enum class RelationshipType {
	FOLLOWS, FOLLOWS_T, PARENT, PARENT_T, USES, USES_S, USES_P, MODIFIES,
	MODIFIES_S, MODIFIES_P, NEXT, NEXT_T, CALL, CALL_T, AFFECTS, AFFECTS_T
};

enum class ExpressionType {
	VARIABLE, CONSTANT, COND_EXPR, EXP_OPR, TERM_OPR, LOGICAL_OPR, REL_EXPR
};

enum class ExpressionPos {
	RHS, LHS  // DEFAULT as RHS
};

enum class TableDirection {
	LEFTKEY, RIGHTKEY
};

typedef int ConstValue;
typedef int StmtIndex;
typedef int ContainerBlockIndex;
