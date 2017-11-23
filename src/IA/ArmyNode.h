#ifndef ARMY_NODE_H
#define ARMY_NODE_H

#include "Node.h"

class ArmyNode : public Node {

    public:
        ArmyNode(Node*);
        ~ArmyNode();

    private:
        virtual void question();
};

#endif