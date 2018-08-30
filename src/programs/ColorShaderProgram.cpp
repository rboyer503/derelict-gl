//
// Created by Rob on 8/8/2018.
//

#include "ColorShaderProgram.h"
#include "../graphics/OpenGLGraphics.h"
#include "../os/Utilities.h"


const char constexpr ColorShaderProgram::mVertShaderStr[];
const char constexpr ColorShaderProgram::mFragShaderStr[];


ColorShaderProgram::ColorShaderProgram() :
        ShaderProgram(mVertShaderStr, mFragShaderStr) {
    mAttrIndices[ATTR_POSITION] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                           mShaderAttrNames[ATTR_POSITION]);
    mAttrIndices[ATTR_COLOR] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                        mShaderAttrNames[ATTR_COLOR]);
}

unsigned int ColorShaderProgram::getAttrIndex(eShaderAttr attr) const {
    return mAttrIndices[attr];
}

unsigned int ColorShaderProgram::getUniformIndex(eShaderUniform uniform) const {
    return mUniformIndices[uniform];
}
