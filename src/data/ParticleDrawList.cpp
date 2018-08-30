//
// Created by Rob on 7/14/2018.
//

#include "ParticleDrawList.h"

#include <algorithm>

#include "../graphics/OpenGLGraphics.h"
#include "../os/Utilities.h"


ParticleDrawList::ParticleDrawList(const std::vector<eShaderAttr> &shaderAttrVec)
        : IDrawable(shaderAttrVec) {
}

void ParticleDrawList::bindData(ShaderProgram &shaderProgram) {
    int offset = 0;
    for (eShaderAttr attr : mShaderAttrVec)
    {
        GraphicsIntf->SetVertexAttrPtr(0, shaderProgram.getAttrIndex(attr),
                                       ShaderProgram::getShaderAttrComps(attr),
                                       GL_FLOAT, mStride * sizeof(float),
                                       reinterpret_cast<const void *>(mVertAttrs.data() + offset));
        offset += ShaderProgram::getShaderAttrComps(attr);
    }
}

void ParticleDrawList::draw() {
    GraphicsIntf->DrawArrays(GL_POINTS, static_cast<unsigned int>(mVertAttrs.size() / mStride));
}

void ParticleDrawList::addGameObject(const game_object_ptr &gameObject) {
    mGameObjectList.push_back(gameObject);
    mNumVertAttrs += gameObject->getVertAttrs().size();
    mIsDirty = true;
}

void ParticleDrawList::buildBuffers() {
    if (mIsDirty)
    {
        mIsDirty = false;

        mVertAttrs.clear();
        mVertAttrs.reserve(mNumVertAttrs);

        for (auto &element : mGameObjectList)
        {
            mVertAttrs.insert(mVertAttrs.end(), element->getVertAttrs().begin(),
                              element->getVertAttrs().end());
        }
    }
}

void ParticleDrawList::updateBuffers() {
    if (mIsDirty)
        buildBuffers();
    else
    {
        auto it = mVertAttrs.begin();

        for (auto &element : mGameObjectList)
        {
            if (element->isDirty())
            {
                element->setDirty(false);
                std::copy(element->getVertAttrs().begin(), element->getVertAttrs().end(), it);
            }
            it += mStride;
        }
    }
}
