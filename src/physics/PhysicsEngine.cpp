//
// Created by Rob on 7/18/2018.
//

#include "PhysicsEngine.h"

#include <numeric>


void PhysicsEngine::stepTransform() {
    for (iphysical_ptr physical : mPhysicals)
        applyTransform(physical.get());
}

void PhysicsEngine::applyTransform(IPhysical *physical) {
    Vector3 origPos = physical->mPos;

    Vector3 totalForce = std::accumulate(physical->mForces.begin(), physical->mForces.end(),
                                         Vector3());
    physical->mAccel = totalForce / physical->mMass;

    physical->mVel += physical->mAccel;
    physical->mVel *= physical->mFriction;
    physical->mVel.limit(physical->mMaxVel);

    physical->mPos += physical->mVel;

    physical->postTransform(physical->mPos != origPos);
}
