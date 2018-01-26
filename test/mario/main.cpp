#include <GLFW/glfw3.h>

#include <irrlicht.h>
#include <nanogui/nanogui.h>

#include <GraphicEngine/Window.h>
#include <GraphicEngine/Terrain.h>
#include <CameraController.h>

#include <iostream>

int main(int argc, char **argv) {
    Window *w = Window::Instance();

    InputManager *io = new InputManager();
    Mouse *cursor = new Mouse();

    Terrain *map = new Terrain("media/heightmap.bmp"); //ToDo: mover a map
    map -> setTexture(new Texture("media/map-texture.jpg"), new Texture("media/map-detail-texture.jpg")); //ToDo: mover a map

    CameraController *camera = new CameraController(map);

    scene::IMeshSceneNode *cube;
    cube = w -> getSceneManager() -> addCubeSceneNode(100);
    cube -> setMaterialFlag(video::EMF_LIGHTING, false);
    int y = map -> getY(7000,7000);
    cube -> setPosition(core::vector3df(7000, y+500, 7000));

    // Create nanogui gui
    //w -> getGUIEnvironment() -> add<nanogui::Button>("Hola");

    cube = w -> getSceneManager() -> addCubeSceneNode(100);
    cube -> setMaterialFlag(video::EMF_LIGHTING, false);
    y = map -> getY(7200,7200);
    cube -> setPosition(core::vector3df(7200, y+500, 7200));
   
    w -> setGUI();

    cube = w -> getSceneManager() -> addCubeSceneNode(100);
    cube -> setMaterialFlag(video::EMF_LIGHTING, false);
    y = map -> getY(7400,7400);
    cube -> setPosition(core::vector3df(7400, y+500, 7400));

    while (w -> isOpen()){
        w -> beginScene();

        camera -> Move(io, cursor);
        camera -> RotateAndInclinate(io, cursor);
        camera -> Zoom(io);

        camera -> Update(w -> getDeltaTime());

        w -> endScene();
    }

    w -> close();
}