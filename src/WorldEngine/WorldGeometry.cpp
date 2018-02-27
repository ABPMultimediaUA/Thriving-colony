#include "WorldGeometry.h"
#include "Cell.h"
#include "Quadtree.h"
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>
#include <Building.h>
#define MAP 10240
#define CELL 80
WorldGeometry* WorldGeometry::pinstance = 0;
WorldGeometry* WorldGeometry::Instance(){
    if(pinstance == 0){
        pinstance = new WorldGeometry();
        pinstance->Init();
    }
    return pinstance;
}
WorldGeometry::WorldGeometry(){
/* Calculates the maximun N cells and reserve memory */
    i32 n = (MAP * MAP) / (CELL * CELL);
    mCells = std::vector<Cell*>(n);
    cellsDistance = std::vector< std::vector<f32> >(n);
    quadTree = NULL;
}
WorldGeometry::~WorldGeometry(){
    mCells.clear();
    delete quadTree;
}
void WorldGeometry::Init(){
/* Especifies the N cells each axis has */
    i32 maxCells = MAP / CELL;
    
    for (i32 y = 0; y < maxCells; y++)
    {
        for (i32 x = 0; x < maxCells; x++)
        {
        /* Calculates the index */
            i32 index = y * maxCells + x;
        /* Especifies the center where the cell is allocated */
            f32 dX = x * CELL + CELL / 2;
            f32 dY = y * CELL + CELL / 2;
            Vector2<f32> tmp = Vector2<f32>(dX, dY);
        /* Creates the hitbox */
            Vector2<f32> topLeft;
            topLeft.x = tmp.x - CELL / 2;
            topLeft.y = tmp.y - CELL / 2;
            Vector2<f32> botRight;
            botRight.x = tmp.x + CELL / 2;
            botRight.y = tmp.y + CELL / 2;
            Box2D hitBox = Box2D(topLeft, botRight);
        /* Creates the cell, and copy it to the WorldGeometry vector */
            Cell* cell = new Cell(tmp, hitBox, index);
            //mCells.push_back(cell);
            mCells[index] = cell;
        }
    }
/* Creates the hitbox for the Quadtree, and creates it */
    Vector2<f32> topLeft = Vector2<f32>(0, 0);
    Vector2<f32> botRight = Vector2<f32>(MAP, MAP);
    Box2D hitBox = Box2D(topLeft, botRight);
    Vector2<f32> center = botRight / 2;
    //std::cout << "Quadtree center: " << center.x << "," << center.y << "\n";
    quadTree = new Quadtree(center, hitBox, 1);
/* Adds each cell in the quadtree */
    for(i32 i = 0; i < mCells.size(); i++){
        quadTree->insertCell(mCells[i]);
    }
/* Calculate neighbors for each cell (this method cost a lot of time) */
    //for(i32 i = 0; i < mCells.size(); i++){
    //    quadTree->assignNeighbors(mCells[i]);
    //}
/* Calculate neighbors for each cell (faster version) */
    for(i32 y = 0; y < maxCells; y++){
        for(i32 x = 0; x < maxCells; x++){
            Cell* tmp = mCells.at(maxCells * y + x);
            if(y == 0){
                if(x == 0){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(maxCells));
                    tmp->setNeighbor(mCells.at(maxCells + 1));
                }
                else if(x == maxCells - 1){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex()));
                }
                else{
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex()));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex() + 1));
                }
            }
            else if(y == maxCells - 1){
                if(x == 0){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells + 1));
                }
                else if(x == maxCells - 1){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells - 1));
                }
                else{
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells + 1));
                }
            }
            else{
                if(x == 0){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCells));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCells + 1));
                }
                else if(x == maxCells - 1){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCells - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCells));
                }
                else{
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCells + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCells - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCells));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCells + 1));
                }
            }
        }
    }
/* Pre-calculate the distance between each cell and his neighbors */
    for(i32 j = 0; j < mCells.size(); j++){
        std::vector<Cell*> neighbors = mCells[j]->getNeighbors();
        i32 size = neighbors.size();
        cellsDistance[j] = std::vector<f32>(size);
        for(i32 k = 0; k < size; k++){
            cellsDistance[j][k] = calculateDistance(mCells[j]->getPosition(), neighbors[k]->getPosition());
        }
    }
}
void WorldGeometry::Clear(){
    
}
void WorldGeometry::build(Building* buildingPtr){
    quadTree->insertBuilding(buildingPtr);
}
Vector2<f32> WorldGeometry::correctBuildingPosition(Vector2<f32> targetPos, Building *buildingPtr, bool &collision){
    Vector2<f32> correctOne = Vector2<f32>();
    if(buildingPtr != NULL){
        Cell* dummy = positionToCell(targetPos);
        Vector2<f32> storage;
        if(buildingPtr -> getCells() % 2 == 0){
            storage = dummy->getHitbox().TopLeft();
            correctOne.x = storage.x;
            correctOne.y = storage.y;
            storage.x -= CELL / 2;
            storage.y -= CELL / 2;
            storage.x -= (buildingPtr -> getCells() / 2) * (CELL / 2);
            storage.y -= (buildingPtr -> getCells() / 2) * (CELL / 2);
        }
        else{
            storage = dummy->getHitbox().Center();
            correctOne.x = storage.x;
            correctOne.y = storage.y;
            storage.x -= (buildingPtr -> getCells() - 1) * (CELL / 2);
            storage.y -= (buildingPtr -> getCells() - 1) * (CELL / 2);
        }
        if(quadTree->canBuild(buildingPtr->getHit())){
            collision = true;
        }
    }
    return correctOne;
}
Cell* WorldGeometry::positionToCell(Vector2<f32> position){
    int dummy = (i32)((MAP / CELL) * position.x / MAP) + 
                ((i32)((MAP / CELL) * position.y / MAP) * (MAP / CELL));
    if(dummy < 0 || dummy > mCells.size()){
        return NULL;
    }
    i32 idx = dummy;

    if (idx == mCells.size()) 
        idx = mCells.size() - 1;

    return mCells.at(idx);
}
Cell* WorldGeometry::indexToCell(i32 index){
    return mCells[index];
}
f32 WorldGeometry::calculateDistance(Vector2<f32> a, Vector2<f32> b){
    f32 dX = b.x - a.x;
    f32 dY = b.y - a.y;
    f32 distance = std::sqrt(std::pow(dX, 2) + std::pow(dY,2));
    return distance;
}
f32 WorldGeometry::getCost(i32 indexA, i32 indexB){
    return cellsDistance[indexA][indexB];
}
const std::vector<Cell*>& WorldGeometry::getNeighbors(i32 index){
    return mCells[index]->getNeighbors();
}
const std::vector<Cell*>& WorldGeometry::getCells(){
    return mCells;
}
const std::vector< std::vector<f32> >& WorldGeometry::getCellsDistance(){
    return cellsDistance;
}