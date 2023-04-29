
#include "UsesP.h"

UsesP::UsesP() {}

void UsesP::insertUsesP(std::string procName, std::vector<std::string> varLst) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator procExist =
		usesPtable.find(procName);
	std::unordered_set<std::string> varSet;
	if (procExist != usesPtable.end()) {
		varSet = procExist->second;
	}
	for (auto& var : varLst) {
		varSet.insert(var);
	}
	usesPtable[procName] = varSet;
}

std::unordered_map<std::string, std::vector<std::string>> UsesP::getUsesPTable() {
	std::unordered_map<std::string, std::vector<std::string>> res;
	for (std::pair<std::string, std::unordered_set<std::string>> keyValue : usesPtable) {
		std::string key = keyValue.first;
		std::unordered_set<std::string> varSet = keyValue.second;
		std::vector<std::string> varLst = std::vector<std::string>(varSet.begin(), varSet.end());
		res[key] = varLst;
	}
	return res;
}

void UsesP::insertProcCall(std::string procName, std::string callerProcName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator calledProcExist =
		usesPtable.find(procName);
	if (calledProcExist != usesPtable.end()) {
		std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator mainProcExist =
			usesPtable.find(callerProcName);
		std::unordered_set<std::string> mainProcVarSet;
		if (mainProcExist != usesPtable.end()) {
			mainProcVarSet = mainProcExist->second;
		}
		std::unordered_set<std::string> calledProcVarSet = calledProcExist->second;
		for (auto& var : calledProcVarSet) {
			mainProcVarSet.insert(var);
		}
		usesPtable[callerProcName] = mainProcVarSet;
	}
}

std::vector<std::string> UsesP::getUsesPVarLstFromProc(std::string procName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator procExist =
		usesPtable.find(procName);
	std::vector<std::string> res;
	if (procExist != usesPtable.end()) {
		std::unordered_set<std::string> varSet = procExist->second;
		res = std::vector<std::string>(varSet.begin(), varSet.end());
	}
	return res;
}
