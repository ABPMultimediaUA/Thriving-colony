#include "SchoolNode.h"

SchoolNode::SchoolNode(Node *fatherPnt) : Node() {
    father = fatherPnt;
    children = 0;
}

SchoolNode::~SchoolNode(){
    delete father;
}

void SchoolNode::question() {
    //std::cout << "Contruyo una escuela" << std::endl;
    //ToDo: Construir escuela
}