//
// Created by Rob on 7/30/2018.
//

#ifndef DGL_SCENEMANAGER_H
#define DGL_SCENEMANAGER_H

#include "Scene.h"


class SceneManager
{
    scene_vec mSceneVec;
    uint32_t mActiveScene = 0;

public:
    SceneManager() {}
    ~SceneManager() {}

    void addScene(const scene_ptr &scene) { mSceneVec.push_back(scene); }
    void setActiveScene(uint32_t sceneIndex) {
        if (sceneIndex >= mSceneVec.size())
            throw std::runtime_error("SceneManager::setActiveScene: [sceneIndex out of bounds]");

        if (mSceneVec[mActiveScene]->isSceneActive())
        {
            mSceneVec[mActiveScene]->unloadScene();
            mSceneVec[mActiveScene]->removeAllTouchables();
            mSceneVec[mActiveScene]->setSceneActive(false);
        }

        mActiveScene = sceneIndex;
        mSceneVec[mActiveScene]->loadScene();
        mSceneVec[mActiveScene]->setSceneActive(true);
    }

    scene_ptr getActiveScene() {
        if (mActiveScene >= mSceneVec.size())
            return nullptr;

        if (mSceneVec[mActiveScene]->isSceneActive())
            return mSceneVec[mActiveScene];
        else
            return nullptr;
    }
};


#endif //DGL_SCENEMANAGER_H
