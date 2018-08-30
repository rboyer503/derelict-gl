//
// Created by Rob on 7/1/2018.
//

#ifndef DGL_DRAWLIST_H
#define DGL_DRAWLIST_H

#include "IDrawable.h"
#include "../objects/GameObject.h"


class DrawList : public IDrawable
{
    game_object_list mGameObjectList;
    unsigned int mVertexBufferId = 0;
    unsigned int mIndexBufferId = 0;
    unsigned int mNumVertAttrs = 0;
    unsigned int mNumIndices = 0;
    std::vector<float> mVertAttrs;
    std::vector<unsigned short> mIndices;
    bool mIndexed = false;
    bool mIsDirty = true;

public:
    DrawList(const std::vector<eShaderAttr> &shaderAttrVec, bool indexed);

    // IDrawable interface:
    void bindData(ShaderProgram &shaderProgram) override;
    void draw() override;

    void addGameObject(const game_object_ptr &gameObject);
    void removeGameObject(const game_object_ptr &gameObject);
    void removeAllGameObjects();

    void buildBuffers();
    void updateBuffers();

    bool isEmpty() const { return (mNumVertAttrs == 0); }
};


#endif //DGL_DRAWLIST_H
