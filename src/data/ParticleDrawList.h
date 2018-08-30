//
// Created by Rob on 7/14/2018.
//

#ifndef DGL_PARTICLEDRAWLIST_H
#define DGL_PARTICLEDRAWLIST_H

#include "IDrawable.h"
#include "../objects/GameObject.h"


class ParticleDrawList : public IDrawable
{
    game_object_list mGameObjectList;
    unsigned int mNumVertAttrs = 0;
    std::vector<float> mVertAttrs;
    bool mIsDirty = false;

public:
    ParticleDrawList(const std::vector<eShaderAttr> &shaderAttrVec);

    std::vector<float> &GetVertAttrs() { return mVertAttrs; }

    // IDrawable interface:
    void bindData(ShaderProgram &shaderProgram) override;
    void draw() override;

    void addGameObject(const game_object_ptr &gameObject);
    void buildBuffers();
    void updateBuffers();
};


#endif //DGL_PARTICLEDRAWLIST_H
