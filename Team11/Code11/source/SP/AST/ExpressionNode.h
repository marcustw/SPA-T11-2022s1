#pragma once

#include <string>
#include <vector>
#include "../../Common/Types.h"
#include "TNode.h"

class Visitor;

class ExpressionNode : public TNode {
public:
	ExpressionNode();
	ExpressionNode(int stmtIndex, std::string val, ExpressionType type);
	ExpressionNode(int stmtIndex, std::string val, ExpressionType type, ExpressionPos exprPos);

	void addLeftChild(ExpressionNode* expr);
	void addRightChild(ExpressionNode* expr);

	int getStmtIndex();
	std::string getValue();
	ExpressionNode* getLeftChild();
	ExpressionNode* getRightChild();
	ExpressionType getExpressionType();
	ExpressionPos getExpressionPos();

	void accept(Visitor* visitor);

	std::string toExprString();

private:
	std::string value;
	ExpressionType exprType;
	ExpressionPos exprPos;
	int stmtIndex;
	ExpressionNode* leftChild = nullptr;
	ExpressionNode* rightChild = nullptr;
};
