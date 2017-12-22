#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <GraphicEngine/Terrain.h>
#include "Ranged.h"
#include "Melee.h"
class UnitManager{
    // POR QUE ESTA CLASE ESTA DEL REVES WTF?
    private:
        SceneNode *unitLayer;

		SceneNode *currentCollision;

        std::vector<Unit*> *inHallTroops;
        //std::vector<Unit*> *inMapTroops;
        std::map<int, Unit*> *inMapTroops;

        std::vector<Unit*> *totalTroops;

        Unit *selectedTroop;

        Enumeration::Team teamManager;

        bool isDeployingTroop;
        int currentDeployingTroop;

        int gridAlignment;
    public:
        UnitManager(Enumeration::Team teamData);             //Constructor
        virtual ~UnitManager();                 //Destroyer

        void testRaycastCollisions();
		int getCollisionID();
		std::string getCollisionName();

        void updateUnitManager();               //Updates the UnitManager

        //Call for creating new troops, see the .cpp for more info on how to insert
        //the desired unit
        bool createTroop(Enumeration::UnitType unitData);

        void deployTroopAtPosition(int index, Vector3<float> vectorData);
        
        void startDeployingTroop(int index);
        void deployTroop(Terrain *terrain);

        void selectTroop(int troopID);      //Call for selecting a troop
        void unSelectTroop();
        void newOrder(Terrain *terrain);                        //Order for selected troop

        bool isSolvent(int, int, Enumeration::Team);
        bool checkCanPay(Enumeration::UnitType::SubClass);

        std::vector<Unit*> *getTotalTroops(); //Returns all troops player has
};

#endif