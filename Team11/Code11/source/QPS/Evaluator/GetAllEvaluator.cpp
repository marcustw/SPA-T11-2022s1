#include "GetAllEvaluator.h"

GetAllEvaluator::GetAllEvaluator(const PKBQueryAPI& pkbQueryApi) : pkbQueryApi(pkbQueryApi) {
}

std::vector<std::string> GetAllEvaluator::getAllStmt(EntityType declaration) const {
	switch (declaration) {
	case EntityType::STMT:
		return pkbQueryApi.getAllStmts();
		break;
	case EntityType::READ:
		return pkbQueryApi.getAllReads();
		break;
	case EntityType::PRINT:
		return pkbQueryApi.getAllPrints();
		break;
	case EntityType::CALL:
		return pkbQueryApi.getAllProcCalls();
		break;
	case EntityType::WHILE:
		return pkbQueryApi.getAllWhileContainers();
		break;
	case EntityType::IF:
		return pkbQueryApi.getAllIfContainers();
		break;
	case EntityType::ASSIGN:
		return pkbQueryApi.getAllAssignments();
		break;
	case EntityType::CONSTANT:
		return pkbQueryApi.getAllConsts();
		break;
	default:
		throw QPSException(QPSException::QPS_SEMANTIC_ERROR);
	}
	return std::vector<std::string>();
}


std::vector<std::string> GetAllEvaluator::getAll(EntityType declaration) const {
	switch (declaration) {
	case EntityType::VARIABLE:
		return pkbQueryApi.getAllVars();
	case EntityType::PROCEDURE:
		return pkbQueryApi.getAllProcedures();
	case EntityType::STMT:
	case EntityType::READ:
	case EntityType::PRINT:
	case EntityType::CALL:
	case EntityType::WHILE:
	case EntityType::IF:
	case EntityType::ASSIGN:
	case EntityType::CONSTANT:
		return getAllStmt(declaration);
	default:
		break;
	}
	throw SPAException("GetAllEvaluator missing EntityType");
}
