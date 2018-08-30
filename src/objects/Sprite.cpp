//
// Created by Rob on 8/9/2018.
//

#include "Sprite.h"


SpriteObject::SpriteObject(const SpriteFrameMapInfo *frameMapInfo, Vector3 pos, Vector2 size,
                           DGLColor color)
        : mFrameMapInfo(frameMapInfo),
          mPos(pos),
          mSize(size),
          mColor(color) {
    mIndices = {0, 1, 2, 0, 2, 3};
    mNumVerts = 4;

    handleDirty();
}

void SpriteObject::handleDirty() {
    uint32_t col = mFrame % mFrameMapInfo->mapWidth;
    uint32_t row = mFrame / mFrameMapInfo->mapWidth;
    float left = col * mFrameMapInfo->frameSize.x;
    float top = row * mFrameMapInfo->frameSize.y;
    float right = left + mFrameMapInfo->frameSize.x;
    float bottom = top + mFrameMapInfo->frameSize.y;
    mVertAttrs.assign(
            {mPos.x, mPos.y, mPos.z,
             mColor.red, mColor.green, mColor.blue, mColor.alpha,
             left, bottom,
             mPos.x, mPos.y + mSize.y, mPos.z,
             mColor.red, mColor.green, mColor.blue, mColor.alpha,
             left, top,
             mPos.x + mSize.x, mPos.y + mSize.y, mPos.z,
             mColor.red, mColor.green, mColor.blue, mColor.alpha,
             right, top,
             mPos.x + mSize.x, mPos.y, mPos.z,
             mColor.red, mColor.green, mColor.blue, mColor.alpha,
             right, bottom});
}
