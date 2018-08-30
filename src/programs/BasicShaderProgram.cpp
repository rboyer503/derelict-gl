//
// Created by Rob on 7/11/2018.
//

#include "BasicShaderProgram.h"
#include "../graphics/OpenGLGraphics.h"
#include "../os/Utilities.h"


const char constexpr BasicShaderProgram::mVertShaderStr[];
const char constexpr BasicShaderProgram::mFragShaderStr[];


BasicShaderProgram::BasicShaderProgram() :
        ShaderProgram(mVertShaderStr, mFragShaderStr) {
    mAttrIndices[ATTR_POSITION] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                           mShaderAttrNames[ATTR_POSITION]);
    mAttrIndices[ATTR_TEXTUREUV] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                            mShaderAttrNames[ATTR_TEXTUREUV]);

    mUniformIndices[UNIFORM_MVPMATRIX] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                     mShaderUniformNames[UNIFORM_MVPMATRIX]);
    mUniformIndices[UNIFORM_TEXTUREUNIT] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                       mShaderUniformNames[UNIFORM_TEXTUREUNIT]);
}

unsigned int BasicShaderProgram::getAttrIndex(eShaderAttr attr) const {
    return mAttrIndices[attr];
}

unsigned int BasicShaderProgram::getUniformIndex(eShaderUniform uniform) const {
    return mUniformIndices[uniform];
}

void BasicShaderProgram::setUniforms(Matrix4 &mvpMatrix, unsigned int textureId) {
    GraphicsIntf->SetUniformMatrix4fv(mUniformIndices[UNIFORM_MVPMATRIX], mvpMatrix);
    GraphicsIntf->BindTexture(mUniformIndices[UNIFORM_TEXTUREUNIT], 0, textureId);
}
