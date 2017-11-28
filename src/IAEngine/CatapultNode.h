#ifndef CATAPULT_NODE_H
#define CATAPULT_NODE_H

#include "Node.h"

class CatapultNode : public Node {

    public:
        CatapultNode(Node *);
        virtual ~CatapultNode();

    private:
        virtual void question();
};

#endif