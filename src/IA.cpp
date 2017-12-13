#include "IA.h"

IA::IA() : Player() {
    happiness = 0;
    cityLevel = 1;
    
    siderurgyAmount = 1;
    quarryAmount= 0;
    
    citizens = 0;

    armySize = 0;
    meleeAmount = 0;
    rangeAmount = 0;
    siegeAmount = 0;
    catapultAmount = 0;
    ramAmount = 0;

    wallBuilt = false;
    barrackBuilt = false;
    barnBuilt = false;
    workshopBuilt = false;

    tree = new BehaviourTree();
}

IA::~IA() {
    delete tree;
}

IA* IA::instance = 0;

IA* IA::getInstance() {
    if (instance == 0) {
        instance = new IA();
    }
    return instance;
}

BehaviourTree* IA::getTree() {
    return tree;
}

/*
* Return a position of the map where there is nothing built
* Goes over the vector of building looking up, right, down and left of every building built
* until find the first empty position
*/
Vector3<float>* IA::determinatePositionBuilding() {
    Vector3<float> *v = 0;
    bool found = false;
    bool occupied = false;
    std::vector<Building*> *b = buildings -> getBuildings();

    // If it is the first building start always on the same position
    // ToDo: como el primer edificio va a ser el centro de mandos que ya va a estar
    // construido, esto no haria falta
    if (b -> size() == 0) {
        v = new Vector3<float>(1600, 300, 1500);
    } else {

        //When there are some buildings
        Vector3<float> *v2 = 0;
        Vector3<float> *v3 = 0;
        for (int i = 0; i < b -> size() && found == false; i++) {
            v2 = b -> at(i) -> getPosition();
            occupied = false;
            v = new Vector3<float>(v2 -> x, v2 -> y, v2 -> z + 100);
            for (int j = 0; j < b -> size() && occupied == false; j++) {
                v3 = b -> at(j) -> getPosition();
                if (v3 -> x == v -> x && v3 -> z == v -> z) {
                    occupied = true;
                }
            }
            if (occupied == false ) {
                found = true;
            } else {
                v = new Vector3<float>(v2 -> x + 100, v2 -> y, v2 -> z);
                occupied = false;
                for (int j = 0; j < b -> size() && occupied == false; j++) {
                    v3 = b -> at(j) -> getPosition();
                    if (v3 -> x == v -> x && v3 -> z == v -> z) {
                        occupied = true;
                    }
                }
                if (occupied == false ) {
                    found = true;
                } else {
                    v = new Vector3<float>(v2 -> x, v2 -> y, v2 -> z - 100);
                    occupied = false;
                    for (int j = 0; j < b -> size() && occupied == false; j++) {
                        v3 = b -> at(j) -> getPosition();
                        if (v3 -> x == v -> x && v3 -> z == v -> z) {
                            occupied = true;
                        }
                    }
                    if (occupied == false ) {
                        found = true;
                    } else {
                        v = new Vector3<float>(v2 -> x - 100, v2 -> y, v2 -> z);
                        occupied = false;
                        for (int j = 0; j < b -> size() && occupied == false; j++) {
                            v3 = b -> at(j) -> getPosition();
                            if (v3 -> x == v -> x && v3 -> z == v -> z) {
                                occupied = true;
                            }
                        }
                        if (occupied == false ) {
                            found = true;
                        }
                    }
                }
            }
        }
    }
    return v;
}