#include "Unit.h"

#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Map.h"
#include "Hud.h"
#include "GraphicEngine/Window.h"
#include "Troop.h"
#include <WorldEngine/WorldGeometry.h>

Unit::Unit(SceneNode *l, i32 id, Enumeration::Team team, UnitData d) : Entity(id, team, Enumeration::EntityType::Unit) {
    //Layer
    layer = l;

    // Actions of the units
    finished = false;
    moving = false;
    attacking = false;

    // Default target
    target = nullptr;

    //Default state
    state = Enumeration::UnitState::Recruiting;

    // Timers
    lookForTargetTimer = new Timer (0.5, true);
    lookForTargetTimer -> setCallback([&](){
        // Ask for a new target
        Game::Instance() -> getGameState() -> getBattleManager() -> askForTarget(this); //ToDo: La hipocresia
    });

    recruitingTimer = new Timer(0, false);
    recruitingTimer -> setCallback([&](){
        recruitedCallback(this);
        switchState(Enumeration::UnitState::InHome);
    });

    // ToDo: Esto puede ser un timer?
    attackCountdown = 0;

    // Preparado para algo
    readyToEnter = false;

    // Pathfinding
    pathManager = new PathManager(this);

    //Iniciar
    Init();
}

Unit::~Unit() {
    WorldGeometry::Instance()->clearUnitCell(vectorPos, this);
    delete lookForTargetTimer;
    delete pathManager;
    delete troops;
    delete recruitingTimer;
}

