#include "ResourceNode.h"
#include "SiderurgyNode.h"
#include "QuarryNode.h"

ResourceNode::ResourceNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = new Node*[2];
    children[0] = new QuarryNode(this);
    children[1] = new SiderurgyNode(this);
    
}

ResourceNode::~ResourceNode(){
    delete father;
    delete[] children;
}

void ResourceNode::question() {
    //std::cout << Voy a invertir en recursos << std::endl;
    //First subbranch: Quarry
    if (tree -> getShortOnCrystal() && IA::getInstance() -> getCityLevel() >= tree -> getQuarryMilestone()) {
        children[0] -> question();
    } else {
        //Second subbranch: Siderurgy
        if (tree -> getShortOnMetal()) {            
            children[1] -> question();
        }
        
    }
}