//
// Created by Rob on 8/23/2018.
//

#ifndef FOURTHREALM_COLORSHADERPROGRAM_H
#define FOURTHREALM_COLORSHADERPROGRAM_H

#include "ShaderProgram.h"


class ColorShaderProgram : public ShaderProgram
{
    static const char constexpr mVertShaderStr[] =
            "#version 100\n"
                    "attribute vec4 a_Position;\n"
                    "attribute vec4 a_Color;\n"

                    "varying vec4 v_Color;\n"

                    "void main() {\n"
                    "    v_Color = a_Color;\n"
                    "    gl_Position = a_Position;\n"
                    "}\n";

    static const char constexpr mFragShaderStr[] =
            "#version 100\n"
                    "precision mediump float;\n"

                    "varying vec4 v_Color;\n"

                    "void main() {\n"
                    "    gl_FragColor = v_Color;\n"
                    "}\n";

    unsigned int mAttrIndices[ATTR_MAX] = {0};
    unsigned int mUniformIndices[UNIFORM_MAX] = {0};

public:
    ColorShaderProgram();

    unsigned int getAttrIndex(eShaderAttr attr) const override;
    unsigned int getUniformIndex(eShaderUniform uniform) const override;

};


#endif //FOURTHREALM_COLORSHADERPROGRAM_H
