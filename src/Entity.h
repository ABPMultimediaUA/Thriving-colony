#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <Types.h>
#include <Enumeration.h> /* Maybe enumeraiton should be removed */
#include <IOEngine/Timer.h>
#include <MathEngine/Box3D.h>
#include <MathEngine/Box2D.h>

class Model;
class SceneNode;

/**
 * @class Entity
 * @brief Crea un objeto tipo Entity
 */
class Entity {

    public:
        Entity(i32, Enumeration::Team, Enumeration::EntityType);
        virtual ~Entity();

        /* MAIN FUNCTIONS */
        void refreshHitbox();
        void takeDamage(i32);
        void addHostile(Entity* hostileTarget);
        void removeHostile(Entity* hostileTarget);
        void putHostileTargetsToNull();

        /* SETTERS */
        void setTarget(Entity*);
        void setModel(SceneNode* sNode, const wchar_t* modelPath);
        void setPosition(Vector2<f32> positionVector);
        void setID(i32 idValue);
        
        /* GETTERS */
        i32 getHP() const;
        i32 getViewRadius() const;
        i32 getHappiness() const;
        i32 getID() const;
        Enumeration::Team getTeam() const; 
        Enumeration::EntityType getEntityType() const; /* Is this needed? We just need to know that's an entity (?) */
        Model* getModel() const;
        std::vector<Entity*> getHostile() const;
        Entity* getTarget() const;
        Vector2<f32> getPosition() const; 
        Box3D<f32> getHitBox() const;
        Box2D getHit() const;
        i32 getCellsX() const;
        i32 getCellsY() const;
    protected:
        i32 ID;
        Enumeration::Team team;
        Enumeration::EntityType entityType;

        //Entity data
        i32 maxHP;
        i32 metalCost;
        i32 crystalCost;
        i32 happiness;
        i32 viewRadius;
        i32 attackRange;

        //Variable data
        Timer *damageTimer;
        i32 currentHP;

        //Model info
        Model *model;
        Box3D<f32> hitbox; //ToDo: revisar si es necesario
        Box2D hitBox; //ToDo: revisar si es necesario
        Vector2<f32> vectorPos;

        //Fight info
        std::vector<Entity*> hostile;
        Entity* target;

        //CellSpace info
        std::vector<i32> kCells; //ToDo: revisar si es necesario
        i32 kCellsX;
        i32 kCellsY;
};

#endif