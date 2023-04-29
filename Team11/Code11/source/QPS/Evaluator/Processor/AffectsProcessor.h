#pragma once

#include "../../../PKB/PKBQueryAPI.h"
#include "AffectsBaseProcessor.h"
#include "../../Common/QPSCache.h"

#ifndef AFFECTSPROCESSOR_H
#define AFFECTSPROCESSOR_H

class AffectsProcessor : public AffectsBaseProcessor {
	static const char NONE_STMT[];
protected:
	QPSCache* cache;
	std::vector<std::string> getNext(StmtIndex idx);
	std::vector<std::string> getPrev(StmtIndex idx);
	bool checkTraversal(StmtIndex left, StmtIndex right) override;
public:
	explicit AffectsProcessor(PKBQueryAPI pkbQueryApi);
	~AffectsProcessor();
	AffectsProcessor(QPSCache* cache, PKBQueryAPI pkbQueryApi);

	bool checkRs(const std::string& leftIdx, const std::string& rightIdx) override;
	std::vector<std::string> getAllLeftStmt(std::string rightIndex) override;
	std::vector<std::string> getAllRightStmt(std::string leftIndex) override;

	bool contains(StmtIndex left, StmtIndex right);

	QPSCache* getCache();
};

#endif
