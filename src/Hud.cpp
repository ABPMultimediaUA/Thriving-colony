#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Enumeration.h"
#include "GraphicEngine/Window.h"

#include <string>

using namespace irr;

Hud::Hud() {
    //Le botone iniciale
    buttonQuit = new Button(Rect2D<int>(1100, 50, 100, 30), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");

    buttonSchool = new Button(Rect2D<int>(0, 0, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_SCHOOL_BUTTON, L"School", L"Build a school that will improve your citizens happiness.\nMetal cost: 500.\nHappiness +5");
    buttonMarket = new Button(Rect2D<int>(0, 60, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_MARKET_BUTTON, L"Market", L"Build a market that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +10");
    buttonHospital = new Button(Rect2D<int>(0, 120, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_HOSPITAL_BUTTON, L"Hospital", L"Build a hospital that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +15");
    buttonSiderurgy = new Button(Rect2D<int>(0, 180, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_SIDERURGY_BUTTON, L"Siderurgy", L"Build a siderurgy that will produce metal over time.\n Metal cost: 500.\nMetal/second +10");
    buttonQuarry = new Button(Rect2D<int>(0, 240, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_QUARRY_BUTTON, L"Quarry", L"Build a quarry that will produce crystal over time.\n Metal cost: 2000.\nCrystal/second +10");
    buttonHome = new Button(Rect2D<int>(0, 300, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_HOME_BUTTON, L"Home", L"Build a home that will increase your total citizens.\n Metal cost: 100.\nCitizens +10");
    buttonBarrack = new Button(Rect2D<int>(0, 360, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_BARRACK_BUTTON, L"Barrack", L"Build a barrack that will allow you to train basic military units.\n Metal cost: 720.");
    buttonBarn = new Button(Rect2D<int>(0, 420, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_BARN_BUTTON, L"Barn", L"Build a barn that will allow you to train mounted military units.\n Metal cost: 800.");
    buttonWorkshop = new Button(Rect2D<int>(0, 480, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_WORKSHOP_BUTTON, L"Workshop", L"Build a workshop that will allow you to create siege weapons.\n Metal cost: 1100.\nCrystal cost: 230");
    buttonWall = new Button(Rect2D<int>(0, 540, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_WALL_BUTTON, L"Wall", L"Build a wall that will protect your city from outsiders.\n Metal cost: 75.");
    buttonTower = new Button(Rect2D<int>(0, 600, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_TOWER_BUTTON, L"Tower", L"Build a wall that will protect your city from outsiders by attacking them.\n Metal cost: 300.");

    menus = new std::vector<Tab*>();
    buttons = new std::vector<Button*>();

    tabs = new TabPanel(Rect2D<int>(300, 300, 400, 200), 0);
    tabs->disable();

    this->addTab(0, Enumeration::BuildingType::MainBuilding);
    updateTimer = 0.5;
    resourceText = new Text(Rect2D<int>(200, 0, 100, 55), L"Hola mundo", true);
    // Solo de debug
    iaResourceText = new Text(Rect2D<int>(300, 0, 100, 55), L"Hola mundo", true);
    
}

Hud::~Hud() {
    //Los dos botones iniciales
    delete buttonQuit;

    //Los botones edificios
    delete buttonSchool;
    delete buttonMarket;
    delete buttonHospital;
    delete buttonSiderurgy;
    delete buttonQuarry;
    delete buttonHome;
    delete buttonBarrack;
    delete buttonBarn;
    delete buttonWorkshop;
    delete buttonWall;
    delete buttonTower;

    delete tabs;

    delete hallTroopText;
    delete hallTroopList;
    
    delete resourceText;
    delete iaResourceText;
}

void Hud::addTab(int id, int type){
    switch (type) {
        case Enumeration::BuildingType::MainBuilding:
        {
            Tab *t = tabs->addTab(L"Main Building", id);
            menus->push_back(t);

            Button *b = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(120, 10, 100, 20), Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON, L"Deploy selected troop", L"Deploy a troop");
            t->addChild(b);
            buttons->push_back(b);

            hallTroopText = new Text(Rect2D<int>(20, 10, 100, 15), L"Tropas en el ayuntamiento");
            t->addChild(hallTroopText);
            hallTroopList = new ListBox(Rect2D<int>(10, 40, 350, 150));
            t->addChild(hallTroopList);
        }
        break;
        case Enumeration::BuildingType::Barn:
        {
            Tab *t = tabs->addTab(L"Barn", id);
            menus->push_back(t);

            Button *b = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON, L"Crear tropa montada. Ataque cuerpo a cuerpo.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 50, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON, L"Crear tropa montada. Ataque a distancia.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 90, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON, L"Crear ente.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
        }
        break;
        case Enumeration::BuildingType::Barrack:
        {
            Tab *t = tabs->addTab(L"Barrack", id);

            Button *b = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MELEE_TROOP_BUTTON, L"Crear tropa a pie. Ataque cuerpo a cuerpo.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 50, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON, L"Crear tropa a pie. Ataque a distancia.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
        }
        break;
        case Enumeration::BuildingType::Workshop:
        {
            Tab *t = tabs->addTab(L"Workshop", id);

            Button *b = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON, L"Crear maquina de asedio.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
        }
        break;
        default: break;
    }
}

void Hud::showPopup(int tabId){
    tabs->changeActiveTab(tabId);
    tabs->enable();
}

void Hud::hidePopup(){
    tabs->disable();
}

void Hud::getHUDEvents(){
    Game *g = Game::Instance();
    int id = g->getIO()->getGUIClickedID();
    switch(id){
        //Le botone iniciale
        case Enumeration::idGUI::GUI_ID_QUIT_BUTTON:
            g->getWindow()->getDevice()->closeDevice();
        break;
        //Los botones nuevos de cada edificio
        case Enumeration::idGUI::GUI_ID_BUILD_SCHOOL_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::School);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_MARKET_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Market);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_HOSPITAL_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Hospital);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_SIDERURGY_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Siderurgy);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_QUARRY_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Quarry);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_HOME_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::House);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_BARRACK_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barrack);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_BARN_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barn);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_WORKSHOP_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Workshop);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_WALL_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Wall);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_TOWER_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Tower);
        break;
        //Los botones de cada tab
        case Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON:
            tabs->disable();
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MELEE_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Melee;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Tropa melee a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Tropa rango a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Tropa melee en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Tropa rango en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON:
            {
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Ente");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON:
            {
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Maquina de guerra 1");
            }
        break;
        case Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON:
            {
                int index = hallTroopList->getSelected();
                if (index >= 0){
                    hallTroopList->removeItem(index);
                    Human::getInstance()->getUnitManager()->startDeployingTroop(index);
                }
            }
        break;
    }
}

void Hud::update() {
    if (updateTimer <= 0) {
        //ToDo: añadir los metodos de getmetalamount y getcrystalamount
        std::wstringstream os;
        os << L"Player resources:\n" << "Metal: " << std::to_wstring(Human::getInstance() -> getMetalAmount()) << "\nCrystal: " << std::to_wstring(Human::getInstance() -> getCrystalAmount()) << "\nCitizens: " << std::to_wstring(Human::getInstance() -> getCitizens()) << "\nHappiness: " << std::to_wstring(Human::getInstance() -> getHappiness());
        resourceText -> setText(os.str().c_str());
        std::wstringstream iaos;
        iaos << L"IA resources:\n" << "Metal: " << std::to_wstring(IA::getInstance() -> getMetalAmount()) << "\nCrystal: " << std::to_wstring(IA::getInstance() -> getCrystalAmount()) << "\nCitizens: " << std::to_wstring(IA::getInstance() -> getCitizens()) << "\nHappiness: " << std::to_wstring(IA::getInstance() -> getHappiness());
        iaResourceText -> setText(iaos.str().c_str());
        updateTimer = 0.5;
    } else {
        updateTimer -= Window::Instance() ->getDeltaTime();
    }
}

/*hospitalMenu = tabs->addTab(L"Hospital", Enumeration::BuildingType::Hospital);
hospitalMenu->addChild(buttonCloseTab3);
homeMenu = tabs->addTab(L"Home", Enumeration::BuildingType::House);
homeMenu->addChild(buttonCloseTab4);
marketMenu = tabs->addTab(L"Market", Enumeration::BuildingType::Market);
marketMenu->addChild(buttonCloseTab5);
quarryMenu = tabs->addTab(L"Quarry", Enumeration::BuildingType::Quarry);
quarryMenu->addChild(buttonCloseTab6);
siderurgyMenu = tabs->addTab(L"Siderurgy", Enumeration::BuildingType::Siderurgy);
siderurgyMenu->addChild(buttonCloseTab7);
schoolMenu = tabs->addTab(L"School", Enumeration::BuildingType::School);
schoolMenu->addChild(buttonCloseTab8);
towerMenu = tabs->addTab(L"Tower", Enumeration::BuildingType::Tower);
towerMenu->addChild(buttonCloseTab9);
wallMenu = tabs->addTab(L"Wall", Enumeration::BuildingType::Wall); 
wallMenu->addChild(buttonCloseTab10);
buttonCloseTab3 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab4 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab5 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab6 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab7 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab8 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab9 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab10 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab11 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
*/