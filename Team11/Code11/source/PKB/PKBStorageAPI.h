#pragma once

#include "../PKB/PKB.h"
#include "../Common/Types.h"

// Interface for SP to interact with PKB
class PKBStorageAPI {
private:
	PKB* pkb;

	void updateAllProcCalls();
	void updateIfContainers(StmtIndex stmtNum,
		const std::vector<std::string>& usesPVarLst,
		const std::vector<std::string>& modifiesPvarLst);
	void updateWhileContainers(StmtIndex stmtNum,
		const std::vector<std::string>& usesPVarLst,
		const std::vector<std::string>& modifiesPvarLst);

public:
	explicit PKBStorageAPI(PKB* pkb);
	void insertAssign(StmtIndex stmtNum, std::string varName);
	void insertConst(StmtIndex stmtNum, std::vector<ConstValue> constLst);
	void insertStmtExpressionLst(StmtIndex stmtNum, std::string expression);
	void insertStmtExactExpression(StmtIndex stmtNum, std::string expression);
	void insertPrint(StmtIndex stmtNum, std::string varName);
	void insertProc(StmtIndex startStmtNum, StmtIndex endStmtNum, std::string procName);
	void insertProcCall(StmtIndex stmtNum, std::string procName, std::string callerProcName);
	void insertRead(StmtIndex stmtNum, std::string varName);
	void insertStmt(StmtIndex stmtNum, StatementType stmtType);
	void insertVar(StmtIndex stmtNum, std::string varName);
	void insertWhileContainer(StmtIndex startStmtNum, StmtIndex endStmtNum);
	void insertIfContainer(std::vector<std::vector<StmtIndex>> containerBlockStmtLst);

	void updateProcCall(std::string procName, std::string callerProcName);
	void updateAllProcCalls(size_t n);

	// Follow
	void setRelationship(RelationshipType relationshipType, StmtIndex s1, StmtIndex s2);
	// FollowsT, Parent, ParentT, Next
	void setRelationship(RelationshipType relationshipType, StmtIndex s1, std::vector<StmtIndex> s2Lst);
	// usesS, modidiesS
	void setRelationship(RelationshipType relationshipType, StmtIndex stmtNum, std::vector<std::string> varLst);
	// usesP, modifiesP
	void setRelationship(RelationshipType relationshipType, std::string procName, std::vector<std::string> varLst);
	// Calls, CallsT
	void setRelationship(RelationshipType relationshipType, std::string procName, std::unordered_set<std::string> procLst);
};
