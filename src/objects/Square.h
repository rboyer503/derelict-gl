//
// Created by Rob on 7/5/2018.
//

#ifndef DGL_SQUARE_H
#define DGL_SQUARE_H

#include <memory>

#include "GameObject.h"
#include "../data/Vectors.h"
#include "../graphics/IGraphics.h"


class SquareObject : public GameObject
{
    Vector3 mPos;
    Vector2 mSize;
    DGLColor mColor;
    bool mIsColored;

public:
    SquareObject(Vector3 pos, Vector2 size);
    SquareObject(Vector3 pos, Vector2 size, DGLColor color);

    void handleDirty() override;

    void setColor(DGLColor color) {
        mColor = color;
        mIsDirty = true;
    }
};

typedef std::shared_ptr<SquareObject> square_ptr;
typedef std::vector<square_ptr> square_vec;


#endif //DGL_SQUARE_H
