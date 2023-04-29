#pragma once

#include "EntityVisitor.h"
#include "FollowsVisitor.h"
#include "ParentVisitor.h"
#include "ParentTVisitor.h"
#include "UsesVisitor.h"
#include "ModifiesVisitor.h"
#include "PatternVisitor.h"
#include "../../PKB/PKBStorageAPI.h"
#include "../../SP/AST/ProgrammeNode.h"

#ifndef VISITORMANAGER_H
#define VISITORMANAGER_H

class VisitorManager {
private:
	EntityVisitor* entityVisitor;
	FollowsVisitor* followsVisitor;
	ParentTVisitor* parentTVisitor;
	ParentVisitor* parentVisitor;
	UsesVisitor* usesVisitor;
	ModifiesVisitor* modifiesVisitor;
	PatternVisitor* patternVisitor;

	ProgrammeNode* root;
	PKBStorageAPI pkbStorageApi;


public:
	VisitorManager(ProgrammeNode* root, const PKBStorageAPI& pkbStorageApi);
	void initialiseVisitors();
};

#endif
