#ifndef VERYHAPPY_TREE_H
#define VERYHAPPY_TREE_H

#include "BehaviourTree.h"

class VeryHappyTree : public BehaviourTree {
    
    public:
        VeryHappyTree(IA*);
        ~VeryHappyTree();

        virtual void developCity();

        virtual bool readyToAttack();
    
    private:
};

#endif