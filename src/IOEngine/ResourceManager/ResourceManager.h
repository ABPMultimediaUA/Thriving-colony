#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <queue>
#include <vector>
#include <thread>
#include "ResourceOBJ.h"
#include <Types.h>

class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();

        void Update();

        void loadResource(std::string, bool);

        Resource *getResource(std::string);
    private:
        void load(std::string);
        void push(std::string);

        std::map<std::string, Resource *> resources;
        std::queue<std::thread> threads;
};

#endif