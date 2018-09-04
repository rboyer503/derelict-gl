//
// Created by Rob on 8/31/2018.
//

#include "ITouchable.h"


bool ITouchable::handleTouch(Vector2 touchStartPos, Vector2 touchEndPos) {
    if (mCallback)
    {
        if (pointInRange(touchStartPos) && pointInRange(touchEndPos))
            return mCallback();
    }

    return false;
}

bool ITouchable::pointInRange(Vector2 &point) {
    return ((point.x >= mPos.x) && (-point.y >= mPos.y) && (point.x <= (mPos.x + mSize.x)) &&
            (-point.y <= (mPos.y + mSize.y)));
}
