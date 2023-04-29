#pragma once

#ifndef PARENTTVISITOR_H
#define PARENTTVISITOR_H

#include <vector>
#include <string>

#include "Visitor.h"
#include "../AST/StmtNode.h"
#include "../../PKB/PKBStorageAPI.h"

class ParentTVisitor : public Visitor {
	PKBStorageAPI pkbStorageApi;
public:
	explicit ParentTVisitor(PKBStorageAPI pkbStorageApi);
	virtual ~ParentTVisitor();

	void visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes) override;
	void visitIfNode(int stmtIndex,
		int lastStmt,
		std::vector<StmtNode*> ifContainer,
		std::vector<StmtNode*> thenContainer) override;
};

#endif