void Unit::Init() {
    // Box2D parameters
    Vector2<f32> topLeft;
    Vector2<f32> bottomRight;

    //Texture *tex;
    //const char *path;
    // Basic stats of each unit are here
    f32 recruitingTime = 0;
    /*
        //Metal and crystal costs of each unit.
        enum UnitCost {
            MeleeFootmenMetalCost = 125,
            MeleeFootmenCrystalCost = 0,

            RangedFootmenMetalCost = 150,
            RangedFootmenCrystalCost = 0,

            MountedMeleeMetalCost = 235,
            MountedMeleeCrystalCost = 75,

            MountedRangedMetalCost = 245,
            MountedRangedCrystalCost = 75,

            CreatureMetalCost = 215,
            CreatureCrystalCost = 60,

            CatapultMetalCost = 265,
            CatapultCrystalCost = 160,

            RamMetalCost = 295,
            RamCrystalCost = 160,
        };

        //Army level provided by each type of unit.
        enum ArmyLevel {
            Footmen = 5,
            Mounted = 10,
            Siege = 7,
            Creatures = 15
        };
    switch (type) {
        // Basic melee soldier
        case Enumeration::UnitType::StandardM:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 420;
                attackDamage = 15;
                attackRange = 100;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 80;
                currentHP = 80;
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Footmen;
                attackEvent = "event:/UnitAttack/Drorania_melee_S";
                moveEvent = "event:/UnitMovement/Drorania_melee_S";
                selectEvent = "event:/UnitSelect/Drorania_melee_S";
                metalCost = Enumeration::UnitCost::MeleeFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::MeleeFootmenCrystalCost;
                path = L"media/unitModels/Drorania/Melee_Soldier_Drorania.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 4, ID);
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_melee_soldier.jpg");
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 420;
                attackDamage = 1000;
                attackRange = 100;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 80;
                currentHP = 80;
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Footmen;
                attackEvent = "event:/UnitAttack/Kaonov_melee_S";
                moveEvent = "event:/UnitMovement/Kaonov_melee_S";
                selectEvent = "event:/UnitSelect/Kaonov_melee_S";
                metalCost = Enumeration::UnitCost::MeleeFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::MeleeFootmenCrystalCost;
                path = L"media/unitModels/Kaonov/kaonov_melee_soldier.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 4, ID);
            }
        break;
        //Advanced melee soldier (mounted)
        case Enumeration::UnitType::AdvancedM:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 530;
                attackDamage = 21;
                attackRange = 140;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 140;
                currentHP = 140;
                recruitingTime = 10;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Mounted;
                attackEvent = "event:/UnitAttack/Drorania_melee_A";
                moveEvent = "event:/UnitMovement/Drorania_melee_A";
                selectEvent = "event:/UnitSelect/Drorania_melee_A";
                metalCost = Enumeration::UnitCost::MountedMeleeMetalCost;
                crystalCost = Enumeration::UnitCost::MountedMeleeCrystalCost;
                path = L"media/unitModels/Drorania/criatura_drorania.obj";
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_criature.jpg");
                setModel(layer, path);
                //troops = new Troop(layer, path, 4, ID);
            } else if (breed == Enumeration::BreedType::Kaonov) {
                //This should be changed
                moveSpeed = 530;
                attackDamage = 21;
                attackRange = 140;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 140;
                currentHP = 140;
                recruitingTime = 10;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Mounted;
                attackEvent = "event:/UnitAttack/Kaonov_melee_A";
                moveEvent = "event:/UnitMovement/Kaonov_melee_A";
                selectEvent = "event:/UnitSelect/Kaonov_melee_A";
                metalCost = Enumeration::UnitCost::MountedMeleeMetalCost;
                crystalCost = Enumeration::UnitCost::MountedMeleeCrystalCost;
                path = L"media/unitModels/Kaonov/creature_kaonov.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 4, ID);
            }
        break;
        //Standard ranged unit
        case Enumeration::UnitType::StandardR:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 350;
                attackDamage = 13;
                attackRange = 350;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 60;
                currentHP = 60;
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Footmen;
                attackEvent = "event:/UnitAttack/Drorania_ranged_S";
                moveEvent = "event:/UnitMovement/Drorania_ranged_S";
                selectEvent = "event:/UnitSelect/Drorania_ranged_S";
                metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;
                path = L"media/unitModels/Drorania/rank_soldier_drorania.obj";
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_rank_soldier.jpg");
                setModel(layer, path);
                //troops = new Troop(layer, path, 4, ID);
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 350;
                attackDamage = 13;
                attackRange = 350;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 60;
                currentHP = 60;
                recruitingTime = 5;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Footmen;
                attackEvent = "event:/UnitAttack/Kaonov_ranged_S";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_S";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_S";
                metalCost = Enumeration::UnitCost::RangedFootmenMetalCost;
                crystalCost = Enumeration::UnitCost::RangedFootmenCrystalCost;
                path = L"media/unitModels/Kaonov/kaonov_rank_soldier.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 4, ID);
            }   
        break;
        //Advanced ranged soldier (mounted)
        case Enumeration::UnitType::AdvancedR:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 530;
                attackDamage = 18;
                attackRange = 700;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 110;
                currentHP = 110;
                recruitingTime = 10;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Mounted;
                attackEvent = "event:/UnitAttack/Drorania_ranged_A";
                moveEvent = "event:/UnitMovement/Drorania_ranged_A";
                selectEvent = "event:/UnitSelect/Drorania_ranged_A";
                metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
                crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
                path = L"media/unitModels/Drorania/criatura_drorania.obj";
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_criature.jpg");
                setModel(layer, path);
                //troops = new Troop(layer, path, 0, ID);
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 530;
                attackDamage = 18;
                attackRange = 700;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 110;
                currentHP = 110;
                recruitingTime = 10;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Mounted;
                attackEvent = "event:/UnitAttack/Kaonov_ranged_A";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_A";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_A";
                metalCost = Enumeration::UnitCost::MountedRangedMetalCost;
                crystalCost = Enumeration::UnitCost::MountedRangedCrystalCost;
                path = L"media/unitModels/Kaonov/creature_kaonov.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 0, ID);
            }
        break;
        //Idol (to be defined)
        case Enumeration::UnitType::Idol:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 250;
                attackDamage = 27;
                attackRange = 140;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 180;
                currentHP = 180;
                recruitingTime = 20;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Creatures;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Drorania_melee_A";
                moveEvent = "event:/UnitMovement/Drorania_melee_A";
                selectEvent = "event:/UnitSelect/Drorania_melee_A";
                metalCost = Enumeration::UnitCost::CreatureMetalCost;
                crystalCost = Enumeration::UnitCost::CreatureCrystalCost;
                path = L"media/unitModels/Drorania/Ente_Drorania.obj";
                //tex = new Texture("./media/textures/Drorania/Unit/drorania_entity.jpg");
                setModel(layer, path);
                //troops = new Troop(layer, path, 0, ID);
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 250;
                attackDamage = 27;
                attackRange = 140;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 180;
                currentHP = 180;
                recruitingTime = 20;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Creatures;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_melee_A";
                moveEvent = "event:/UnitMovement/Kaonov_melee_A";
                selectEvent = "event:/UnitSelect/Kaonov_melee_A";
                metalCost = Enumeration::UnitCost::CreatureMetalCost;
                crystalCost = Enumeration::UnitCost::CreatureCrystalCost;
                path = L"media/unitModels/Kaonov/entinity_kaonov.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 0, ID);
            }
        break;
        //Rock launcher
        case Enumeration::UnitType::Launcher:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 250;
                attackDamage = 27;
                attackRange = 900;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 180;
                currentHP = 180;
                recruitingTime = 15;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Siege;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Drorania_ranged_S";
                moveEvent = "event:/UnitMovement/Drorania_ranged_S";
                selectEvent = "event:/UnitSelect/Drorania_ranged_S";
                metalCost = Enumeration::UnitCost::CatapultMetalCost;
                crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
                path = L"media/unitModels/Drorania/dorania_cannon.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 0, ID);
            } 
            else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 250;
                attackDamage = 27;
                attackRange = 900;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 180;
                currentHP = 180;
                recruitingTime = 15;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Siege;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_ranged_S";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_S";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_S";
                metalCost = Enumeration::UnitCost::CatapultMetalCost;
                crystalCost = Enumeration::UnitCost::CatapultCrystalCost;
                path = L"media/unitModels/Kaonov/kaonov_cannon.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 0, ID);
            }
        break;
        //Wall desintegrator
        case Enumeration::UnitType::Desintegrator:
            if (breed == Enumeration::BreedType::Drorania) {
                moveSpeed = 250;
                attackDamage = 41;
                attackRange = 120;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 220;
                currentHP = 220;
                recruitingTime = 20;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Siege;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Drorania_ranged_A";
                moveEvent = "event:/UnitMovement/Drorania_ranged_A";
                selectEvent = "event:/UnitSelect/Drorania_ranged_A";
                metalCost = Enumeration::UnitCost::RamMetalCost;
                crystalCost = Enumeration::UnitCost::RamCrystalCost;
                path = L"media/unitModels/Drorania/drorania_walls_desintegrator.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 0, ID);
            } else if (breed == Enumeration::BreedType::Kaonov) {
                moveSpeed = 250;
                attackDamage = 41;
                attackRange = 120;
                attackSpeed = 1;
                viewRadius = 450;
                maxHP = 220;
                currentHP = 220;
                recruitingTime = 20;
                happiness = -10;
                citizens = -10;
                armyLevel = Enumeration::ArmyLevel::Siege;
                //ToDo: CHANGE
                attackEvent = "event:/UnitAttack/Kaonov_ranged_A";
                moveEvent = "event:/UnitMovement/Kaonov_ranged_A";
                selectEvent = "event:/UnitSelect/Kaonov_ranged_A";
                metalCost = Enumeration::UnitCost::RamMetalCost;
                crystalCost = Enumeration::UnitCost::RamCrystalCost;
                path = L"media/unitModels/Kaonov/kaonov_walls_desintegrator.obj";
                setModel(layer, path);
                //troops = new Troop(layer, path, 0, ID);
            }
        break;
        default: break;
    }*/
    //Material *m = new Material(tex);
    //this->model->setMaterial(m);
    /* Juli */
    
    //troops = new Troop(layer, path, 4, ID);
    //path = L"media/unitModels/Flags/flag.obj";
    //setModel(layer, path);
    preTaxPlayer();
}

