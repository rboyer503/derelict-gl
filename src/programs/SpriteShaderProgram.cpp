//
// Created by Rob on 8/8/2018.
//

#include "SpriteShaderProgram.h"
#include "../graphics/OpenGLGraphics.h"
#include "../os/Utilities.h"


const char constexpr SpriteShaderProgram::mVertShaderStr[];
const char constexpr SpriteShaderProgram::mFragShaderStr[];


SpriteShaderProgram::SpriteShaderProgram() :
        ShaderProgram(mVertShaderStr, mFragShaderStr) {
    mAttrIndices[ATTR_POSITION] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                           mShaderAttrNames[ATTR_POSITION]);
    mAttrIndices[ATTR_COLOR] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                        mShaderAttrNames[ATTR_COLOR]);
    mAttrIndices[ATTR_TEXTUREUV] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                            mShaderAttrNames[ATTR_TEXTUREUV]);

    mUniformIndices[UNIFORM_TEXTUREUNIT] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                       mShaderUniformNames[UNIFORM_TEXTUREUNIT]);
}

unsigned int SpriteShaderProgram::getAttrIndex(eShaderAttr attr) const {
    return mAttrIndices[attr];
}

unsigned int SpriteShaderProgram::getUniformIndex(eShaderUniform uniform) const {
    return mUniformIndices[uniform];
}

void SpriteShaderProgram::setUniforms(unsigned int textureId) {
    GraphicsIntf->BindTexture(mUniformIndices[UNIFORM_TEXTUREUNIT], 0, textureId);
}
