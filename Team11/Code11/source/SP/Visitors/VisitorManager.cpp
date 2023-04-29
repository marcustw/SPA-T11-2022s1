#include "VisitorManager.h"

VisitorManager::VisitorManager(ProgrammeNode* root, const PKBStorageAPI& pkbStorageApi) :
	root(root), pkbStorageApi(pkbStorageApi) {
}

void VisitorManager::initialiseVisitors() {
	EntityVisitor* entityVisitor = new EntityVisitor(pkbStorageApi);
	FollowsVisitor* followsVisitor = new FollowsVisitor(pkbStorageApi);
	ParentTVisitor* parentTVisitor = new ParentTVisitor(pkbStorageApi);
	ParentVisitor* parentVisitor = new ParentVisitor(pkbStorageApi);
	UsesVisitor* usesVisitor = new UsesVisitor(pkbStorageApi);
	ModifiesVisitor* modifiesVisitor = new ModifiesVisitor(pkbStorageApi);
	PatternVisitor* patternVisitor = new PatternVisitor(pkbStorageApi);

	root->accept(usesVisitor);
	root->accept(modifiesVisitor);
	root->accept(entityVisitor);
	root->accept(followsVisitor);
	root->accept(parentTVisitor);
	root->accept(parentVisitor);
	root->accept(patternVisitor);
}
