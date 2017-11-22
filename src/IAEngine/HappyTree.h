#ifndef HAPPY_TREE_H
#define HAPPY_TREE_H

#include "BehaviourTree.h"

class HappyTree : public BehaviourTree {
    
    public: 
        HappyTree(IA*);
        ~HappyTree();

        void developCity();

        bool readyToAttack();

    private:
};

#endif