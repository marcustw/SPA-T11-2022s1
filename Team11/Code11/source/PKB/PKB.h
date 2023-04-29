#pragma once

#include "../PKB/Entity/Assign.h"
#include "../PKB/Entity/Constant.h"
#include "../PKB/Entity/ContainerIf.h"
#include "../PKB/Entity/ContainerWhile.h"
#include "../PKB/Entity/PrintVar.h"
#include "../PKB/Entity/Procedure.h"
#include "../PKB/Entity/ProcCall.h"
#include "../PKB/Entity/Statement.h"
#include "../PKB/Entity/ReadVar.h"
#include "../PKB/Entity/Variable.h"

#include "../PKB/Pattern/Pattern.h"

#include "../PKB/Relationship/CallRel.h"
#include "../PKB/Relationship/CallsT.h"
#include "../PKB/Relationship/Follows.h"
#include "../PKB/Relationship/FollowsT.h"
#include "../PKB/Relationship/Parent.h"
#include "../PKB/Relationship/ParentT.h"
#include "../PKB/Relationship/UsesS.h"
#include "../PKB/Relationship/UsesP.h"
#include "../PKB/Relationship/ModifiesS.h"
#include "../PKB/Relationship/ModifiesP.h"
#include "../PKB/Relationship/Next.h"


class PKB {
private:
	Assign* assignManager;
	Constant* constantManager;
	ContainerIf* ifManager;
	ContainerWhile* whileManager;
	PrintVar* printManager;
	Procedure* procedureManager;
	ProcCall* procCallManager;
	Statement* statementManager;
	ReadVar* readManager;
	Variable* variableManager;

	Pattern* patternManager;

	CallRel* callsManager;
	CallsT* callsTManager;
	Follows* followsManager;
	FollowsT* followsTManager;
	Parent* parentManager;
	ParentT* parentTManager;
	UsesS* usesSManager;
	UsesP* usesPManager;
	ModifiesS* modifiesSManager;
	ModifiesP* modifiesPManager;
	Next* nextManager;

public:
	PKB();

	friend class PKBStorageAPI;
	friend class PKBQueryAPI;
};
