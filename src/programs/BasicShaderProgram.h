//
// Created by Rob on 8/8/2018.
//

#ifndef DGL_BASICSHADERPROGRAM_H
#define DGL_BASICSHADERPROGRAM_H

#include "ShaderProgram.h"
#include "../data/Matrices.h"


class BasicShaderProgram : public ShaderProgram
{
    static const char constexpr mVertShaderStr[] =
            "#version 100\n"
                    "uniform mat4 u_MVPMatrix;\n"

                    "attribute vec4 a_Position;\n"
                    "attribute vec2 a_TextureUV;\n"

                    "varying vec2 v_TextureUV;\n"

                    "void main() {\n"
                    "    v_TextureUV = a_TextureUV;\n"
                    "    gl_Position = u_MVPMatrix * a_Position;\n"
                    "}\n";

    static const char constexpr mFragShaderStr[] =
            "#version 100\n"
                    "precision mediump float;\n"

                    "uniform sampler2D u_TextureUnit;\n"

                    "varying vec2 v_TextureUV;\n"

                    "void main() {\n"
                    "    gl_FragColor = texture2D(u_TextureUnit, v_TextureUV);\n"
                    "}\n";

    unsigned int mAttrIndices[ATTR_MAX] = {0};
    unsigned int mUniformIndices[UNIFORM_MAX] = {0};

public:
    BasicShaderProgram();

    unsigned int getAttrIndex(eShaderAttr attr) const override;
    unsigned int getUniformIndex(eShaderUniform uniform) const override;

    void setUniforms(Matrix4 &mvpMatrix, unsigned int textureId);

};


#endif //DGL_BASICSHADERPROGRAM_H
