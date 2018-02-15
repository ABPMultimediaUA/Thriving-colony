#include "ResourceJSON.h"

ResourceJSON::ResourceJSON(){

}

ResourceJSON::~ResourceJSON(){
    
} 

void ResourceJSON::load(const char *path){
    setIdentifier(path);
    try{
        std::ifstream i;
        i.open(path);
        j << i;
        i.close();
    }catch(std::ifstream::failure e){
        std::cout << "Error al abrir el fichero " << path << std::endl;
        exit(0);
    }
}

void ResourceJSON::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceJSON::getIdentifier(){
    return identifier;
}

json *ResourceJSON::getJSON(){
    return &j;
}