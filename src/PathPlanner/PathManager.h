#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include <vector>
#include <queue>
#include <Types.h>
#include <MathEngine/Vector2.h>

class Unit;
class WorldGeometry;
class PathManager{
    private:
        Unit* propietary;
        Vector2<f32> vDestination;
    public:
        /**
         * @brief Default constructor
         * 
         * @param unitPtr The units that owns this pathManager
         */
        PathManager(Unit* unitPtr);
        /**
         * @brief Default destructor
         * 
         */
        ~PathManager();
        /**
         * @brief Creates a path to the given position, and assing it to the owner of this pathManager
         * 
         * @param targetPos The point where the units is pretending to go
         * @return true True if a path if possible
         * @return false Else
         */
        bool createPathTo(Vector2<f32> targetPos);
};
#endif /* PATHMANAGER_H */