#pragma once

#include "../../../PKB/PKBQueryAPI.h"

#ifndef AFFECTSBASEPROCESSOR_H
#define AFFECTSBASEPROCESSOR_H

class AffectsBaseProcessor {
protected:
	bool isNonContainerStmt(StmtIndex stmtIndex);
	bool isPureContainerStmt(StmtIndex stmtIndex);
	bool checkPrelimConstraints(StmtIndex leftIndex, StmtIndex rightIndex);
	std::vector<std::string> getNextStmts(StmtIndex stmtIndex);
	std::vector<std::string> getPrevStmts(StmtIndex stmtIndex);
	bool checkModifiedPath(StmtIndex leftIndex, StmtIndex currentIndex);
	PKBQueryAPI pkbQueryApi;

	std::vector<std::string> getVector(const std::unordered_set<StmtIndex>& set);
	virtual bool checkTraversal(StmtIndex left, StmtIndex right) = 0;

	bool isInvalid(StmtIndex left, StmtIndex right);
public:
	explicit AffectsBaseProcessor(PKBQueryAPI pkbQueryApi);
	virtual bool checkRs(const std::string& leftIdx, const std::string& rightIdx) = 0;
	virtual std::vector<std::string> getAllLeftStmt(std::string rightIndex) = 0;
	virtual std::vector<std::string> getAllRightStmt(std::string leftIndex) = 0;
	std::pair<std::vector<std::string>, std::vector<std::string>> getAllAffects();
};


#endif
