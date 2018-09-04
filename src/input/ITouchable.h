//
// Created by Rob on 8/31/2018.
//

#ifndef DGL_ITOUCHABLE_H
#define DGL_ITOUCHABLE_H

#include <functional>
#include <list>
#include <memory>

#include "../data/Vectors.h"


class ITouchable
{
protected:
    Vector3 mPos;
    Vector2 mSize;
    std::function< bool() > mCallback;

public:
    ITouchable(Vector3 pos, Vector2 size, std::function< bool() > callback = nullptr)
        : mPos(pos),
          mSize(size),
          mCallback(callback) {
    }
    virtual ~ITouchable() = default;

    bool handleTouch(Vector2 touchStartPos, Vector2 touchEndPos);

private:
    bool pointInRange(Vector2 &point);

};

typedef std::shared_ptr<ITouchable> touchable_ptr;
typedef std::list<touchable_ptr> touchable_list;


#endif //DGL_ITOUCHABLE_H
