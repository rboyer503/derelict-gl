//
// Created by Rob on 7/5/2018.
//

#include "Square.h"


SquareObject::SquareObject(Vector3 pos, Vector2 size)
        : mPos(pos),
          mSize(size),
          mIsColored(false) {
    mIndices = {0, 1, 2, 0, 2, 3};
    mNumVerts = 4;

    handleDirty();
}

SquareObject::SquareObject(Vector3 pos, Vector2 size, DGLColor color)
        : mPos(pos),
          mSize(size),
          mColor(color),
          mIsColored(true) {
    mIndices = {0, 1, 2, 0, 2, 3};
    mNumVerts = 4;

    handleDirty();
}

void SquareObject::handleDirty() {
    if (mIsColored)
    {
        mVertAttrs.assign(
                {mPos.x, mPos.y, mPos.z, mColor.red, mColor.green, mColor.blue, mColor.alpha,
                 mPos.x, mPos.y + mSize.y, mPos.z, mColor.red, mColor.green, mColor.blue,
                 mColor.alpha,
                 mPos.x + mSize.x, mPos.y + mSize.y, mPos.z, mColor.red, mColor.green, mColor.blue,
                 mColor.alpha,
                 mPos.x + mSize.x, mPos.y, mPos.z, mColor.red, mColor.green, mColor.blue,
                 mColor.alpha});
    }
    else
    {
        mVertAttrs.assign(
                {mPos.x, mPos.y, mPos.z, 0.0f, 0.5f,
                 mPos.x, mPos.y + mSize.y, mPos.z, 0.0f, 0.0f,
                 mPos.x + mSize.x, mPos.y + mSize.y, mPos.z, 1.0f, 0.0f,
                 mPos.x + mSize.x, mPos.y, mPos.z, 1.0f, 0.5f});
    }
}