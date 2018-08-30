//
// Created by Rob on 7/11/2018.
//

#include "WallShaderProgram.h"
#include "../graphics/OpenGLGraphics.h"
#include "../os/Utilities.h"


const char constexpr WallShaderProgram::mVertShaderStr[];
const char constexpr WallShaderProgram::mFragShaderStr[];


WallShaderProgram::WallShaderProgram() :
        ShaderProgram(mVertShaderStr, mFragShaderStr) {
    mAttrIndices[ATTR_POSITION] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                           mShaderAttrNames[ATTR_POSITION]);
    mAttrIndices[ATTR_NORMAL] = GraphicsIntf->GetAttrLoc(mProgramId, mShaderAttrNames[ATTR_NORMAL]);
    mAttrIndices[ATTR_TEXTUREUV] = GraphicsIntf->GetAttrLoc(mProgramId,
                                                            mShaderAttrNames[ATTR_TEXTUREUV]);

    mUniformIndices[UNIFORM_MVMATRIX] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                    mShaderUniformNames[UNIFORM_MVMATRIX]);
    mUniformIndices[UNIFORM_ITMVMATRIX] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                      mShaderUniformNames[UNIFORM_ITMVMATRIX]);
    mUniformIndices[UNIFORM_MVPMATRIX] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                     mShaderUniformNames[UNIFORM_MVPMATRIX]);
    mUniformIndices[UNIFORM_POINTLIGHTPOS] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                         mShaderUniformNames[UNIFORM_POINTLIGHTPOS]);
    mUniformIndices[UNIFORM_POINTLIGHTCOLOR] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                           mShaderUniformNames[UNIFORM_POINTLIGHTCOLOR]);
    mUniformIndices[UNIFORM_TEXTUREUNIT] = GraphicsIntf->GetUniformLoc(mProgramId,
                                                                       mShaderUniformNames[UNIFORM_TEXTUREUNIT]);
}

unsigned int WallShaderProgram::getAttrIndex(eShaderAttr attr) const {
    return mAttrIndices[attr];
}

unsigned int WallShaderProgram::getUniformIndex(eShaderUniform uniform) const {
    return mUniformIndices[uniform];
}

void WallShaderProgram::setUniforms(Matrix4 &mvMatrix, Matrix4 &it_mvMatrix, Matrix4 &mvpMatrix,
                                    std::vector<float> &pointLightPos,
                                    std::vector<float> &pointLightColor, int numPointLights,
                                    unsigned int textureId) {
    GraphicsIntf->SetUniformMatrix4fv(mUniformIndices[UNIFORM_MVMATRIX], mvMatrix);
    GraphicsIntf->SetUniformMatrix4fv(mUniformIndices[UNIFORM_ITMVMATRIX], it_mvMatrix);
    GraphicsIntf->SetUniformMatrix4fv(mUniformIndices[UNIFORM_MVPMATRIX], mvpMatrix);

    GraphicsIntf->SetUniform4fv(mUniformIndices[UNIFORM_POINTLIGHTPOS], pointLightPos,
                                numPointLights);
    GraphicsIntf->SetUniform3fv(mUniformIndices[UNIFORM_POINTLIGHTCOLOR], pointLightColor,
                                numPointLights);

    GraphicsIntf->BindTexture(mUniformIndices[UNIFORM_TEXTUREUNIT], 0, textureId);
}
