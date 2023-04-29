#include "PKBStorageAPI.h"

PKBStorageAPI::PKBStorageAPI(PKB* pkb): pkb(pkb) {}

void PKBStorageAPI::insertAssign(StmtIndex stmtNum, std::string varName) {
	pkb->assignManager->insertAssign(stmtNum, varName);
}

void PKBStorageAPI::insertConst(StmtIndex stmtNum, std::vector<ConstValue> constLst) {
	pkb->constantManager->insertConst(stmtNum, constLst);
}

void PKBStorageAPI::insertStmtExpressionLst(StmtIndex stmtNum, std::string expression) {
	pkb->patternManager->insertStmtExpressionLst(stmtNum, expression);
}

void PKBStorageAPI::insertStmtExactExpression(StmtIndex stmtNum, std::string expression) {
	pkb->patternManager->insertStmtExactExpression(stmtNum, expression);
}

void PKBStorageAPI::insertPrint(StmtIndex stmtNum, std::string varName) {
	pkb->printManager->insertPrint(stmtNum, varName);
}

void PKBStorageAPI::insertProc(StmtIndex startStmtNum, StmtIndex endStmtNum, std::string procName) {
	pkb->procedureManager->insertProc(startStmtNum, endStmtNum, procName);
}

void PKBStorageAPI::insertProcCall(StmtIndex stmtNum, std::string procName, std::string callerProcName) {
	pkb->procCallManager->insertProcCall(stmtNum, procName, callerProcName);
}

void PKBStorageAPI::insertRead(StmtIndex stmtNum, std::string varName) {
	pkb->readManager->insertRead(stmtNum, varName);
}

void PKBStorageAPI::insertStmt(StmtIndex stmtNum, StatementType stmtType) {
	pkb->statementManager->insertStmt(stmtNum, stmtType);
}

void PKBStorageAPI::insertVar(StmtIndex stmtNum, std::string varName) {
	pkb->variableManager->insertVar(stmtNum, varName);
}

void PKBStorageAPI::insertWhileContainer(StmtIndex startStmtNum, StmtIndex endStmtNum) {
	pkb->whileManager->insertWhileContainer(startStmtNum, endStmtNum);
}

void PKBStorageAPI::insertIfContainer(std::vector<std::vector<StmtIndex>> containerBlockStmtLst) {
	pkb->ifManager->insertIfContainer(containerBlockStmtLst);
}

void PKBStorageAPI::setRelationship(RelationshipType relationshipType, StmtIndex s1, StmtIndex s2) {
	if (relationshipType == RelationshipType::FOLLOWS) {
		pkb->followsManager->insertFollows(s1, s2);
	}
}

void PKBStorageAPI::setRelationship(RelationshipType relationshipType,
	StmtIndex s1, std::vector<StmtIndex> s2Lst)  // FollowsT, Parent, ParentT
{
	if (relationshipType == RelationshipType::PARENT) {
		pkb->parentManager->insertParent(s1, s2Lst);
	} else if (relationshipType == RelationshipType::FOLLOWS_T) {
		pkb->followsTManager->insertFollowsT(s1, s2Lst);
	} else if (relationshipType == RelationshipType::PARENT_T) {
		pkb->parentTManager->insertParentT(s1, s2Lst);
	} else if (relationshipType == RelationshipType::NEXT) {
		pkb->nextManager->insertNext(s1, s2Lst);
	}
}

void PKBStorageAPI::setRelationship(RelationshipType relationshipType,
	StmtIndex stmtNum, std::vector<std::string> varLst)  // usesS, modidiesS
{
	if (relationshipType == RelationshipType::USES_S) {
		pkb->usesSManager->insertUsesS(stmtNum, varLst);
	} else if (relationshipType == RelationshipType::MODIFIES_S) {
		pkb->modifiesSManager->insertModifiesS(stmtNum, varLst);
	}
}

void PKBStorageAPI::setRelationship(RelationshipType relationshipType,
	std::string procName, std::vector<std::string> varLst)  // usesP, modifiesP
{
	if (relationshipType == RelationshipType::USES_P) {
		pkb->usesPManager->insertUsesP(procName, varLst);
	} else if (relationshipType == RelationshipType::MODIFIES_P) {
		pkb->modifiesPManager->insertModifiesP(procName, varLst);
	}
}

