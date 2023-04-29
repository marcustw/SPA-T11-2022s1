#pragma once

#ifndef FOLLOWSVISITOR_H
#define FOLLOWSVISITOR_H

#include "./Visitor.h"
#include "../AST/StmtNode.h"
#include "../../PKB/PKBStorageAPI.h"


class FollowsVisitor : public Visitor {
	PKBStorageAPI pkbStorageApi;
public:
	explicit FollowsVisitor(PKBStorageAPI pkbStorageApi);
	virtual ~FollowsVisitor();

	void visitStmtLstNode(std::vector<StmtNode*>) override;
};

#endif
