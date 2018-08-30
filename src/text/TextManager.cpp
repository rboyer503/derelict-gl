//
// Created by Rob on 8/8/2018.
//

#include "TextManager.h"
#include "../graphics/OpenGLGraphics.h"


TextManager::TextManager(const SpriteFrameMapInfo *frameMapInfo)
        : mFrameMapInfo(frameMapInfo) {
}

std::unique_ptr<TextObject>
TextManager::buildTextObject(std::string text, uint32_t maxLength, eTextJustifyMode justifyMode,
                             Vector3 pos, Vector2 size, DGLColor color, bool active) {
    return std::unique_ptr<TextObject>(
            new TextObject(mFrameMapInfo, text, maxLength, justifyMode, pos, size, color, active));
}

void TextManager::initialize() {
    if (!mInitialized)
    {
        mInitialized = true;
        loadDrawList();
        buildShaders();
    }
}

void TextManager::render() {
    (*mDrawList).updateBuffers();
    if (!(*mDrawList).isEmpty())
    {
        GraphicsIntf->SetBlend(BLEND_MODE_ONE_ONE);
        (*mShaderProgram).useProgram();
        (*mShaderProgram).setUniforms(mFontTextureId);
        (*mDrawList).bindData(*mShaderProgram);
        (*mDrawList).draw();
        GraphicsIntf->SetBlend(BLEND_MODE_NONE);
    }
}

void TextManager::loadDrawList() {
    mDrawList.reset(new DrawList({ATTR_POSITION, ATTR_COLOR, ATTR_TEXTUREUV}, true));

    for (auto &text : mTextObjectList)
    {
        for (auto &sprite : text->getSpriteVec())
            (*mDrawList).addGameObject(sprite);
    }

    (*mDrawList).buildBuffers();
}

void TextManager::buildShaders() {
    mShaderProgram.reset(new SpriteShaderProgram());
}