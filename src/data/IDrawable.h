//
// Created by Rob on 6/29/2018.
//

#ifndef DGL_IDRAWABLE_H
#define DGL_IDRAWABLE_H

#include <vector>

#include "../programs/ShaderProgram.h"
#include "../os/Utilities.h"


class IDrawable
{
protected:
    std::vector<eShaderAttr> mShaderAttrVec;
    int mStride = 0;

public:
    IDrawable(const std::vector<eShaderAttr> &shaderAttrVec) : mShaderAttrVec(shaderAttrVec) {
        for (eShaderAttr attr : mShaderAttrVec)
            mStride += ShaderProgram::getShaderAttrComps(attr);
    }
    virtual ~IDrawable() = default;

    virtual void bindData(ShaderProgram &shaderProgram) = 0;
    virtual void draw() = 0;
};


#endif //DGL_IDRAWABLE_H
