//
// Created by Rob on 7/18/2018.
//

#ifndef DGL_IPHYSICAL_H
#define DGL_IPHYSICAL_H

#include <list>
#include <memory>
#include <vector>

#include "../data/Vectors.h"
#include "../os/Utilities.h"


class PhysicsEngine;

class IPhysical
{
    friend class PhysicsEngine;

protected:
    Vector3 mPos;
    Vector3 mVel;
    Vector3 mMaxVel;
    Vector3 mAccel;
    float mMass;
    float mFriction;
    std::vector<Vector3> mForces;

public:
    explicit IPhysical(Vector3 pos, Vector3 maxVel, float mass, float friction)
            : mPos(pos),
              mMaxVel(maxVel),
              mMass(mass),
              mFriction(friction) {}
    virtual ~IPhysical() = default;

    const Vector3 &getPosition() const { return mPos; }

    void setPosition(const Vector3 &pos) {
        mPos = pos;
        postTransform(true);
    }

    void setVelocity(const Vector3 &vel) {
        mVel = vel;
    }

    void addForce(const Vector3 &force) {
        mForces.push_back(force);
    }

    void updateForce(size_t forceIndex, const Vector3 &force) {
        if (forceIndex < mForces.size())
            mForces[forceIndex] = force;
    }

    std::vector<Vector3> &getForces() {
        return mForces;
    }

    virtual void postTransform(bool updated) {};

};

typedef std::shared_ptr<IPhysical> iphysical_ptr;
typedef std::list<iphysical_ptr> iphysical_list;


#endif //DGL_IPHYSICAL_H
