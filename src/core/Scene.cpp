//
// Created by Rob on 7/30/2018.
//

#include "Scene.h"


void Scene::surfaceChanged(int widthInPixels, int heightInPixels) {
    mProjMatrix = Matrix4(90.0f, static_cast<float>(widthInPixels) /
                                 static_cast<float>(heightInPixels), 0.1f, 100.0f);
    mViewProjMatrix = mProjMatrix * mViewMatrix;
}

bool Scene::applyTouchInput(eInputEvent event, Vector2 &pos) {
    bool handled = false;

    switch (event)
    {
        case INPUT_EVENT_TOUCH_DOWN:
            mTouchStartPos = pos;
            mTouchActive = true;
            break;

        case INPUT_EVENT_TOUCH_UP:
            mTouchCurrPos = pos;
            mTouchActive = false;

            for (touchable_ptr touchable : mTouchableList)
                if (touchable->handleTouch(mTouchStartPos, mTouchCurrPos))
                    handled = true;

            if (!handled)
                mGestureEvent = true;
            break;

        case INPUT_EVENT_TOUCH_MOVE:
            mTouchCurrPos = pos;
            mTouchEvent = true;
            break;

        default:
            break;
    }

    return handled;
}

void Scene::applyPhysics() {
    mPhysicsEngine->stepTransform();
}