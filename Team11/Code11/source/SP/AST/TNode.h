#pragma once

#include <string>

#ifndef TNODE_H
#define TNODE_H

class Visitor;

class TNode
{
public:
    TNode();

    virtual void accept(Visitor* visitor) = 0;
};

#endif
