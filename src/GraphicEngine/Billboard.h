#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <Types.h>
#include <MathEngine/Vector3.h>
#include <MathEngine/Color.h>
#include "SceneNode.h"
#include "Window.h"

class Billboard {
    public:
        Billboard(SceneNode* parent, i32 id, Vector3<f32> pos);
        ~Billboard();

        void setColor(Color* top, Color* bot);
        void setSize(f32 h, f32 tw, f32 bw);
        void setPosition(Vector3<f32> pos);

        Vector3<f32> getPosition();
        Color getTopColor();
        Color getBottomColor();
        f32 getHeight();
        f32 getTopWidth();
        f32 getBottomWidth();
        i32 getID();

    private:
        OBDBillboard* billboard;
};

#endif