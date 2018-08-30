//
// Created by Rob on 6/29/2018.
//

#include "ShaderProgram.h"
#include "../graphics/OpenGLGraphics.h"


const char *ShaderProgram::mShaderAttrNames[] = {
        "a_Position",
        "a_Color",
        "a_Normal",
        "a_TextureUV",
        "a_PointSize",
        ""
};

const char *ShaderProgram::mShaderUniformNames[] = {
        "u_Color",
        "u_ProjMatrix",
        "u_MVMatrix",
        "u_IT_MVMatrix",
        "u_MVPMatrix",
        "u_PointLightPositions",
        "u_PointLightColors",
        "u_TextureUnit",
        ""
};

const int ShaderProgram::mShaderAttrComps[] = {3, 4, 3, 2, 1};


ShaderProgram::ShaderProgram(const char *vertShaderStr, const char *fragShaderStr) {
    mProgramId = buildProgram(vertShaderStr, fragShaderStr);
}

unsigned int ShaderProgram::buildProgram(const char *vertShaderStr, const char *fragShaderStr) {
    unsigned int vertShaderId = GraphicsIntf->CompileShader(GL_VERTEX_SHADER, vertShaderStr);
    if (!vertShaderId)
        return 0;

    unsigned int fragShaderId = GraphicsIntf->CompileShader(GL_FRAGMENT_SHADER, fragShaderStr);
    if (!fragShaderId)
        return 0;

    unsigned int programId = GraphicsIntf->LinkProgram(vertShaderId, fragShaderId);
    if (programId)
    {
        // Validation.
        if (!GraphicsIntf->ValidateProgram(programId))
        {
            // TODO: Add debug logging.
            programId = 0;
        }
    }

    return programId;
}

void ShaderProgram::useProgram() const {
    GraphicsIntf->UseProgram(mProgramId);
}