void PKBStorageAPI::setRelationship(RelationshipType relationshipType,
	std::string procName, std::unordered_set<std::string> procLst)
{
	if (relationshipType == RelationshipType::CALL) {
		pkb->callsManager->insertCalls(procName, procLst);
	} else if (relationshipType == RelationshipType::CALL_T) {
		pkb->callsTManager->insertCallsT(procName, procLst);
	}
}

void PKBStorageAPI::updateProcCall(std::string procName, std::string callerProcName) {
	pkb->usesPManager->insertProcCall(procName, callerProcName);
	pkb->modifiesPManager->insertProcCall(procName, callerProcName);
}

void PKBStorageAPI::updateAllProcCalls(size_t n) {
	for (size_t i = 0; i < n; i++) {
		updateAllProcCalls();
	}
}

void PKBStorageAPI::updateWhileContainers(StmtIndex stmtNum,
	const std::vector<std::string>& usesPVarLst,
	const std::vector<std::string>& modifiesPVarLst)
{
	// get while containers containing procCalls
	std::vector<std::vector<std::string>> whileContainers = pkb->whileManager->getWhileContainerRangeFromStmtIdx(stmtNum);
	if (whileContainers.empty()) {
		return;
	}
	// update variables for while condition statements
	for (std::vector<std::string> whileContainer : whileContainers) {
		if (!whileContainer.empty()) {
			StmtIndex whileStartStmtIdx = std::stoi(whileContainer.front());
			pkb->usesSManager->insertUsesS(whileStartStmtIdx, usesPVarLst);
			pkb->modifiesSManager->insertModifiesS(whileStartStmtIdx, modifiesPVarLst);
		}
	}
}

void PKBStorageAPI::updateIfContainers(StmtIndex stmtNum,
	const std::vector<std::string>& usesPVarLst,
	const std::vector<std::string>& modifiesPVarLst)
{
	// get if containers containing procCalls
	std::vector<std::vector<std::string>> ifContainers = pkb->ifManager->getIfContainerRangeFromStmtIdx(stmtNum);
	if (ifContainers.empty()) {
		return;
	}
	// update variables for if condition statements
	for (std::vector<std::string> ifContainer : ifContainers) {
		if (!ifContainer.empty()) {
			StmtIndex ifStartStmtIdx = std::stoi(ifContainer.front());
			pkb->usesSManager->insertUsesS(ifStartStmtIdx, usesPVarLst);
			pkb->modifiesSManager->insertModifiesS(ifStartStmtIdx, modifiesPVarLst);
		}
	}
}

void PKBStorageAPI::updateAllProcCalls() {
	std::vector<std::string> callerProcLst = pkb->procCallManager->getAllCallerProcs();
	for (auto& callerProc : callerProcLst) {
		std::vector<std::string> procCallLst = pkb->procCallManager->getProcCallLstFromCallerProc(callerProc);
		for (auto& call : procCallLst) {
			updateProcCall(call, callerProc);
		}
	}
	// get list of proc call statement numbers
	std::vector<std::string> procCallLst = pkb->procCallManager->getAllProcCalls();
	std::vector<std::string> usesPVarLst;
	std::vector<std::string> modifiesPvarLst;
	for (auto& procCallStmt : procCallLst) {
		StmtIndex stmtNum = std::stoi(procCallStmt);  // get statement number for procCall
		std::vector<std::string> procCallContainer = pkb->procCallManager->getProcCallFromStmtIdx(stmtNum);
		std::string procCall = procCallContainer.at(0);  // get name of proc call statement
		// get usesP var list for given proc call
		usesPVarLst = pkb->usesPManager->getUsesPVarLstFromProc(procCall);
		// get modifiesP var list for given proc call
		modifiesPvarLst = pkb->modifiesPManager->getModifiesPVarLstFromProc(procCall);

		// update variables for while condition statements
		updateWhileContainers(stmtNum, usesPVarLst, modifiesPvarLst);
		// update variables for if condition statements
		updateIfContainers(stmtNum, usesPVarLst, modifiesPvarLst);

		// update variables for proccall statement
		pkb->usesSManager->insertUsesS(stmtNum, usesPVarLst);
		pkb->modifiesSManager->insertModifiesS(stmtNum, modifiesPvarLst);
	}
}
