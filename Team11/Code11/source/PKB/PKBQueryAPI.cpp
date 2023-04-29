
#include "PKBQueryAPI.h"

PKBQueryAPI::PKBQueryAPI(PKB* pkb): pkb(pkb) {}

std::vector<StatementType> PKBQueryAPI::getStmtTypeFromStmtIdx(StmtIndex stmtNum) {
	return pkb->statementManager->getStmtTypeFromStmtIdx(stmtNum);
}

std::vector<std::string> PKBQueryAPI::getAssignmentFromStmtIdx(StmtIndex stmtNum) {
	return pkb->assignManager->getAssignmentFromStmtIdx(stmtNum);
}

std::vector<std::string> PKBQueryAPI::getExpressionLstFromStmtIdx(StmtIndex stmtNum) {
	return pkb->patternManager->getExpressionLstFromStmt(stmtNum);
}

std::vector<std::string> PKBQueryAPI::getProcedureFromStmtIdx(StmtIndex stmtNum) {
	return pkb->procedureManager->getProcedureFromStmtIdx(stmtNum);
}

std::vector<std::string> PKBQueryAPI::getStmtLstFromProcCall(std::string procName) {
	return pkb->procCallManager->getStmtLstFromProcCall(procName);
}

std::vector<std::string> PKBQueryAPI::getStmtLstFromExactExpression(std::string expression) {
	return pkb->patternManager->getStmtLstFromExactExpression(expression);
}

std::vector<std::string> PKBQueryAPI::getVarLstFromStmtIdx(StmtIndex stmtNum) {
	return pkb->variableManager->getVarLstFromStmtIdx(stmtNum);
}

std::vector<std::vector<std::string>> PKBQueryAPI::getContainerRangeFromStmtIdx(
	StatementType stmtType, StmtIndex stmtNum)
{
	if (stmtType == StatementType::IF_STMT) {
		return pkb->ifManager->getIfContainerRangeFromStmtIdx(stmtNum);
	} else if (stmtType == StatementType::WHILE_STMT) {
		return pkb->whileManager->getWhileContainerRangeFromStmtIdx(stmtNum);
	} else {
		throw SPAException(PKBException::PKB_INVALID_STMT_TYPE);
	}
}

std::vector<std::string> PKBQueryAPI::getAllAssignments() const {
	return pkb->assignManager->getAllAssignments();
}

std::vector<std::string> PKBQueryAPI::getAllConsts() const {
	return pkb->constantManager->getAllConsts();
}

std::vector<std::string> PKBQueryAPI::getAllIfContainers() const {
	return pkb->ifManager->getAllIfContainers();
}

std::vector<std::string> PKBQueryAPI::getAllPrints() const {
	return pkb->printManager->getAllPrints();
}

std::vector<std::string> PKBQueryAPI::getAllProcedures() const {
	return pkb->procedureManager->getAllProcedures();
}

std::vector<std::string> PKBQueryAPI::getAllProcCalls() const {
	return pkb->procCallManager->getAllProcCalls();
}

std::vector<std::string> PKBQueryAPI::getAllReads() const {
	return pkb->readManager->getAllReads();
}

std::vector<std::string> PKBQueryAPI::getAllStmts() const {
	return pkb->statementManager->getAllStmts();
}

std::vector<std::string> PKBQueryAPI::getAllVars() const {
	return pkb->variableManager->getAllVars();
}

std::vector<std::string> PKBQueryAPI::getAllWhileContainers() const {
	return pkb->whileManager->getAllWhileContainers();
}

std::vector<std::string> PKBQueryAPI::getRelationshipLeftArg(
	RelationshipType relationshipType, StmtIndex rightArg)
{
	if (relationshipType == RelationshipType::FOLLOWS) {
		return pkb->followsManager->getFollowLeftArg(rightArg);
	} else if (relationshipType == RelationshipType::FOLLOWS_T) {
		return pkb->followsTManager->getFollowsTLeftArgLst(rightArg);
	} else if (relationshipType == RelationshipType::PARENT) {
		return pkb->parentManager->getParentLeftArgLst(rightArg);
	} else if (relationshipType == RelationshipType::PARENT_T) {
		return pkb->parentTManager->getParentTLeftArgLst(rightArg);
	} else if (relationshipType == RelationshipType::NEXT) {
		return pkb->nextManager->getNextLeftArgLst(rightArg);
	} else {
		throw SPAException(PKBException::PKB_INVALID_RELATIONSHIP_TYPE);
	}
}

