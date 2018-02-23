#ifndef BOX_3D_H
#define BOX_3D_H

#include <irrlicht/irrlicht.h>
#include "Vector3.h"
#include <Types.h>

using namespace irr;

template <class T>
class Box3D {
	public:
		Box3D();
		Box3D(core::aabbox3d<T> box);

		~Box3D();

		void set(Box3D<T> other);
		void set(core::aabbox3d<T> box);

		bool intersects(Box3D<T> other);
		
		Vector3<T> getSize();

		core::aabbox3d<T> getAABBox3D();
	private:
		core::aabbox3d<T> box;
};

#endif