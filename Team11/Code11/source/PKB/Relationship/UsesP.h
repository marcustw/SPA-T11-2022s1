#pragma once

#ifndef USESP_H
#define USESP_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class UsesP {
private:
	// key: procName, value: variable used in proc on the right side of '=' or used in condition
	std::unordered_map<std::string, std::unordered_set<std::string>> usesPtable;

public:
	UsesP();
	void insertUsesP(std::string procName, std::vector<std::string> varLst);

	// update callerProcName value to include procName's value
	void insertProcCall(std::string procName, std::string callerProcName);

	// return usesP Var List given procedure name
	std::vector<std::string> getUsesPVarLstFromProc(std::string procName);

	std::unordered_map<std::string, std::vector<std::string>> getUsesPTable();
};

#endif
