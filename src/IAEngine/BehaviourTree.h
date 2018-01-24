#ifndef BEHAVIOUR_TREE_H
#define BEHAVIOUR_TREE_H

class BehaviourTree {
    
    public:
        BehaviourTree();
        virtual ~BehaviourTree();
        void makeChoice();
/*
        void serviceBranch();
        void unitsBranch();
        void buildingsBranch();
        void armyBranch();
        void resourcesBranch();
*/
        bool needResourcesInvestment();
        bool needArmyInvestment();
        
        bool evaluateWallNeed();

        bool readyToAttack();

        float calculateMetalProductionRate();
        float calculateCrystalProductionRate();
        float calculateCitizensRate();
        float calculateArmyCitizensRate();
        float calculateMeleeRate();
        float calculateRangeRate();
        float calculateSiegeRate();

        int getHospitalMilestone();
        int getMarketMilestone();
        int getQuarryMilestone();
        
        int getCreatureMilestone();
        int getMountedCreatureMilestone();

        int getHappinessThreshold();

        float getMeleeThreshold();
        float getRangeThreshold();
        float getCitizensThreshold();

        bool getShortOnCrystal();
        bool getShortOnMetal(); 

        bool getNeedSoldiers();
        bool getNeedBuildings();

        bool getNeedBarracks();
        bool getNeedBarn();
        bool getNeedWorkshop();
        bool getNeedWall();
        bool getNeedTower();
        
        bool getUnderAttack();
        
        void debugMessage();

        //Goal oriented
        bool getRequireBarrack();
        bool getRequireBarn();
        bool getRequireWorkshop();

        void setRequireBarrack(bool);
        void setRequireBarn(bool);
        void setRequireWorkshop(bool);

        void setRequireCrystal(bool);
        bool getRequireCrystal();

        void setRequireCitizens(bool);
        bool getRequireCitizens();

        void init(int);

    protected:

        int happinessThreshold;
        int quarryMilestone;
        int mountedCreatureMilestone;
        int wallMilestone;
        int towerMilestone;
        int barnMilestone;
        int workshopMilestone;
        int creatureMilestone;

        int hospitalMilestone;
        int marketMilestone;

        float metalThreshold;
        float crystalThreshold;
        float citizensThreshold;
        float armyThreshold;
        float meleeThreshold;
        float rangeThreshold;
        float siegeThreshold;

        bool underAttack;
        // The production rate of a given resource is low in comparison with your city level
        bool shortOnMetal;
        bool shortOnCrystal;

        bool needSoldiers;
        // Dictate the need of a certain building
        bool needBarracks;
        bool needBarn;
        bool needWorkshop;
        bool needWall;
        bool needTower;
        // Dictate the requirement of a certain building
        bool requireBarrack;
        bool requireBarn;
        bool requireWorkshop;

        bool requireCrystal;

        bool requireCitizens;

    private:
};

#endif