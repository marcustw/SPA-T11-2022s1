
#include "CallRel.h"

CallRel::CallRel() {}

void CallRel::insertCalls(std::string procName, std::unordered_set<std::string> procLst) {
	std::unordered_set<std::string> callSet;
	callSet = callTable.contains(TableDirection::LEFTKEY, procName);
	for (auto& proc : procLst) {
		callSet.insert(proc);
		std::unordered_set<std::string> procMainSet;
		procMainSet = callTable.contains(TableDirection::RIGHTKEY, proc);
		procMainSet.insert(procName);
		callTable.insert(TableDirection::RIGHTKEY, proc, procMainSet);
	}
	callTable.insert(TableDirection::LEFTKEY, procName, callSet);
}

std::vector<std::string> CallRel::getCallsLeftArgLst(std::string rightArg) {
	std::vector<std::string> res;
	std::unordered_set<std::string> leftArgSet = callTable.contains(TableDirection::RIGHTKEY, rightArg);
	res = std::vector<std::string>(leftArgSet.begin(), leftArgSet.end());
	return res;
}

std::vector<std::string> CallRel::getCallsRightArgLst(std::string leftArg) {
	std::vector<std::string> res;
	std::unordered_set<std::string> rightArgSet = callTable.contains(TableDirection::LEFTKEY, leftArg);
	res = std::vector<std::string>(rightArgSet.begin(), rightArgSet.end());
	return res;
}
