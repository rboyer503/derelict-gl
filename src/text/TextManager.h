//
// Created by Rob on 8/8/2018.
//

#ifndef DGL_TEXTMANAGER_H
#define DGL_TEXTMANAGER_H

#include "TextObject.h"
#include "../data/DrawList.h"
#include "../objects/Sprite.h"
#include "../programs/SpriteShaderProgram.h"


class TextManager
{
    const SpriteFrameMapInfo *mFrameMapInfo;
    text_object_list mTextObjectList;
    std::unique_ptr<DrawList> mDrawList;
    std::unique_ptr<SpriteShaderProgram> mShaderProgram;
    unsigned int mFontTextureId = 0;
    bool mInitialized = false;

public:
    TextManager(const SpriteFrameMapInfo *frameMapInfo);

    std::unique_ptr<TextObject>
    buildTextObject(std::string text, uint32_t maxLength, eTextJustifyMode justifyMode, Vector3 pos,
                    Vector2 size, DGLColor color, bool active);

    void addTextObject(const text_object_ptr &text) {
        for (auto &sprite : text->getSpriteVec())
            (*mDrawList).addGameObject(sprite);
        mTextObjectList.push_back(text);
    }

    void removeTextObject(const text_object_ptr &text) {
        for (auto &sprite : text->getSpriteVec())
            (*mDrawList).removeGameObject(sprite);
        mTextObjectList.remove(text);
    }

    void removeAllTextObjects() {
        (*mDrawList).removeAllGameObjects();
        mTextObjectList.clear();
    }

    void setFontTextureId(unsigned int fontTextureId) { mFontTextureId = fontTextureId; }

    void initialize();
    void uninitialize() { mInitialized = false; }
    void render();

private:
    void loadDrawList();
    void buildShaders();
};


#endif //DGL_TEXTMANAGER_H
