#ifndef CLOSE_DOORS_NODE_H
#define CLOSE_DOORS_NODE_H

#include "Node.h"

class CloseDoorsNode : public Node {

    public:
        CloseDoorsNode(Node*);
        virtual ~CloseDoorsNode();

    private:
        virtual void question();
};

#endif