#pragma once

#include <string>
#include <list>
#include <unordered_set>

#include "../../PKB/PKBQueryAPI.h"
#include "../Evaluator/QueryResult.h"
#include "../Parser/PQLQueryObject.h"

class ResultProjector {
	std::string getProcedureName(PQLReference attr, const std::string& syn);
	std::string getVariableName(PQLReference attr, const std::string& syn);
	std::string project(PQLReference attr, const std::string& syn);

	PKBQueryAPI* pkbQueryApi;
	DeclareMap declareMap;
public:
	ResultProjector(PKBQueryAPI* pkbQueryApi, const DeclareMap& declareMap);
	std::list<std::string> projectResult(QueryResult* queryResult,
		std::vector<PQLReference> pqlRefs, bool isSelectBoolean);
};