void Unit::update() {
    //returnToOriginalColor(); //ToDo: daba segfault aqui en el arbol very unhappy
    attackCountdown -= Window::Instance() -> getDeltaTime();
    //State machine, color changes according to state
    switch (state) {
        case Enumeration::UnitState::Recruiting:
            recruitingState();
        break;
        case Enumeration::UnitState::InHome:
            //inHomeState();
        break;
        case Enumeration::UnitState::Idle:
            //setColor(video::SColor(255, 0, 255, 255)); //ToDo: cambiar por materiales
            idleState();
        break;
        case Enumeration::UnitState::Move:
            //setColor(video::SColor(255, 255, 0, 255)); //ToDo: cambiar por materiales
            moveState();
        break;
        case Enumeration::UnitState::AttackMove:
            //setColor(video::SColor(255, 255, 255, 0)); //ToDo: cambiar por materiales
            attackMoveState();
        break;
        case Enumeration::UnitState::Attack:
            //setColor(video::SColor(255, 0, 0, 0)); //ToDo: cambiar por materiales
            attackState();
        break;    
        case Enumeration::UnitState::Chase:
            //setColor(video::SColor(255, 255, 255, 255)); //ToDo: cambiar por materiales
            chaseState();
        break;
        case Enumeration::UnitState::Retract:
            //setColor(video::SColor(255, 127, 127, 127)); //ToDo: cambiar por materiales
            retractState();
        break;
        default: break;
    }
}

