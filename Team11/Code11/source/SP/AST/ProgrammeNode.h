#pragma once

#ifndef PROGRAMMENODE_H
#define PROGRAMMENODE_H

#include <vector>

#include "TNode.h"
#include "ProcedureNode.h"

class Visitor;

class ProgrammeNode : public TNode {
public:
	ProgrammeNode();
	~ProgrammeNode();

	void addProcedure(ProcedureNode* proc);
	std::vector<ProcedureNode*> getProcedureNodes();
	void accept(Visitor* visitor);

private:
	std::vector<ProcedureNode*> procedureNodes;
};

#endif
