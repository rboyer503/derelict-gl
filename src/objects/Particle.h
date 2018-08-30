//
// Created by Rob on 7/16/2018.
//

#ifndef DGL_PARTICLE_H
#define DGL_PARTICLE_H

#include "GameObject.h"
#include "../data/Vectors.h"
#include "../graphics/IGraphics.h"
#include "../physics/IPhysical.h"


class ParticleObject : public GameObject, public IPhysical
{
    static constexpr int NUM_VERT_ATTRS = 8;

    DGLColor mColor;
    float mPointSize = 128.0f;
    float mIntensity = 1.0f;
    bool mActive = false;

public:
    explicit ParticleObject(Vector3 pos, DGLColor color, float pointSize, float intensity,
                            Vector3 maxVel, float mass, float friction, bool active);

    // IPhysical interface:
    void postTransform(bool updated) override;

    const DGLColor &getColor() const { return mColor; }
    const float getPointSize() const { return mPointSize; }
    const float getIntensity() const { return mIntensity; }
    const float getEffectiveIntensity() const {
        if (mActive)
            return mIntensity;
        else
            return 0.0f;
    }
    const bool isActive() const { return mActive; }

    void setColor(const DGLColor &color) {
        mColor = color;
        updateVertAttrs();
    }

    void setPointSize(float pointSize) {
        mPointSize = pointSize;
        updateVertAttrs();
    }

    void setIntensity(float intensity) {
        mIntensity = intensity;
        updateVertAttrs();
    }

    void setActive(bool active) {
        mActive = active;
        updateVertAttrs();
    }

private:
    void updateVertAttrs();

};

typedef std::shared_ptr<ParticleObject> particle_object_ptr;
typedef std::vector<particle_object_ptr> particle_object_vec;


#endif //DGL_PARTICLE_H
