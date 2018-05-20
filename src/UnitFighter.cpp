#include "UnitFighter.h"
#include "MathEngine/Vector3.h"
#include "Map.h"
#include "GraphicEngine/Window.h"
#include "IOEngine/Timer.h"
#include "IOEngine/IO.h"
<<<<<<< HEAD
UnitFighter::UnitFighter(SceneNode* _parent, std::string _path, f32 _speed):speed(_speed), isMoving(false), maxDesviation(_speed * 0.5f), maxTime(0), unitFighterClock(nullptr), fighterState(Enumeration::UnitFighterState::ufMove){
=======

UnitFighter::UnitFighter(SceneNode* _parent, std::string _path, f32 _speed):speed(_speed), isMoving(false), maxDesviation(_speed * 0.5f), maxTime(0), unitFighterClock(nullptr), fighterState(Enumeration::UnitFighterState::ufIdle) {
>>>>>>> 2cabd49d1611ca22b2723c026fc3ffdb4e594460
    fighterModel = new Animation(_parent, _path);
    vectorPosition = Vector2<f32>(0, 0);
    vectorSpeed = Vector2<f32>(0, 0);
    vectorDestiny = Vector2<f32>(0, 0);
    vectorDirection = Vector2<f32>(0, 0);
    nearFighters = std::vector< UnitFighter* >();
    unitFighterClock = new Timer(1, false, false);
    unitFighterClock->setCallback([&]{
        isMoving = false;
    });
}

<<<<<<< HEAD
UnitFighter::~UnitFighter(){
=======
UnitFighter::~UnitFighter() {
    IO::Instance()->unregisterTimer(unitFighterClock);
>>>>>>> 2cabd49d1611ca22b2723c026fc3ffdb4e594460
    delete unitFighterClock;
    delete fighterModel;
    nearFighters.clear();
}

void UnitFighter::setPosition(Vector2<f32> _pos) {
    vectorPosition = _pos;
}

<<<<<<< HEAD
void UnitFighter::setDestiny(Vector2<f32> _dest){
    if(fighterState != Enumeration::UnitFighterState::ufMove && fighterState != Enumeration::UnitFighterState::ufConfront){
        switchState(Enumeration::UnitFighterState::ufMove);
    }
=======
void UnitFighter::setDestiny(Vector2<f32> _dest) {
>>>>>>> 2cabd49d1611ca22b2723c026fc3ffdb4e594460
    vectorDestiny = _dest;
    Vector2<f32> vectorDistance = (vectorDestiny - vectorPosition);
    maxTime = (std::sqrt(std::pow(vectorDistance.x, 2) + std::pow(vectorDistance.y, 2))) / speed * 0.016f ;
    maxTime += 0.15f * maxTime;
    unitFighterClock->changeDuration(maxTime);
    unitFighterClock->restart();

    isMoving = true;
}

void UnitFighter::move(){
    if(isMoving){
        if(!hasArrived()){
            calculateDirection();
            Vector2<f32> _oldPosition = vectorPosition;
            vectorSpeed = vectorDirection * speed;
            vectorPosition += vectorSpeed;
            vectorPosition = _oldPosition + (vectorPosition - _oldPosition) * Window::Instance()->getDeltaTimeVariance();
            fighterModel->setPosition(Vector3<f32>(vectorPosition.x, Map::Instance()->getTerrain()->getY(vectorPosition.x, vectorPosition.y), vectorPosition.y));
        }   
        else{
            isMoving = false;
            unitFighterClock->stop();
            if(fighterState == Enumeration::UnitFighterState::ufMove){
                switchState(Enumeration::UnitFighterState::ufIdle);
            }
            if(fighterState == Enumeration::UnitFighterState::ufConfront){
                switchState(Enumeration::UnitFighterState::ufAttack);
            }
        }
    }
}

void UnitFighter::update() {
    if (isMoving) {
        move();
    }
    switch(fighterState) {
        case Enumeration::UnitFighterState::ufAttack:
            //ufAttackState();
        break;

        case Enumeration::UnitFighterState::ufMove:
            //ufMoveState();
        break;

        case Enumeration::UnitFighterState::ufIdle:
            //ufIdleState();
        break;

        case Enumeration::UnitFighterState::ufConfront:
            //ufConfrontState();
        break;
    
        default: 
            std::cout << "INVALID UNITfightER STATE \n";
        break;
    }
}

void UnitFighter::switchState(Enumeration::UnitFighterState _state) {
    // Do something (clocks ?)
    switch(_state) {
        case Enumeration::UnitFighterState::ufAttack:
            if(fighterState != Enumeration::UnitFighterState::ufAttack){
                //std::cout << "Estado attack";
                fighterState = _state;
                ufAttackState();
            }
        break;

        case Enumeration::UnitFighterState::ufMove:
            if(fighterState != Enumeration::UnitFighterState::ufMove){
                //std::cout << "Estado move";
                fighterState = _state;
                ufMoveState();
            }
        break;

        case Enumeration::UnitFighterState::ufIdle:
            if(fighterState != Enumeration::UnitFighterState::ufIdle){
                //std::cout << "Estado idle";
                fighterState = _state;
                ufIdleState();
            }
        break;

        case Enumeration::UnitFighterState::ufConfront:
            if(fighterState != Enumeration::UnitFighterState::ufConfront){
                //std::cout << "Estado confront";
                fighterState = _state;
                ufConfrontState();
            }
        break;

        default: 
            std::cout << "INVALID UNITfightER STATE \n";
        break;
    }
}

void UnitFighter::ufAttackState() {
    /* Animation attack */
    fighterModel->changeAnimation("attack");
}

void UnitFighter::ufMoveState() {
    /* Animation move */
    fighterModel->changeAnimation("walk");
}

void UnitFighter::ufIdleState() {
    /* Animation IDLE */
    fighterModel->changeAnimation("idle");
}

void UnitFighter::ufConfrontState() {
    /* LOCURA */
    fighterModel->changeAnimation("walk");
}

void UnitFighter::setNearFighters(std::vector<UnitFighter*>& _nearFighters) {
    nearFighters = _nearFighters;
}

void UnitFighter::setActive(bool _active) {
    fighterModel->setActive(_active);
}

Vector2<f32> UnitFighter::getVectorPosition() const{
    return vectorPosition;
}

Vector2<f32> UnitFighter::getVectorSpeed() const{
    return vectorSpeed;
}

Vector2<f32> UnitFighter::getVectorDestiny() const{
    return vectorDestiny;
}

const f32 UnitFighter::getSpeed() const{
    return speed;
}

bool UnitFighter::hasArrived() {
    if ((vectorPosition - vectorDestiny).dotProduct() < maxDesviation) {
        vectorSpeed = Vector2<f32>(0, 0);
        return true;
    }
    return false;
}

/* Maybe we can calculate it in only one method */
Vector2<f32> UnitFighter::calculateFlocking() {
    Vector2<f32> alignment(0, 0);
    Vector2<f32> cohesion(0, 0);
    Vector2<f32> separation(0, 0);
    Vector2<f32> flock(0, 0);
    i32 k(0);
    f64 distance(0);
    Vector2<f32> other(0, 0);

    for (std::size_t i = 0; i < nearFighters.size(); i++) {
        if (nearFighters[i] != this) {
            other = nearFighters[i]->getVectorPosition();
            distance = std::sqrt(std::pow(other.x - vectorPosition.x, 2) + std::pow(other.y - vectorPosition.y, 2));
            if (distance < 15.0f) {
                /* Alignment */
                alignment += nearFighters[i]->getVectorSpeed();
                /* Cohesion */
                cohesion += other;
                /* Separation */
                separation += (other - vectorPosition);
                /* Count */
                k++;
            }
        }   
    }
    /* Final maths */
    if (k == 0) {
        return flock;
    }

    /* Alignment */
    alignment = alignment / k;
    if (alignment.x != 0 || alignment.y != 0) {
        distance = std::sqrt(std::pow(alignment.x, 2) + std::pow(alignment.y, 2));
        alignment = alignment / distance;
    }

    /* Cohesion */
    cohesion = cohesion / k;
    cohesion = cohesion - vectorPosition;
    if (cohesion.x != 0 || cohesion.y != 0) {
        distance = std::sqrt(std::pow(cohesion.x, 2) + std::pow(cohesion.y, 2));

        cohesion = cohesion / distance;
    }
    
    /* Separation */
    separation = (separation * (-1)) / k;
    if (separation.x != 0 || separation.y != 0) {
        distance = std::sqrt(std::pow(separation.x, 2) + std::pow(separation.y, 2));
        separation = separation / distance;
    }

    flock = alignment * 1.1f + cohesion * 1.0f + separation * 1.1f;

    /* Normalize Flock */
    if (flock.x != 0 || flock.y != 0) {
        distance = std::sqrt(std::pow(flock.x, 2) + std::pow(flock.y, 2));
        flock = flock / distance;
    }

    return flock;
}

void UnitFighter::calculateDirection() {
    Vector2<f32> _incVector = vectorDestiny - vectorPosition;
    /* Calculate speed */
    f32 distance = std::sqrt(std::pow(_incVector.x, 2) + std::pow(_incVector.y ,2));
    if (distance != 0) {
        vectorDirection = _incVector / distance;
        vectorDirection += calculateFlocking();
        
        /* Normalize */
        if (vectorDirection.x != 0 || vectorDirection.y != 0) {
            distance = std::sqrt(std::pow(vectorDirection.x, 2) + std::pow(vectorDirection.y, 2));
            vectorDirection = vectorDirection / distance;   
        }
<<<<<<< HEAD
        //fighterModel->setRotation(Vector3<f32>(vectorDirection.x, 0, vectorDirection.y));
    }   
    else{
=======
        fighterModel -> setRotation(Vector3<f32>(vectorDirection.x, 0, vectorDirection.y));
    } else {
>>>>>>> 2cabd49d1611ca22b2723c026fc3ffdb4e594460
        vectorDirection = Vector2<f32>(0, 0);
    }
}