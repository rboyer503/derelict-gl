//
// Created by Rob on 7/1/2018.
//

#include "DrawList.h"

#include <algorithm>

#include "../graphics/OpenGLGraphics.h"
#include "../os/Utilities.h"


DrawList::DrawList(const std::vector<eShaderAttr> &shaderAttrVec, bool indexed)
        : IDrawable(shaderAttrVec) {
    mIndexed = indexed;

    mVertexBufferId = GraphicsIntf->GenBuffer();
    if (!mVertexBufferId)
    {
        LOGE("Failed to generate vertex buffer.");
    }

    if (mIndexed)
    {
        mIndexBufferId = GraphicsIntf->GenBuffer();
        if (!mIndexBufferId)
        {
            LOGE("Failed to generate index buffer.");
        }
    }
}

void DrawList::bindData(ShaderProgram &shaderProgram) {
    int offset = 0;
    for (eShaderAttr attr : mShaderAttrVec)
    {
        GraphicsIntf->SetVertexAttrPtr(mVertexBufferId, shaderProgram.getAttrIndex(attr),
                                       ShaderProgram::getShaderAttrComps(attr),
                                       GL_FLOAT, mStride * sizeof(float),
                                       reinterpret_cast<const void *>(offset * sizeof(float)));
        offset += ShaderProgram::getShaderAttrComps(attr);
    }
}

void DrawList::draw() {
    if (mIndexed)
        GraphicsIntf->DrawElementsIndexed(mIndexBufferId, mNumIndices);
    else
        GraphicsIntf->DrawArrays(GL_TRIANGLES, mNumVertAttrs / mStride);
}

void DrawList::addGameObject(const game_object_ptr &gameObject) {
    mGameObjectList.push_back(gameObject);
    mNumVertAttrs += gameObject->getVertAttrs().size();
    mIsDirty = true;

    if (mIndexed)
        mNumIndices += gameObject->getIndices().size();
}

void DrawList::removeGameObject(const game_object_ptr &gameObject) {
    mGameObjectList.remove(gameObject);
    mNumVertAttrs -= gameObject->getVertAttrs().size();
    mIsDirty = true;

    if (mIndexed)
        mNumIndices -= gameObject->getIndices().size();
}

void DrawList::removeAllGameObjects() {
    mGameObjectList.clear();
    mNumVertAttrs = 0;
    mIsDirty = true;

    if (mIndexed)
        mNumIndices = 0;
}

void DrawList::buildBuffers() {
    if (mIsDirty)
    {
        mIsDirty = false;

        mVertAttrs.clear();
        mVertAttrs.reserve(mNumVertAttrs);

        if (mIndexed)
        {
            mIndices.clear();
            mIndices.reserve(mNumIndices);
        }

        unsigned short offset = 0;
        for (auto &element : mGameObjectList)
        {
            mVertAttrs.insert(mVertAttrs.end(), element->getVertAttrs().begin(),
                              element->getVertAttrs().end());

            if (mIndexed)
            {
                std::transform(element->getIndices().begin(), element->getIndices().end(),
                               std::back_inserter(mIndices),
                               [&](unsigned short val) { return val + offset; });
                offset += element->getNumVerts();
            }
        }

        GraphicsIntf->LoadVertexBufferData(mVertexBufferId, mVertAttrs.data(), mNumVertAttrs);

        if (mIndexed)
            GraphicsIntf->LoadIndexBufferData(mIndexBufferId, mIndices.data(), mNumIndices);
    }
}

void DrawList::updateBuffers() {
    if (mIsDirty)
        buildBuffers();

    auto it = mVertAttrs.begin();
    signed long int offset = 0;

    for (auto &element : mGameObjectList)
    {
        if (element->isDirty())
        {
            element->handleDirty();
            element->setDirty(false);
            std::copy(element->getVertAttrs().begin(), element->getVertAttrs().end(), it);
            GraphicsIntf->UpdateVertexBufferData(mVertexBufferId, offset, &(*it),
                                                 element->getVertAttrs().size());
        }
        it += element->getVertAttrs().size();
        offset += element->getVertAttrs().size() * sizeof(float);
    }
}
