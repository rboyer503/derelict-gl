//
// Created by Rob on 8/8/2018.
//

#ifndef DGL_SPRITESHADERPROGRAM_H
#define DGL_SPRITESHADERPROGRAM_H

#include "ShaderProgram.h"


class SpriteShaderProgram : public ShaderProgram
{
    static const char constexpr mVertShaderStr[] =
            "#version 100\n"
                    "attribute vec4 a_Position;\n"
                    "attribute vec4 a_Color;\n"
                    "attribute vec2 a_TextureUV;\n"

                    "varying vec4 v_Color;\n"
                    "varying vec2 v_TextureUV;\n"

                    "void main() {\n"
                    "    v_Color = a_Color;\n"
                    "    v_TextureUV = a_TextureUV;\n"
                    "    gl_Position = a_Position;\n"
                    "}\n";

    static const char constexpr mFragShaderStr[] =
            "#version 100\n"
                    "precision mediump float;\n"

                    "uniform sampler2D u_TextureUnit;\n"

                    "varying vec4 v_Color;\n"
                    "varying vec2 v_TextureUV;\n"

                    "void main() {\n"
                    "    gl_FragColor = v_Color * texture2D(u_TextureUnit, v_TextureUV);\n"
                    "}\n";

    unsigned int mAttrIndices[ATTR_MAX] = {0};
    unsigned int mUniformIndices[UNIFORM_MAX] = {0};

public:
    SpriteShaderProgram();

    unsigned int getAttrIndex(eShaderAttr attr) const override;
    unsigned int getUniformIndex(eShaderUniform uniform) const override;

    void setUniforms(unsigned int textureId);

};


#endif //DGL_SPRITESHADERPROGRAM_H
