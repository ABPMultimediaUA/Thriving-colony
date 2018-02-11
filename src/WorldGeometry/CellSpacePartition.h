#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H
#include <vector>
#include <list>
#include <Entity.h>
#include <Types.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>

class CellSpacePartition;
struct Cell{
// All the entities inhabiting this cell
    std::list< Entity* > entities;
// Cell bounding box
    Box2D BBox;
// Bool block
    bool blocked = false;
// Constructor
    Cell(Vector2<f32> topLeft,
         Vector2<f32> botRight):BBox(topLeft, botRight)
    {}
// Destructor
    ~Cell();
};
class CellSpacePartition{
    private:
    // CellSpace instance
        static CellSpacePartition* pinstance;
    // Width and height
        //f32 spaceWidth;
        //f32 spaceHeight;
    // Number of cells the space is going to be divided into
        //i32 cellsX;
        //i32 cellsY;
    
        f32 cellSizeX;
        f32 cellSizeY;
    // Required number of cells
        std::vector< Cell > mCells;
    // Stores valid neighbors 
        std::vector< Entity* > mNeighbors;
    // Iterator used by methods next and begin
        std::vector< Entity* >::iterator mCurNeighbor;
    // Returns an index from a position 
        i32 positionToIndex(Vector2<f32> position);
    public:
    // Constructor
        static CellSpacePartition* Instance();
        CellSpacePartition();
    // Destructor
        ~CellSpacePartition();
    // Add entities to the proper cell
        void addEntity(Entity* ent);
    // Updates a entity's cell, calling this from the entity update method
        void updateEntity(Entity* ent, Vector2<f32> oldPos);
    // Calculate neighbors and add them in the neighbor vector
        void calculateNeighbors(Vector2<f32> targetPos, f32 radious);
    // Returns the correct position where the building is built
        Vector3<f32> correctPosition(Vector3<f32> targetPos, Entity *object, bool &collision);
    // Returns if the given hitbox collides with a blocked cell
        void updateCell(Entity *object);
        //bool checkBuildingCollision();
    // Checks if the cell is blocked
        bool isBlocked(Vector3<f32> targetPos);
    // Returns a reference to the entity of the neighbor vector
        Entity* begin();
    // Used to iterate trought the neighbor vector
        Entity* next();
    // Returns true if the iterator reach the end of the vector
        bool end();
    // Clears the cells
        void clearCells();
};
#endif /* CELLSPACEPARTITION_H */