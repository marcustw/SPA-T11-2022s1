
#include "Constant.h"

Constant::Constant() {}

void Constant::insertConst(StmtIndex stmtNum, std::vector<ConstValue> constLst) {
	std::unordered_map<StmtIndex, std::unordered_set<std::string>>::const_iterator stmtExist =
		stmtConstLstTable.find(stmtNum);
	std::unordered_set<std::string> constSet;
	if (stmtExist != stmtConstLstTable.end()) {
		constSet = stmtExist->second;
	}
	for (auto& constant : constLst) {
		constSet.insert(std::to_string(constant));
		std::unordered_map<ConstValue, std::unordered_set<StmtIndex>>::const_iterator constExist =
			constStmtTable.find(constant);
		std::unordered_set<StmtIndex> stmtSet;
		if (constExist != constStmtTable.end()) {
			stmtSet = constExist->second;
		}
		stmtSet.insert(stmtNum);
		constStmtTable[constant] = stmtSet;
	}
	stmtConstLstTable[stmtNum] = constSet;
}

std::vector<std::string> Constant::getAllConsts() {
	std::vector<std::string> res;

	for (auto& row : constStmtTable) {
		res.push_back(std::to_string(row.first));
	}

	return res;
}
