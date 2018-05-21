#ifndef TSKYBOX_H
#define TSKYBOX_H

#include "TEntity.h"
#include "TTexture.h"

class TSkybox : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TSkybox(TTexture* texture);

        /**
         * @brief 
         * 
         */
        virtual ~TSkybox();

        /**
         * @brief 
         * 
         */
        void beginDraw();

        /**
         * @brief 
         * 
         */
        void endDraw();

        /**
         * @brief Set the Texture object
         * 
         */
        void setTexture(TTexture*);

    private:        
        GLuint textureID;
};

#endif