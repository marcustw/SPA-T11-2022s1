#include "ExpressionNode.h"

#include <vector>
#include <iterator>
#include "../Visitors/Visitor.h"

ExpressionNode::ExpressionNode() : TNode() {}

ExpressionNode::ExpressionNode(int stmtIx, std::string val, ExpressionType type) {
	exprType = type;
	stmtIndex = stmtIx;
	value = val;
}

ExpressionNode::ExpressionNode(int stmtIx, std::string val, ExpressionType type, ExpressionPos pos) {
	exprType = type;
	exprPos = pos;
	stmtIndex = stmtIx;
	value = val;
}

void ExpressionNode::addLeftChild(ExpressionNode* expr) {
	leftChild = expr;
}

void ExpressionNode::addRightChild(ExpressionNode* expr) {
	rightChild = expr;
}

void ExpressionNode::accept(Visitor* visitor) {
	if (this->leftChild != nullptr) {
		leftChild->accept(visitor);
	}

	if (this->rightChild != nullptr) {
		rightChild->accept(visitor);
	}

	visitor->visitExpressionNode(this);
}

std::string ExpressionNode::toExprString() {
	if (exprType == ExpressionType::TERM_OPR && leftChild && rightChild) {
		return leftChild->toExprString() + " " + value + " " + rightChild->toExprString();
	}
	if (exprType == ExpressionType::EXP_OPR && leftChild && rightChild) {
		return leftChild->toExprString() + " " + value + " " + rightChild->toExprString();
	}
	if (leftChild == nullptr && rightChild == nullptr) {
		return value;
	}
	if (leftChild == nullptr) {
		return value + " " + rightChild->toExprString();
	}
	if (rightChild == nullptr) {
		return leftChild->toExprString() + " " + value;
	}
	return leftChild->toExprString() + " " + value + " " + rightChild->toExprString();
}
int ExpressionNode::getStmtIndex()
{
	return stmtIndex;
}

std::string ExpressionNode::getValue()
{
	return value;
}

ExpressionNode* ExpressionNode::getLeftChild()
{
	return leftChild;
}

ExpressionNode* ExpressionNode::getRightChild()
{
	return rightChild;
}

ExpressionType ExpressionNode::getExpressionType()
{
	return exprType;
}

ExpressionPos ExpressionNode::getExpressionPos()
{
	return exprPos;
}


