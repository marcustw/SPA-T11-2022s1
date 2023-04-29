
#include "CallsT.h"

CallsT::CallsT() {}

void CallsT::insertCallsT(std::string procName, std::unordered_set<std::string> procLst) {
	std::unordered_set<std::string> callTSet;
	callTSet = callTTable.contains(TableDirection::LEFTKEY, procName);
	for (auto& proc : procLst) {
		callTSet.insert(proc);
		std::unordered_set<std::string> procMainSet;
		procMainSet = callTTable.contains(TableDirection::RIGHTKEY, proc);
		procMainSet.insert(procName);
		callTTable.insert(TableDirection::RIGHTKEY, proc, procMainSet);
	}
	callTTable.insert(TableDirection::LEFTKEY, procName, callTSet);
}

std::vector<std::string> CallsT::getCallsTLeftArgLst(std::string rightArg) {
	std::vector<std::string> res;
	std::unordered_set<std::string> leftArgSet = callTTable.contains(TableDirection::RIGHTKEY, rightArg);
	res = std::vector<std::string>(leftArgSet.begin(), leftArgSet.end());
	return res;
}

std::vector<std::string> CallsT::getCallsTRightArgLst(std::string leftArg) {
	std::vector<std::string> res;
	std::unordered_set<std::string> rightArgSet = callTTable.contains(TableDirection::LEFTKEY, leftArg);
	res = std::vector<std::string>(rightArgSet.begin(), rightArgSet.end());
	return res;
}
