#ifndef CLOSE_BUILDING_NODE_H
#define CLOSE_BUILDING_NODE_H

#include "Node.h"

class CloseBuildingNode : public Node {

    public:
        CloseBuildingNode(Node *);
        virtual ~CloseBuildingNode();

    private:
        virtual void question();
};

#endif