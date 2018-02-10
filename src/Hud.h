#ifndef HUD_H
#define HUD_H

#include <irrlicht.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GUIEngine/Rect2D.h>
#include <GUIEngine/TextBox.h>
#include <GUIEngine/Button.h>
#include <GUIEngine/TabPanel.h>
#include <GUIEngine/Tab.h>
#include <GUIEngine/Panel.h>
#include <GUIEngine/Label.h>
#include <GUIEngine/ComboBox.h>
#include <GUIEngine/Widget.h>
#include <GUIEngine/ScrollPanel.h>
#include <GUIEngine/ProgressBar.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/Mouse.h>
#include <Types.h>

using namespace irr;
       
static TextBox *warningText = 0;

/**
 * @class Hud
 * @brief Crea un objeto tipo Hud
 */
class Hud {
    public:
        /**
         * @brief Constructor
         */
        Hud();
        /**
         * @brief Destructor
         */
        ~Hud();

        /**
         * @brief Inicializa el HUD
         */
        void Init();
        /**
         * @brief Actualiza el HUD
         */
        void Update();

        /**
         * @brief Activa una pestaña
         * @param Tipo de pestaña
         */
        void enableTab(Enumeration::BuildingType);
        /**
         * @brief Desctiva una pestaña
         * @param Tipo de pestaña
         */
        void disableTab(Enumeration::BuildingType);

        /**
         * @brief Despliega y muestra el PopUp
         */
        void showPopup();
        /**
         * @brief Despliega y muestra el PopUp
         * @param indica el tipo de pestaña que mostrar en el popup
         */
        void showPopup(Enumeration::BuildingType);
        /**
         * @brief Oculta el PopUp
         */
        void hidePopup();

        /**
         * @brief Actualiza las posiciones de los elementos del HUD
         */
        void updatePositions();

        /**
         * @brief 
         * @param
         * @param
         */
        void addTroopToHall(i32, Enumeration::UnitType);
        /**
         * @brief 
         * @param
         */
        void removeTroopFromHall(i32);

        /**
         * @brief 
         * @param
         * @param
         */
        void addTroopToQueue(i32, Enumeration::UnitType);
        /**
         * @brief
         * @param
         * @param
         */
        void modifyTroopFromQueue(i32, f32);
        /**
         * @brief 
         * @param
         */
        void removeTroopFromQueue(i32);

        /**
         * @brief Devuelve cosas
         * @return pop
         */
        bool getPopUpOpen();
    private:
        bool popUpOpen;
    
        std::vector<i32> troopsInHallIDs;

        std::map<i32, Widget*> troopQueueList;
        std::map<i32, ProgressBar*> troopQueueProgressBars;

        //Buildings panel
        Panel *buildingsPanel;

        Button *buttonOpenPanel;

        //Popup panel
        Panel *tabContainer;
        
        TabPanel *tabs;
        
        Widget *barrackEmpty;
        Widget *barrackContent;
        Widget *barnEmpty;
        Widget *barnContent;
        Widget *workshopEmpty;
        Widget *workshopContent;

        Widget *barrackTroopQueueWidget;
        Widget *barnTroopQueueWidget;
        Widget *workshopTroopQueueWidget;

        ComboBox *hallTroopList;
        
        //Text
        Panel *playerResources;
        Label *playerMetalAmount;
        Label *playerCrystalAmount;
        Label *playerCitizens;
        Label *playerHappiness;
        Label *playerCityLevel;
        Label *playerArmySize;
        Label *playerMelees;
        Label *playerRangeds;
        Label *playerSieges;

        Panel *iaResources;
        Label *iaMetalAmount;
        Label *iaCrystalAmount;
        Label *iaCitizens;
        Label *iaHappiness;
        Label *iaCityLevel;
        Label *iaArmySize;
        Label *iaMelees;
        Label *iaRangeds;
        Label *iaSieges;
        Label *iaNextChoice;
        Label *iaBehaviour;

        f32 updateTimer;
        f32 deleteTextTimer;

        /**
         * @brief Crea un boton 
         * @param id del boton, de tipo entero
         * @param type sera el tipo de edificio que se creara con ese boton, de tipo entero
         */
        void addTab(i32, i32);
};

#endif