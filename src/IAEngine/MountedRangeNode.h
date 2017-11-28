#ifndef MOUNTED_RANGE_NODE_H
#define MOUNTED_RANGE_NODE_H

#include "Node.h"

class MountedRangeNode : public Node {

    public:
        MountedRangeNode(Node *);
        virtual ~MountedRangeNode();

    private:
        virtual void question();
};

#endif