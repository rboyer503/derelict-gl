//
// Created by Rob on 7/18/2018.
//

#ifndef DGL_PHYSICSENGINE_H
#define DGL_PHYSICSENGINE_H

#include "IPhysical.h"


class PhysicsEngine
{
    iphysical_list mPhysicals;

public:
    void addPhysical(const iphysical_ptr &physical) {
        mPhysicals.push_back(physical);
    }

    void removePhysical(const iphysical_ptr &physical) {
        mPhysicals.remove(physical);
    }

    void removeAllPhysicals() {
        mPhysicals.clear();
    }

    void stepTransform();

private:
    void applyTransform(IPhysical *physical);

};


#endif //DGL_PHYSICSENGINE_H
