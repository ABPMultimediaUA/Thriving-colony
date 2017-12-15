#include "Building.h"
#include "IA.h"
#include "Human.h"

Building::Building(Enumeration::BuildingType buildingData, Vector3<float> *vectorData, Enumeration::Team teamData, Model *modelData, Box3D<float> *boxData) : Entity()
{
    int happiness = 0;
    int cityLevel = 0;
    switch (buildingData) {
        case Enumeration::BuildingType::Barn:
            this->hpMax = 1100;
            this->hp = 1100;
            happiness = 0;
            cityLevel = 15;
            if (teamData == Enumeration::Team::Human) {
                Human::getInstance() -> setBarnBuilt(true);
                Human::getInstance() -> increaseHappiness(happiness);
			} else {
				IA::getInstance() -> setBarnBuilt(true);
            }
        break;
        case Enumeration::BuildingType::Barrack:
            this->hpMax = 720;
            this->hp = 720;
            happiness = 0;
            cityLevel = 10;
            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> setBarrackBuilt(true);
			} else {
				IA::getInstance() -> setBarrackBuilt(true);
			}
        break;
        case Enumeration::BuildingType::Hospital:
            this->hpMax = 750;
            this->hp = 750;
            happiness = 15;
            cityLevel = 5;
            break;
        case Enumeration::BuildingType::House:
            this->hpMax = 150;
            this->hp = 150;
            happiness = 1;
            cityLevel = 5;
            //ToDo: Debug cambiar cuando se haga el jugador
            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> increaseCitizens();
			} else {
				IA::getInstance() -> increaseCitizens();
			}
        break;
        case Enumeration::BuildingType::MainBuilding:
            this->hpMax = 3000;
            this->hp = 3000;
            happiness = 0;
        break;
        case Enumeration::BuildingType::Market:
            this->hpMax = 600;
            this->hp = 600;
            happiness = 10;
            cityLevel = 5;
        break;
        case Enumeration::BuildingType::Quarry:
            this->hpMax = 1000;
            this->hp = 1000;
            happiness = 0;
            cityLevel = 15;
        break;
        case Enumeration::BuildingType::Siderurgy:
            this->hpMax = 1000;
            this->hp = 1000;
            happiness = 0;
            cityLevel = 5;
        break;
        case Enumeration::BuildingType::School:
            this->hpMax = 550;
            this->hp = 550;
            happiness = 5;
            cityLevel = 5;
        break;
        case Enumeration::BuildingType::Tower:
            this->hpMax = 500;
            this->hp = 500;
            happiness = 1;
            cityLevel = 5;
        break;
        case Enumeration::BuildingType::Wall:
            this->hpMax = 200;
            this->hp = 200;
            happiness = 1;
            cityLevel = 1;
        break;
        case Enumeration::BuildingType::Workshop:
            this->hpMax = 800;
            this->hp = 800;
            happiness = 0;
            cityLevel = 15;
            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> setWorkshopBuilt(true);
			} else {
				IA::getInstance() -> setWorkshopBuilt(true);
			}
        break;
    }
    //Graphic engine, this should be in the switch (when models done)
    this->model = modelData;
    this->hitbox = boxData;
    this->type = buildingData;
    this->position = vectorData;
    if (teamData == Enumeration::Team::Human) {
        Human::getInstance() -> increaseHappiness(happiness);
        Human::getInstance() -> increaseCityLevel(cityLevel);
    } else {
        IA::getInstance() -> increaseHappiness(happiness);
        IA::getInstance() -> increaseCityLevel(cityLevel);
    }
}

Building::~Building() {
    
}
