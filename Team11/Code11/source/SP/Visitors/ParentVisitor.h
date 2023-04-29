#pragma once


#include <vector>
#include <string>

#include "Visitor.h"
#include "../AST/StmtNode.h"
#include "../../PKB/PKBStorageAPI.h"
#include "../../PKB/PKBQueryAPI.h"


class ParentVisitor : public Visitor {
	PKBStorageAPI pkbStorageApi;
	std::vector<int> allParentIndexes;
public:
	explicit ParentVisitor(PKBStorageAPI pkbStorageApi);
	virtual ~ParentVisitor();

	void visitWhileNode(int stmtIndex, int lastStmt, std::vector<StmtNode*> whileStmtNodes) override;
	void visitIfNode(int stmtIndex,
		int lastStmt,
		std::vector<StmtNode*> ifContainer,
		std::vector<StmtNode*> thenContainer) override;
};
