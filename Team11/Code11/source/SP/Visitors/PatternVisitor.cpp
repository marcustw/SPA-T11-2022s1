#include <string>
#include <vector>

#include "PatternVisitor.h"
#include "../Extractors/ExtractorUtils.h"

PatternVisitor::PatternVisitor(PKBStorageAPI pkbStorageApi) : pkbStorageApi(pkbStorageApi) {}
PatternVisitor::~PatternVisitor() {}

void PatternVisitor::visitExpressionNode(ExpressionNode* self)
{
	ExpressionType exprType = self->getExpressionType();
	ExpressionPos exprPos = self->getExpressionPos();
	StmtIndex stmtIndex = self->getStmtIndex();
	std::string value = self->getValue();

	if (exprType == ExpressionType::CONSTANT || exprType == ExpressionType::VARIABLE && exprPos != ExpressionPos::LHS) {
		pkbStorageApi.PKBStorageAPI::insertStmtExpressionLst(stmtIndex, value);
	}

	if (exprType == ExpressionType::EXP_OPR
		|| exprType == ExpressionType::TERM_OPR
		|| (exprType == ExpressionType::COND_EXPR)
		|| exprType == ExpressionType::REL_EXPR) {
		std::string expr = flatten(self);
		pkbStorageApi.PKBStorageAPI::insertStmtExpressionLst(stmtIndex, expr);
	}
}

void PatternVisitor::visitAssignNode(int stmtIndex, std::string varName, ExpressionNode* exprNode) {
	std::string expr = flatten(exprNode);
	pkbStorageApi.PKBStorageAPI::insertStmtExactExpression(stmtIndex, expr);
}
