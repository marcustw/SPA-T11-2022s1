
#include "ProcCall.h"

ProcCall::ProcCall() {}

void ProcCall::insertProcCall(StmtIndex stmtNum, std::string procName, std::string callerProcName) {
	stmtProcCallTable.insert({ stmtNum, procName });
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator procNameExist =
		procCallStmtLstTable.find(procName);
	std::unordered_set<std::string> stmtLst;
	if (procNameExist != procCallStmtLstTable.end()) {
		stmtLst = procNameExist->second;
	}
	stmtLst.insert(std::to_string(stmtNum));
	procCallStmtLstTable[procName] = stmtLst;
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator callerProcExist =
		procCallerTable.find(callerProcName);
	std::unordered_set<std::string> procSet;
	if (callerProcExist != procCallerTable.end()) {
		procSet = callerProcExist->second;
	}
	procSet.insert(procName);
	procCallerTable[callerProcName] = procSet;
}

std::vector<std::string> ProcCall::getAllProcCalls(){
	std::vector<std::string> res;
	for (auto& procCall : stmtProcCallTable) {
		res.push_back(std::to_string(procCall.first));
	}
	return res;
}

std::vector<std::string> ProcCall::getProcCallFromStmtIdx(StmtIndex stmtNum) {
	std::unordered_map<StmtIndex, std::string>::const_iterator procCallExist =
		stmtProcCallTable.find(stmtNum);
	std::vector<std::string> res;
	if (procCallExist != stmtProcCallTable.end()) {
		res = { procCallExist->second };
	}
	return res;
}

std::vector<std::string> ProcCall::getAllCallerProcs() {
	std::vector<std::string> res;
	for (auto& procCall : procCallerTable) {
		res.push_back(procCall.first);
	}
	return res;
}

std::vector<std::string> ProcCall::getProcCallLstFromCallerProc(std::string callerProcName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator callerProcExist =
		procCallerTable.find(callerProcName);
	std::vector<std::string> res;
	if (callerProcExist != procCallerTable.end()) {
		std::unordered_set<std::string> procSet = callerProcExist->second;
		res = std::vector<std::string>(procSet.begin(), procSet.end());
	}
	return res;
}

std::vector<std::string> ProcCall::getStmtLstFromProcCall(std::string procName) {
	std::vector<std::string> res;
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator procNameExist =
		procCallStmtLstTable.find(procName);
	if (procNameExist != procCallStmtLstTable.end()) {
		std::unordered_set<std::string> stmtLst = procNameExist->second;
		res = std::vector<std::string>(stmtLst.begin(), stmtLst.end());
	}
	return res;
}


std::pair<std::vector<std::string>, std::vector<std::string>> ProcCall::getAllProcCallNames() {
	std::vector<std::string> res;
	std::vector<std::string> resIdx;
	for (auto& procCall : stmtProcCallTable) {
		res.push_back(procCall.second);
		resIdx.push_back(std::to_string(procCall.first));
	}
	return { res, resIdx };
}