std::vector<std::string> PKBQueryAPI::getRelationshipLeftArg(
	RelationshipType relationshipType, std::string rightArg)
{
	if (relationshipType == RelationshipType::CALL) {
		return pkb->callsManager->getCallsLeftArgLst(rightArg);
	} else if (relationshipType == RelationshipType::CALL_T) {
		return pkb->callsTManager->getCallsTLeftArgLst(rightArg);
	} else if (relationshipType == RelationshipType::MODIFIES_S) {
		return pkb->modifiesSManager->getModifiesSLeftArgLst(rightArg);
	} else if (relationshipType == RelationshipType::USES_S) {
		return pkb->usesSManager->getUsesSLeftArgLst(rightArg);
	} else {
		throw SPAException(PKBException::PKB_INVALID_RELATIONSHIP_TYPE);
	}
}

std::vector<std::string> PKBQueryAPI::getRelationshipRightArg(RelationshipType relationshipType,
	StmtIndex leftArg)
{
	if (relationshipType == RelationshipType::FOLLOWS) {
		return pkb->followsManager->getFollowRightArg(leftArg);
	} else if (relationshipType == RelationshipType::FOLLOWS_T) {
		return pkb->followsTManager->getFollowsTRightArgLst(leftArg);
	} else if (relationshipType == RelationshipType::PARENT) {
		return pkb->parentManager->getParentRightArgLst(leftArg);
	} else if (relationshipType == RelationshipType::PARENT_T) {
		return pkb->parentTManager->getParentTRightArgLst(leftArg);
	} else if (relationshipType == RelationshipType::NEXT) {
		return pkb->nextManager->getNextRightArgLst(leftArg);
	} else if (relationshipType == RelationshipType::USES_S) {
		return pkb->usesSManager->getUsesSRightArgLst(leftArg);
	} else if (relationshipType == RelationshipType::MODIFIES_S) {
		return pkb->modifiesSManager->getModifiesSRightArgLst(leftArg);
	} else {
		throw SPAException(PKBException::PKB_INVALID_RELATIONSHIP_TYPE);
	}
}

std::vector<std::string> PKBQueryAPI::getRelationshipRightArg(RelationshipType relationshipType,
	std::string leftArg)
{
	if (relationshipType == RelationshipType::CALL) {
		return pkb->callsManager->getCallsRightArgLst(leftArg);
	} else if (relationshipType == RelationshipType::CALL_T) {
		return pkb->callsTManager->getCallsTRightArgLst(leftArg);
	} else if (relationshipType == RelationshipType::USES_P) {
		return pkb->usesPManager->getUsesPVarLstFromProc(leftArg);
	} else if (relationshipType == RelationshipType::MODIFIES_P) {
		return pkb->modifiesPManager->getModifiesPVarLstFromProc(leftArg);
	} else {
		throw SPAException(PKBException::PKB_INVALID_RELATIONSHIP_TYPE);
	}
}

std::unordered_map<std::string, std::vector<std::string>> PKBQueryAPI::getUsesSTable() {
	return pkb->usesSManager->getUsesSTable();
}

std::unordered_map<std::string, std::vector<std::string>> PKBQueryAPI::getUsesPTable() {
	return pkb->usesPManager->getUsesPTable();
}

std::unordered_map<std::string, std::vector<std::string>> PKBQueryAPI::getModifiesSTable() {
	return pkb->modifiesSManager->getModifiesSTable();
}

std::unordered_map<std::string, std::vector<std::string>> PKBQueryAPI::getModifiesPTable() {
	return pkb->modifiesPManager->getModifiesPTable();
}

std::string PKBQueryAPI::getAttributeName(EntityType entType, StmtIndex idx) {
	std::vector<std::string> res;
	switch (entType) {
	case EntityType::CALL:
		res = pkb->procCallManager->getProcCallFromStmtIdx(idx);
		break;
	case EntityType::READ:
		res = pkb->readManager->getVarfromStmtIdx(idx);
		break;
	case EntityType::PRINT:
		res = pkb->printManager->getVarfromStmtIdx(idx);
		break;
	default:
		break;
	}
	if (res.empty()) {
		return "";
	}
	return res[0];
}


// Get all NAMES
std::pair<std::vector<std::string>, std::vector<std::string>> PKBQueryAPI::getAttributeNames(
	EntityType entType)
{
	std::vector<std::string> res;
	switch (entType) {
	case EntityType::PROCEDURE:
		return pkb->procedureManager->getAllProcedureNames();
	case EntityType::CALL:
		return pkb->procCallManager->getAllProcCallNames();
	case EntityType::READ:
		return pkb->readManager->getAllReadsVarName();
	case EntityType::PRINT:
		return pkb->printManager->getAllPrintsVarNames();
	case EntityType::VARIABLE:
		res = pkb->variableManager->getAllVars();
		break;
	default:
		break;
	}
	return { res, res };
}