void Unit::preTaxPlayer() {
    if (team == Enumeration::Team::Human) {
        Human::Instance() -> spendResources(metalCost, crystalCost);
        Human::Instance() -> increaseHappiness(happinessVariation);
        Human::Instance() -> increaseCitizens(citizensVariation);
        Human::Instance() -> increaseArmyLevel(armyLevel);
    } else {
        IA::Instance() -> spendResources(metalCost, crystalCost);
        IA::Instance() -> increaseHappiness(happinessVariation);
        IA::Instance() -> increaseCitizens(citizensVariation);
        IA::Instance() -> increaseArmyLevel(armyLevel);
    }
}

void Unit::posTaxPlayer(){
    if (team == Enumeration::Team::Human) {
        Human::Instance() -> increaseArmySize();
    } else {
        IA::Instance() -> increaseArmySize();
    }
}

void Unit::switchState(Enumeration::UnitState newState) {
    lookForTargetTimer -> restart();
    state = newState;
}

void Unit::recruitingState(){
    recruitingTimer -> tick();
    if (!recruitingTimer -> isRunning()){
        if (team == Enumeration::Team::Human){
            Hud::Instance() -> modifyTroopFromQueue(ID, recruitingTimer -> getElapsedTime() / recruitingTimer -> getMaxDuration());
        }
    }
}

void Unit::idleState() {
    if (refreshTarget()) { // if got one
        switchState(Enumeration::UnitState::Chase);
    }
}

void Unit::moveState() {
    moveTroop();
}

void Unit::attackMoveState() {
    attackCountdown -= Window::Instance() -> getDeltaTime();
    // Scan for targets
    if (refreshTarget()) { // if got one
        switchState(Enumeration::UnitState::Chase);
    } else {
        switchState(Enumeration::UnitState::AttackMove);
        moveTroop();  
    }
}

void Unit::attackState() {
    attackCountdown -= Window::Instance() -> getDeltaTime();
    if(inRangeOfAttack()) {
        attack();
    } else {
        switchState(Enumeration::UnitState::Chase);
    }
}

/// Chasing the target
void Unit::chaseState() {
    //If I have a target, then chase it
    if (target != nullptr) {
        Vector2<f32> tpos = Vector2<f32>();
        tpos.x = target->getPosition().x;
        tpos.y = target->getPosition().y;
        this  -> setTroopDestination(tpos);
        chaseTarget();    
    }
}

void Unit::retractState() {
    moveTroop();
    if (readyToEnter){
        retractedCallback(this);
        //troops -> setActive(false);
        getModel() -> setActive(false);
        switchState(Enumeration::UnitState::InHome);
        // Aqui peta
        triggerRetractedCallback();        
    }
}

