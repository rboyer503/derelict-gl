//
// Created by Rob on 7/14/2018.
//

#include "ParticleShaderProgram.h"
#include "../graphics/OpenGLGraphics.h"
#include "../os/Utilities.h"


const char constexpr ParticleShaderProgram::mVertShaderStr[];
const char constexpr ParticleShaderProgram::mFragShaderStr[];


ParticleShaderProgram::ParticleShaderProgram() :
        ShaderProgram(mVertShaderStr, mFragShaderStr) {
    mAttrIndices[ATTR_POSITION] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                           mShaderAttrNames[ATTR_POSITION]);
    mAttrIndices[ATTR_COLOR] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                        mShaderAttrNames[ATTR_COLOR]);
    mAttrIndices[ATTR_POINTSIZE] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                            mShaderAttrNames[ATTR_POINTSIZE]);

    mUniformIndices[UNIFORM_MVMATRIX] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                    mShaderUniformNames[UNIFORM_MVMATRIX]);
    mUniformIndices[UNIFORM_MVPMATRIX] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                     mShaderUniformNames[UNIFORM_MVPMATRIX]);
    mUniformIndices[UNIFORM_TEXTUREUNIT] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                       mShaderUniformNames[UNIFORM_TEXTUREUNIT]);
}

unsigned int ParticleShaderProgram::getAttrIndex(eShaderAttr attr) const {
    return mAttrIndices[attr];
}

unsigned int ParticleShaderProgram::getUniformIndex(eShaderUniform uniform) const {
    return mUniformIndices[uniform];
}

void
ParticleShaderProgram::setUniforms(Matrix4 &mvMatrix, Matrix4 &mvpMatrix, unsigned int textureId) {
    GraphicsIntf->SetUniformMatrix4fv(mUniformIndices[UNIFORM_MVMATRIX], mvMatrix);
    GraphicsIntf->SetUniformMatrix4fv(mUniformIndices[UNIFORM_MVPMATRIX], mvpMatrix);

    GraphicsIntf->BindTexture(mUniformIndices[UNIFORM_TEXTUREUNIT], 0, textureId);
}
