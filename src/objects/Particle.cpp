//
// Created by Rob on 7/16/2018.
//

#include "Particle.h"


ParticleObject::ParticleObject(Vector3 pos, DGLColor color, float pointSize, float intensity,
                               Vector3 maxVel, float mass, float friction, bool active)
        : IPhysical(pos, maxVel, mass, friction),
          mColor(color),
          mPointSize(pointSize),
          mIntensity(intensity),
          mActive(active) {
    mVertAttrs.resize(NUM_VERT_ATTRS);
    updateVertAttrs();
}

void ParticleObject::postTransform(bool updated) {
    if (updated && mActive)
        updateVertAttrs();
}

void ParticleObject::updateVertAttrs() {
    float intensity = mIntensity;
    if (!mActive)
        intensity = 0.0f;

    mVertAttrs[0] = mPos.x;
    mVertAttrs[1] = mPos.y;
    mVertAttrs[2] = mPos.z;
    mVertAttrs[3] = mColor.red * intensity;
    mVertAttrs[4] = mColor.green * intensity;
    mVertAttrs[5] = mColor.blue * intensity;
    mVertAttrs[6] = mColor.alpha;
    mVertAttrs[7] = mPointSize;
    mIsDirty = true;
}