void Unit::moveTroop() {
    std::cout << "Esto en:" << getPosition().x << "," << getPosition().y << "\n";
    if (moving) {
        // close to destination, stop
        if (steps == 0) {
            if(pathFollow.empty()){
                moving = false;
                if (state == Enumeration::UnitState::Retract) {
                    readyToEnter = true;
                    Human::Instance() -> getUnitManager() -> unSelectTroop();
                    //triggerRetractedCallback();
                    return;
                }
                switchState(Enumeration::Idle);
            }
            else{
                //Vector2<f32> newDest = this->pathFollow.front();
                //Vector2<f32> newDest(dummy.x, dummy.y);
                //setTroopDestination(newDest);
                setTroopDestination(this->pathFollow.front());
                pathFollow.pop_front();
            }
        }
        // Update Cell state 
        else if(std::floor(steps) == 0){
            //Vector2<f32> move = vectorMov;
            //move.x *= 1 + Game::Instance() -> getWindow() -> getDeltaTime() * steps;
            //move.z *= 1 + Game::Instance() -> getWindow() -> getDeltaTime() * steps;
            Vector2<f32> newPos = getPosition() + vectorMov;
            //newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            WorldGeometry::Instance()->updateUnitCell(getPosition(), newPos, this);
            WorldGeometry::Instance()->getNeighborUnits(newPos);
            setTroopPosition(newPos);
            //troops->moveTroops(vectorMov);
            /*Vector3<f32> move = vectorMov;
            Vector3<f32> newPos = vectorPos + move;
            newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            WorldGeometry::Instance()->updateUnitCell(vectorPos.toVector2(), newPos.toVector2(), this);
            WorldGeometry::Instance()->getNeighborUnits(newPos.toVector2());
            setTroopPosition(newPos);*/
            troops -> moveTroops(newPos);
            steps = 0;
            std::cout << "Voy pa:" << newPos.x << "," << newPos.y << "\n";
        } 
        else {
            // far from destination, move
            //Vector2<f32> move = vectorMov;
            //move.x *= 1 + Game::Instance() -> getWindow() -> getDeltaTime();
            //move.z *= 1 + Game::Instance() -> getWindow() -> getDeltaTime();
            Vector2<f32> newPos = getPosition() + vectorMov;
            //newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            WorldGeometry::Instance()->updateUnitCell(getPosition(), newPos, this);
            WorldGeometry::Instance()->getNeighborUnits(newPos);
            setTroopPosition(newPos);
            //troops->moveTroops(vectorMov);
            /*Vector3<f32> move = vectorMov;
            Vector3<f32> newPos = vectorPos + move;
            newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            WorldGeometry::Instance()->updateUnitCell(vectorPos.toVector2(), newPos.toVector2(), this);
            WorldGeometry::Instance()->getNeighborUnits(newPos.toVector2());
            setTroopPosition(newPos);*/
            troops -> moveTroops(newPos);
            steps--;
            std::cout << "Voy pa:" << newPos.x << "," << newPos.y << "\n";
        }
    }
}

void Unit::attack() {
    if (target != nullptr && target -> getTeam() != team) {
        setAttacking(true);
        if (attackCountdown <= 0) {
            target -> takeDamage(attackDamage);
            attackCountdown = attackSpeed;
            if (target -> getCurrentHP() <= 0) {
                if (target -> getTarget() != nullptr) {
                    target -> getTarget() -> removeHostile(target);
                }
                if (team == Enumeration::Team::Human) {
                    if (target -> getEntityType() == Enumeration::EntityType::Unit) {
                        IA::Instance() -> getUnitManager() -> deleteUnit(target -> getID());
                    } else {
                        IA::Instance() -> getBuildingManager() -> deleteBuilding(target -> getID());
                    }
                } else {
                    if (target -> getEntityType() == Enumeration::EntityType::Unit) {
                        Human::Instance() -> getUnitManager() -> deleteUnit(target -> getID());
                    } else {
                        Human::Instance() -> getBuildingManager() -> deleteBuilding(target -> getID());
                    }
                }
                target = nullptr;
                switchState(Enumeration::UnitState::AttackMove);
            }
        }
    }
}

void Unit::chaseTarget() {
    if (moving) {
        // If i can attack, then do so
        if (inRangeOfAttack()) {
            moving = false;
            switchState(Enumeration::UnitState::Attack);
        } else { //If i am too far away to attack, then move closer.
            Vector2<f32> newPos = getPosition() + vectorMov;
            //newPos.y = Map::Instance() -> getTerrain() -> getY(newPos.x, newPos.z);
            setTroopPosition(newPos);
        }
    }
}

/* Edit this */
bool Unit::inRangeOfAttack() {
    bool inRange = false;
    if (target != nullptr) {
        f32 xaux = target->getPosition().x - this->getPosition().x;
        f32 yaux = target->getPosition().y - this->getPosition().y;
        f32 dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));
        if (dist <= attackRange) {
            inRange = true;
        }
    }
    return inRange;
}

