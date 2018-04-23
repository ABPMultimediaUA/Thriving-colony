#ifndef BATTLE_MANAGER_H
#define BATTLE_MANAGER_H

#include <vector>
#include <Enumeration.h>
#include <Unit.h>
#include <Building.h>
#include <Types.h>
#include <MathEngine/Vector2.h>

/**
 * @class BattleManager.
 * @brief Create a BattleManager type object.
 */
class BattleManager {
    
    public:
        /**
         * @brief BattleManager constructor.
         */
        BattleManager();

        /**
         * @brief BattleManager destructor.
         */
        virtual ~BattleManager();

        /**
         * @brief Set an objetive for the entity passed by parameter. Search a troop or building from the enemy prioritizing enemy troops. 
         * 
         * @param The entity passed by parameter is the one whose target will change to Unit, Building or nullptr.
         */
        void askForTarget(Entity*);

    private:

};

#endif