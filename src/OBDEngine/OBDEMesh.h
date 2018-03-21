#ifndef OBDEMESH_H
#define OBDEMESH_H

#include "OBDETypes.h"
#include "OBDESceneNode.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceMTL.h"

#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TMesh.h"

class OBDEMesh {
    public:
        /**
         * @brief 
         * 
         * @param  
         * @param 
         * @param 
         */
        OBDEMesh(OBDESceneNode*, ResourceOBJ *, ResourceMTL *);

        /**
         * @brief 
         * 
         */
        ~OBDEMesh();

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void rotate(f32 rX, f32 rY, f32 rZ, f32 angle);

        /**
         * @brief 
         * 
         */
        void scale(f32 sX, f32 sY, f32 sZ);

        /**
         * @brief 
         * 
         */
        void translate(f32 tX, f32 tY, f32 tZ);

        /**
         * @brief Set the Texture object
         * 
         */
        void setTexture(std::string, OBDEEnums::TextureTypes, ResourceIMG*);

        /**
         * @brief Get the Mesh Amount object
         * 
         * @return u32 
         */
        u32 getMeshAmount();

        /**
         * @brief Get the Mesh object
         * 
         * @return TMesh* 
         */
        TMesh *getMesh(std::string);

        /**
         * @brief Get the Meshes object
         * 
         * @return std::map<std::string, TMesh*> 
         */
        std::map<std::string, TMesh*> getMeshes();
    private:
        TNode* meshNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;
        
        std::map<std::string, TMesh*> meshes;
};

#endif