bool Unit::refreshTarget() {
    bool targetUpdated = false;
    lookForTargetTimer -> tick();
    // return wether or not it got updated
    if (target != nullptr) {
        targetUpdated = true;
    } else {
        targetUpdated = false;
    }   
    return targetUpdated;
}

void Unit::triggerRecruitedCallback(){
    finished = true;
    recruitedCallback(this);
}

void Unit::triggerRetractedCallback(){
    retractedCallback(this);
}

/////SETTERS/////
void Unit::setUnitCell(Vector2<f32> vectorPosition){
    WorldGeometry::Instance() -> setUnitCell(vectorPosition, this);
}

void Unit::setMoving(bool movingPnt) {
    moving = movingPnt;
}

void Unit::setAttacking(bool attackingPnt) {
    attacking = attackingPnt;
}
/* Weird method */
void Unit::setTroopPosition(Vector2<f32> vectorData) {
    //vectorPos.set(vectorData);
    //vectorPos = vectorData;
    setPosition(vectorData);
    //troops->setPosition(vectorData);
}
// To do -> adjust units movement
void Unit::setTroopDestination(Vector2<f32> vectorData) {
    if (state == Enumeration::UnitState::Move) {
        target = nullptr;
    }
    //vectorDes.set(vectorData);
    vectorDes = vectorData;
    Vector2<f32> desp = vectorDes - getPosition();
    f32 distance = std::sqrt(std::pow(desp.x, 2) + std::pow(desp.y, 2));
    //vectorMov -> x = (desp.x / distance) * moveSpeed * Game::Instance() -> getWindow() -> getDeltaTime();
    //vectorMov -> z = (desp.z / distance) * moveSpeed * Game::Instance() -> getWindow() -> getDeltaTime();
    vectorMov.x = (desp.x / distance) * (moveSpeed / 100);
    vectorMov.y = (desp.y / distance) * (moveSpeed / 100);
    f32 movDistance = std::sqrt(std::pow(vectorMov.x, 2) + std::pow(vectorMov.y, 2));
    steps = distance / movDistance;

    /*vectorDes.set(vectorData);
    Vector3<f32> desp = vectorDes - vectorPos;
    f32 distance = std::sqrt(std::pow(desp.x, 2) + std::pow(desp.z, 2));
    vectorMov.x = (desp.x / distance) * (moveSpeed / 100);
    vectorMov.z = (desp.z / distance) * (moveSpeed / 100);
    f32 movDistance = std::sqrt(std::pow(vectorMov.x, 2) + std::pow(vectorMov.z, 2));
    steps = (distance / movDistance);*/
    moving = true;
}

void Unit::setPath(std::list< Vector2<f32> > path){
    this->pathFollow = path;
}

void Unit::setPathToTarget(Vector2<f32> vectorData){
    std::cout << "Analizando camino \n";
    this->pathManager->createPathTo(vectorData);
    if(!pathFollow.empty()){
        //Vector2<f32> dummy = this->pathFollow.front();
        //Vector2<f32> newDest;
        //newDest.x = dummy.x;
        //newDest.y = Map::Instance() -> getTerrain() -> getY(dummy.x, dummy.y);
        //newDest.y = dummy.y;
        setTroopDestination(this->pathFollow.front());
        std::cout << "Lo tengo " << pathFollow.size() << "\n";
        pathFollow.pop_front();
    }
}

void Unit::setRecruitedCallback(std::function<void(Unit*)> f){
    recruitedCallback = f;
}

void Unit::setRetractedCallback(std::function<void(Unit*)> f){
    retractedCallback = f;
}

/////GETTERS/////
string Unit::getAttackEvent() {
    return attackEvent;
}

string Unit::getMoveEvent() {
    return moveEvent;
}

string Unit::getSelectEvent() {
    return selectEvent;
}

Vector2<f32> Unit::getDestination() {
    return vectorDes;
}

std::list< Vector2<f32> > Unit::getPath(){
    return pathFollow;
}

std::string Unit::getType(){
    return type;
}

Enumeration::UnitState Unit::getState() {
    return state;
}

i32 Unit::getArmyLevel(){
    return armyLevel;
}