#pragma once

#include "../PKB/PKB.h"
#include "../Common/Types.h"
#include "../Common/SPAException.h"

// Interface for QPS to interact with PKB
class PKBQueryAPI {
private:
	PKB* pkb;

public:
	explicit PKBQueryAPI(PKB* pkb);

	// return statement type for given statement
	std::vector<StatementType> getStmtTypeFromStmtIdx(StmtIndex stmtNum);
	// return var assigned for given statement
	std::vector<std::string> getAssignmentFromStmtIdx(StmtIndex stmtNum);
	// return list of expressions found in given statement
	std::vector<std::string> getExpressionLstFromStmtIdx(StmtIndex stmtNum);
	// return procedure that statement belongs to
	std::vector<std::string> getProcedureFromStmtIdx(StmtIndex stmtNum);
	// return list of statements that called given procedure
	std::vector<std::string> getStmtLstFromProcCall(std::string procName);
	// return list of statements containing full rhs expression
	std::vector<std::string> getStmtLstFromExactExpression(std::string expression);
	// return list of variable that appear in given statement
	std::vector<std::string> getVarLstFromStmtIdx(StmtIndex stmtNum);
	// return container range for given statement
	std::vector<std::vector<std::string>> getContainerRangeFromStmtIdx(StatementType stmtType, StmtIndex stmtNum);

	// return all assignments' stmtNum
	std::vector<std::string> getAllAssignments() const;
	// return all constants
	std::vector<std::string> getAllConsts() const;
	// return all if-containers' startStmtNum
	std::vector<std::string> getAllIfContainers() const;
	// return all print statements
	std::vector<std::string> getAllPrints() const;
	// return all procedure names
	std::vector<std::string> getAllProcedures() const;
	// return all procedure calls' stmtNum
	std::vector<std::string> getAllProcCalls() const;
	// return all read statements
	std::vector<std::string> getAllReads() const;
	// return all the statement numbers
	std::vector<std::string> getAllStmts() const;
	// return all variables
	std::vector<std::string> getAllVars() const;
	// return all while-containers' startStmtNum
	std::vector<std::string> getAllWhileContainers() const;


	// Get NAMES for With Evaluator
	std::pair<std::vector<std::string>, std::vector<std::string>> getAttributeNames(EntityType entType);
	std::string getAttributeName(EntityType entType, StmtIndex idx);

	// return list of possible (left arg: stmtNum) given (right arg: stmtNum) : Follows/FollowsT/Parent/ParentT/Next
	std::vector<std::string> getRelationshipLeftArg(RelationshipType relationshipType, StmtIndex rightArg);

	/*
	returns
	list of possible(left arg : procName) given(right arg : procName) : Calls / CallsT
	list of possible(left arg : stmtNum) given(right arg : varName) : UsesS / ModifiesSs
	*/
	std::vector<std::string> getRelationshipLeftArg(RelationshipType relationshipType, std::string rightArg);

	/*
	return list of possible(right arg : varName) given(left arg : stmtNum): 
	Follows / FollowsT / Parent / ParentT / Next / UsesS / ModifiesS
	*/
	std::vector<std::string> getRelationshipRightArg(RelationshipType relationshipType, StmtIndex leftArg);

	// return list of possible (right arg: procName) given (left arg: procName) : Calls/CallsT/UsesP/ModifiesP
	std::vector<std::string> getRelationshipRightArg(RelationshipType relationshipType, std::string leftArg);

	std::unordered_map<std::string, std::vector<std::string>> getUsesSTable();		  // return usesS table;
	std::unordered_map<std::string, std::vector<std::string>> getUsesPTable();		  // return UsesP table;
	std::unordered_map<std::string, std::vector<std::string>> getModifiesSTable();	  // return ModifiesS table;
	std::unordered_map<std::string, std::vector<std::string>> getModifiesPTable();	  // return ModifiesP table;
};
