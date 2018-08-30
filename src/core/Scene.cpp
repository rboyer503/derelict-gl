//
// Created by Rob on 7/30/2018.
//

#include "Scene.h"


void Scene::surfaceChanged(int widthInPixels, int heightInPixels) {
    mProjMatrix = Matrix4(90.0f, static_cast<float>(widthInPixels) /
                                 static_cast<float>(heightInPixels), 0.1f, 100.0f);
    mViewProjMatrix = mProjMatrix * mViewMatrix;
}

void Scene::applyPhysics() {
    mPhysicsEngine->stepTransform();
}