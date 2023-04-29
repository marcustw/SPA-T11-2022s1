#pragma once

#ifndef MODIFIESP_H
#define MODIFIESP_H

#include <unordered_map>
#include <unordered_set>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class ModifiesP {
private:
	// key: procName, value: variables used in stmt (in Proc) on the left side of '='
	std::unordered_map<std::string, std::unordered_set<std::string>> modifiesPTable;

public:
	ModifiesP();
	void insertModifiesP(std::string procName, std::vector<std::string> varLst);

	// update callerProcName value to include procName's value
	void insertProcCall(std::string procName, std::string callerProcName);

	std::vector<std::string> getModifiesPVarLstFromProc(std::string procName);
	std::unordered_map<std::string, std::vector<std::string>> getModifiesPTable();
};

#endif
