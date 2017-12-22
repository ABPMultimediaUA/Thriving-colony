#include "Ranged.h"
#include "Human.h"
#include "IA.h"

//The teamData and vectorData are passed to the father, because as the melee class,
//also share the same components
Ranged::Ranged(int id, Enumeration::UnitType::SubClass unitData, Vector3<float> vectorData, Enumeration::Team teamData) : Unit(id, vectorData, teamData)
{

    int metalCost = 0;
    int crystalCost = 0;
    int happiness = -10;
    switch(unitData){
        //Basic stats of each unit are here
        //Basic ranged soldier
        case Enumeration::UnitType::SubClass::StandardR:
            this->moveSpeed = 350;
            this->attackDamage = 13;
            this->attackRange = 500;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 60;
            this->hp = 60;

            metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
            crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;  
        break;
        //Advanced ranged soldier (mounted)
        case Enumeration::UnitType::SubClass::AdvancedR:
            this->moveSpeed = 530;
            this->attackDamage = 18;
            this->attackRange = 550;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 110;
            this->hp = 110;

            metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
            crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
        break;
        //Rock launcher
        case Enumeration::UnitType::SubClass::Launcher:
            this->moveSpeed = 250;
            this->attackDamage = 27;
            this->attackRange = 850;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 180;
            this->hp = 180;

            metalCost = Enumeration::UnitCost::CatapultMetalCost;
            crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
        break;
        //Wall desintegrator
        case Enumeration::UnitType::SubClass::Desintegrator:
            this->moveSpeed = 250;
            this->attackDamage = 41;
            this->attackRange = 180;
            this->attackSpeed = 1;
            this->viewRange = 600;
            this->hpMax = 220;
            this->hp = 220;

            metalCost = Enumeration::UnitCost::RamMetalCost;
            crystalCost = Enumeration::UnitCost::RamCrystalCost;
        break;
    }
    //Graphic engine, this should be in the switch (when models done)
    //this->hitbox = new Box3D<float>();
    //this->modelLayer = new SceneNode();
    this->model = new Model(id); //ToDo: cambiar
    this->model->getModel()->setPosition(vectorData.getVectorF());
    this->model->getModel()->setMaterialFlag(video::EMF_LIGHTING, false);
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(model->getModel()->getMesh(), video::SColor(125, 125, 0, 125));
    this->type = unitData;

    if (teamData == Enumeration::Team::Human) {
        Human::getInstance() -> increaseHappiness(happiness);
        if (unitData == Enumeration::UnitType::SubClass::Launcher) {
            Human::getInstance() -> increaseCatapultAmount();
        }else if (unitData == Enumeration::UnitType::SubClass::Desintegrator) {
            Human::getInstance() -> increaseRamAmount();
        } else {
            Human::getInstance() -> increaseRangeAmount();
        }
        Human::getInstance() -> spendResources(metalCost, crystalCost);
    } else {
        IA::getInstance() -> increaseHappiness(happiness);
        if (unitData == Enumeration::UnitType::SubClass::Launcher) {
            IA::getInstance() -> increaseCatapultAmount();
        }else if (unitData == Enumeration::UnitType::SubClass::Desintegrator) {
            IA::getInstance() -> increaseRamAmount();
        } else {
            IA::getInstance() -> increaseRangeAmount();
        }
        IA::getInstance() -> spendResources(metalCost, crystalCost);
    }


}
//It's empty because there are nothing to delete
//maybe this will change in a future
Ranged::~Ranged() {
    
}