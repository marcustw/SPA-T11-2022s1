#pragma once
#ifndef GETALLEVALUATOR_H
#define GETALLEVALUATOR_H

#include "../../Common/SPAException.h"
#include "../../PKB/PKBQueryAPI.h"
#include "../Common/PQLCommon.h"
#include "../../Common/Types.h"
#include "QueryResult.h"

class GetAllEvaluator {
	PKBQueryAPI pkbQueryApi;
public:
	explicit GetAllEvaluator(const PKBQueryAPI& pkbQueryApi);

	std::vector<std::string> getAll(EntityType declaration) const;
	std::vector<std::string> getAllStmt(EntityType declaration) const;
};

#endif
