#include "PKB.h"

PKB::PKB() {
	assignManager = new Assign();
	constantManager = new Constant();
	ifManager = new ContainerIf();
	whileManager = new ContainerWhile();
	printManager = new PrintVar();
	procedureManager = new Procedure();
	procCallManager = new ProcCall();
	statementManager = new Statement();
	readManager = new ReadVar();
	variableManager = new Variable();

	patternManager = new Pattern();

	callsManager = new CallRel();
	callsTManager = new CallsT();
	followsManager = new Follows();
	followsTManager = new FollowsT();
	parentManager = new Parent();
	parentTManager = new ParentT();
	usesSManager = new UsesS();
	usesPManager = new UsesP();
	modifiesSManager = new ModifiesS();
	modifiesPManager = new ModifiesP();
	nextManager = new Next();
}
