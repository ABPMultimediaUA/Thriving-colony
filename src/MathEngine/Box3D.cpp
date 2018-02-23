#include "Box3D.h"

using namespace irr;

template <class T>
Box3D<T>::Box3D(){

}

template <class T>
Box3D<T>::Box3D(core::aabbox3d<T> b){
	box = b;
}

template <class T>
Box3D<T>::~Box3D(){

}

template <class T>
void Box3D<T>::set(core::aabbox3d<T> b){
	box = b;
}

template <class T>
void Box3D<T>::set(Box3D<T> other){
	box = other.getAABBox3D();
}

template <class T>
bool Box3D<T>::intersects(Box3D<T> other){
	return box.intersectsWithBox(other.getAABBox3D());
}

template <class T>
core::aabbox3d<T> Box3D<T>::getAABBox3D(){
	return box;
}

template <class T>
Vector3<T> Box3D<T>::getSize() {
   	core::vector3d<T> *edges = new core::vector3d<T>[8]; 
  	box.getEdges(edges);

   	T width = edges[5].X - edges[1].X;
   	T height = edges[1].Y - edges[0].Y;
   	T depth = edges[2].Z - edges[0].Z;

	return Vector3<T>(width, height, depth);
}

template class Box3D<i32>;
template class Box3D<f32>;