#ifndef TMESH_H
#define TMESH_H

#include <GL/gl.h>

#include "TEntity.h"
#include "TResourceMesh.h"

class TMesh : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TMesh(TResourceMesh *);

        /**
         * @brief 
         * 
         */
        virtual ~TMesh();

        /**
         * @brief 
         * 
         */
        virtual void beginDraw();

        /**
         * @brief 
         * 
         */
        virtual void endDraw();

    private:
        TResourceMesh* mesh;

        GLuint vertexbuffer;
        GLuint normalbuffer;
        GLuint uvbuffer;
	    GLuint elementbuffer;
};

#endif