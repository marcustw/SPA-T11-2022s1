#include <vector>
#include <iterator>

#include "ProgrammeNode.h"
#include "../Visitors/Visitor.h"

ProgrammeNode::ProgrammeNode() : TNode() {}

ProgrammeNode::~ProgrammeNode() {
    for (ProcedureNode*& procNode : procedureNodes) {
        delete procNode;
        procNode = nullptr;
    }
}

void ProgrammeNode::addProcedure(ProcedureNode* proc) {
	procedureNodes.push_back(proc);
}

void ProgrammeNode::accept(Visitor *visitor) {
    std::vector<ProcedureNode*>::iterator iter = procedureNodes.begin();
    for (iter; iter != procedureNodes.end(); ++iter) {
        (*iter)->ProcedureNode::accept(visitor);
    }
    visitor->visitProgrammeNode();
}

std::vector<ProcedureNode*> ProgrammeNode::getProcedureNodes() {
    return procedureNodes;
}

