//
// Created by Rob on 7/30/2018.
//

#ifndef DGL_SCENE_H
#define DGL_SCENE_H

#include <memory>
#include <vector>

#include "../audio/SoundMetadata.h"
#include "../data/Matrices.h"
#include "../input/Input.h"
#include "../input/ITouchable.h"
#include "../physics/PhysicsEngine.h"


class DGLGame;

class Scene
{
protected:
    DGLGame *mGame;
    bool mIsActive = false;
    uint32_t mState = 0;

    sound_metadata_vec mSoundMetadataVec;

    Matrix4 mViewMatrix;
    Matrix4 mProjMatrix;
    Matrix4 mITViewMatrix;
    Matrix4 mViewProjMatrix;

    std::shared_ptr<PhysicsEngine> mPhysicsEngine;

    touchable_list mTouchableList;

    // Input state.
    Vector2 mTouchStartPos;
    Vector2 mTouchCurrPos;
    bool mTouchActive = false;
    bool mTouchEvent = false;
    bool mGestureEvent = false;

public:
    Scene(DGLGame *game)
            : mGame(game),
              mPhysicsEngine(std::make_shared<PhysicsEngine>()) {}
    virtual ~Scene() {}

    bool isSceneActive() const { return mIsActive; }
    void setSceneActive(bool active) { mIsActive = active; }

    virtual void loadScene() {}
    virtual void unloadScene() {}
    virtual void pause() {}
    virtual void resume() {}
    virtual void backPressed() {}
    virtual void surfaceCreated() {}
    virtual void surfaceChanged(int widthInPixels, int heightInPixels);
    virtual void surfaceDestroyed() {}
    virtual void preTicks() {}
    virtual void tick() {}
    virtual void postTicks() {}
    virtual void render() {}
    virtual void touchInput(eInputEvent event, Vector2 &pos) {}
    virtual void rotationInput(double azimuth, double pitch, double roll) {}

    bool applyTouchInput(eInputEvent event, Vector2 &pos);
    void applyPhysics();

    void addTouchable(const touchable_ptr &touchable) { mTouchableList.push_back(touchable); }
    void removeTouchable(const touchable_ptr &touchable) { mTouchableList.remove(touchable); }
    void removeAllTouchables() { mTouchableList.clear(); }

protected:
    virtual void initSounds() {}

};

typedef std::shared_ptr<Scene> scene_ptr;
typedef std::vector<scene_ptr> scene_vec;


#endif //DGL_SCENE_H
