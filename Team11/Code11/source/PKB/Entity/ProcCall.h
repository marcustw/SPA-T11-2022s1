#pragma once

#ifndef PROCCALL_H
#define PROCCALL_H

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "../../Common/Types.h"
#include "../../Common/SPAException.h"

class ProcCall {
private:
	// key: stmtNum proc is called, value: procName
	std::unordered_map<StmtIndex, std::string> stmtProcCallTable;

	// key: procName, value: statement where procName is called
	std::unordered_map<std::string, std::unordered_set<std::string>> procCallStmtLstTable;

	// key: procCalled, value: list of callerProcs that call
	std::unordered_map<std::string, std::unordered_set<std::string>> procCallerTable;

public:
	ProcCall();
	void insertProcCall(StmtIndex stmtNum, std::string procName, std::string callerProcName);
	std::vector<std::string> getAllProcCalls();  // return stmtNum of all procCalls
	std::vector<std::string> getAllCallerProcs();  // return list of all callerProcs
	std::vector<std::string> getProcCallFromStmtIdx(StmtIndex stmtNum);
	std::vector<std::string> getProcCallLstFromCallerProc(std::string callerProcName);
	std::vector<std::string> getStmtLstFromProcCall(std::string procName);
	std::pair<std::vector<std::string>, std::vector<std::string>> getAllProcCallNames();
};

#endif
