#include "Human.h"

#include "IA.h"
#include "GraphicEngine/Window.h"

Human* Human::instance = 0;

Human* Human::Instance() {
    if (instance == 0) {
        instance = new Human();
    }
    return instance;
}

Human::Human() : Player() {
}

Human::~Human() {
    delete buildings;
    delete units;
}

void Human::Init() {
    Player::Init();
    buildings = new BuildingManager(Enumeration::Team::Human, Enumeration::BreedType::Drorania);
    units = new UnitManager(Enumeration::Team::Human, Enumeration::BreedType::Drorania);
    
}

void Human::Update() {
    buildings -> updateBuildingManager();
    units -> updateUnitManager();
    if (updateTimer <= 0.0) {
        gainResources();
        updateTimer = 1.0;
    } else {
       updateTimer -= Window::Instance() -> getDeltaTime();
    }
}

void Human::CleanUp() {
// Add a call to clean the cells the buildings inhabit
    std::cout << "Deleting human building \n";
    delete buildings;
    std::cout << "Human buildings deleted \n";
    
    std::cout << "Deleting human troops \n";
    delete units;
    std::cout << "Human troops deleted \n";
}

bool Human::getUnderAttack() {
    if(underAttack == false){
        Vector3<f32> *pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
        i32 requesterRange = 1000;
        
        f32 xaux = 0;
        f32 yaux = 0;
        f32 dist = 0;
        // Get units in the map of the opposing team
        std::map<i32, Unit*> *inMapTroops = IA::Instance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && underAttack == false; ++it){
            if (it  -> second != nullptr) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition() -> x - pos -> x;
                yaux = it -> second -> getPosition() -> y - pos -> y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist <= requesterRange) {
                    underAttack = true;
                }
            }
        }
    }
    return underAttack;
}

/*
void Human::receiveMetal() {
    metalAmount = metalAmount + 200;
}

void Human::receiveCrystal() {
    crystalAmount = crystalAmount + 200;
}

void Human::receiveCitizens() {
    citizens = citizens + 100;
}
*/