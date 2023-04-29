
#include "ModifiesP.h"

ModifiesP::ModifiesP() {}

void ModifiesP::insertModifiesP(std::string procName, std::vector<std::string> varLst) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator procExist =
		modifiesPTable.find(procName);
	std::unordered_set<std::string> varSet;
	if (procExist != modifiesPTable.end()) {
		varSet = procExist->second;
	}
	for (auto& var : varLst) {
		varSet.insert(var);
	}
	modifiesPTable[procName] = varSet;
}

std::unordered_map<std::string, std::vector<std::string>> ModifiesP::getModifiesPTable()  {
	std::unordered_map<std::string, std::vector<std::string>> res;
	for (std::pair<std::string, std::unordered_set<std::string>> keyValue : modifiesPTable) {
		std::string key = keyValue.first;
		std::unordered_set<std::string> varSet = keyValue.second;
		std::vector<std::string> varLst = std::vector<std::string>(varSet.begin(), varSet.end());
		res[key] = varLst;
	}
	return res;
}

void ModifiesP::insertProcCall(std::string procName, std::string callerProcName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator calledProcExist =
		modifiesPTable.find(procName);
	if (calledProcExist != modifiesPTable.end()) {
		std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator mainProcExist =
			modifiesPTable.find(callerProcName);
		std::unordered_set<std::string> mainProcVarSet;
		if (mainProcExist != modifiesPTable.end()) {
			mainProcVarSet = mainProcExist->second;
		}
		std::unordered_set<std::string> calledProcVarSet = calledProcExist->second;
		for (auto& var : calledProcVarSet) {
			mainProcVarSet.insert(var);
		}
		modifiesPTable[callerProcName] = mainProcVarSet;
	}
}

std::vector<std::string> ModifiesP::getModifiesPVarLstFromProc(std::string procName) {
	std::unordered_map<std::string, std::unordered_set<std::string>>::const_iterator procExist =
		modifiesPTable.find(procName);
	std::vector<std::string> res;
	if (procExist != modifiesPTable.end()) {
		std::unordered_set<std::string> varSet = procExist->second;
		res = std::vector<std::string>(varSet.begin(), varSet.end());
	}
	return res;
}
