#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <map>
#include <irrlicht.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Box3D.h>
#include <GraphicEngine/Terrain.h>
#include <GraphicEngine/Model.h>
#include <Enumeration.h>
#include <Building.h>

using namespace irr;

/**
 * @class BuildingManager
 * @brief Crea un objeto tipo BuildingManager
 */
class BuildingManager {
	public:
		/**
		 * @brief Constructor
		 */
		BuildingManager();
		/**
		 * @brief Destructor
		 */
		virtual ~BuildingManager();

		/**
		 * @brief Comprueba las colisiones con el Raycast
		 */
		void testRaycastCollisions();
		/**
		 * @brief Solicita el id de la colision
		 * @return id de tipo entero
		 */
		int getCollisionID();
		/**
		 * @brief Solicita el nombre de la colision
		 * @return string con el nombre
		 */
		std::string getCollisionName();
		/**
		 * @brief Solicita los edificios del mapa
		 * @return devuelve un objeto de tipo hash map con los edificios y sus IDs asociadas
		 */
		std::map<int, Building*>* getBuildings();

		/**
		 * @brief asigna que un edificio este en construccion
		 * @param entero con el tipo de edificio que se esta construyendo
		 */
		void setBuildingMode(Enumeration::BuildingType);
		/**
		 * @brief dibuja el edificio a construir en el terreno
		 * @param terrain donde se indica el terreno en el que construir
		 */
		void drawBuilding(Terrain *terrain);
		/**
		 * @brief Construye el edificio
		 * @param coordenadas en las que se tiene que construir
		 * @param buildingType con el tipo de edificio a construir
		 * @param team indicando el equipo al que pertenece el edificio
		 */
		void buildBuilding(Vector3<float>, Enumeration::BuildingType, Enumeration::Team);

		/**
		 * @brief Comprueba si el jugador tiene recursos necesarios para comprar el edificio
		 * @param metal es el coste de metal del edificio
		 * @param cristal es el coste de cristal del edificio
		 * @param team es el equipo al que pertenecera el edificio
		 * @return true si es solvente y false, en caso contrario
		 */
		bool isSolvent(int, int, Enumeration::Team);
		/**
		 * @brief Registra el tipo de edifio que se quiere construir y 
		 * maneja las llamadas al metodo isSolvent(), enviandole su precio.
		 * @param buildingType especificando el tipo de edicio a construir
		 * @return true si isSolvent()==true y false si !isSolvent()
		 */
		bool checkCanPay(Enumeration::BuildingType);

		/**
		 * @brief Actualiza el manejador de edificios
		 */
		void updateBuildingManager();
		/**
		 * @brief Comprueba si un edificio ha termiando de construirse o no
		 * @return true en caso de que este terminado y false, en caso contrario
		 */
		bool checkFinished(int);

		/**
		 * @brief Asigna, al edificio que se esta construyendo, el modelo 3D asociado
		 * @param coordenadas donde colocar el modelo 3D
		 * @param buildingType es el tipo de edificio que se construye
		 * @param team es el equipo al que pertece el edificio
		 */
		void setTempBuildingModel(Vector3<float>, Enumeration::BuildingType, Enumeration::Team);
		
		/**
		 * @brief Solicita la capa en la que esta edificio
		 * @return layer de tipo SceneNode
		 */
		SceneNode* getBuildingLayer();
	private:
		int id;
        int gridAlignment;
        bool buildingMode;
		
		SceneNode *buildingLayer;
		SceneNode *currentCollision;
		std::map<int, Building*> *buildings;

		Building *tempBuilding;
};

#endif