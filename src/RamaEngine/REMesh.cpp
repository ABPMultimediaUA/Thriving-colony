#include "REMesh.h"

REMesh::REMesh(RESceneNode* parent, ResourceOBJ *obj, ResourceMTL *mtl) {
    rotationNode = new TNode(new TTransform(), parent->getSceneNode());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    std::map<std::string, ResourceMesh *> submeshes = *obj->getResource();
    std::map<std::string, ResourceMaterial *> submats = *mtl->getResource();

    for (std::map<std::string, ResourceMesh *>::iterator it=submeshes.begin(); it!=submeshes.end(); ++it) {
        std::map<std::string, ResourceMaterial *>::iterator it2;
        it2 = submats.find(it->second->getDefaultMaterialName());
        if (it2 == submats.end()){
            std::cout << "No existe material " << it->second->getDefaultMaterialName() << " para el mesh " << it->first << std::endl;
            exit(0);
        }

        TMesh *tempMesh = new TMesh(it->second, it2->second);

        meshes.insert(std::pair<std::string, TMesh*>(it->second->getName(), tempMesh));
    }

    //ToDo: un nodo para cada submesh
    meshNode = new TNode(meshes.begin()->second, scaleNode);
}

REMesh::~REMesh() {

}

//ToDo: poder cambiar material de cada mesh (o de todos cambiando el MTL)

void REMesh::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void REMesh::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void REMesh::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

void REMesh::setTexture(std::string name, REEnums::TextureTypes tt, ResourceIMG *t){
    meshes[name] -> setTexture(tt, new TTexture(t));
}

u32 REMesh::getMeshAmount(){
    return meshes.size();
}

TMesh *REMesh::getShape(std::string meshName){
    return meshes[meshName];
}

std::map<std::string, TMesh*> REMesh::getMeshes(){
    return meshes;
}