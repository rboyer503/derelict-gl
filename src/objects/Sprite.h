//
// Created by Rob on 8/9/2018.
//

#ifndef DGL_SPRITE_H
#define DGL_SPRITE_H

#include <memory>

#include "GameObject.h"
#include "../data/Vectors.h"
#include "../graphics/IGraphics.h"
#include "../input/ITouchable.h"


struct SpriteFrameMapInfo
{
    Vector2 frameSize;
    int mapWidth;
    int mapHeight;
};


class SpriteObject : public GameObject, public ITouchable
{
    const SpriteFrameMapInfo *mFrameMapInfo;
    uint32_t mFrame = 0;
    DGLColor mColor;

public:
    SpriteObject(const SpriteFrameMapInfo *frameMapInfo, Vector3 pos, Vector2 size,
                 DGLColor color, std::function< bool() > callback = nullptr);

    void handleDirty() override;

    void setFrame(uint32_t frame) {
        mFrame = frame;
        mIsDirty = true;
    }

    void updateColor(DGLColor color) {
        mColor = color;
        mIsDirty = true;
    }
};

typedef std::shared_ptr<SpriteObject> sprite_ptr;
typedef std::vector<sprite_ptr> sprite_vec;


#endif //DGL_SPRITE_H
