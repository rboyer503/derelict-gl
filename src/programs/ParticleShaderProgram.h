//
// Created by Rob on 7/14/2018.
//

#ifndef DGL_PARTICLESHADERPROGRAM_H
#define DGL_PARTICLESHADERPROGRAM_H

#include "ShaderProgram.h"
#include "../data/Matrices.h"


class ParticleShaderProgram : public ShaderProgram
{
    static const char constexpr mVertShaderStr[] =
            "#version 100\n"
                    "uniform mat4 u_MVMatrix;\n"
                    "uniform mat4 u_MVPMatrix;\n"

                    "attribute vec3 a_Position;\n"
                    "attribute vec4 a_Color;\n"
                    "attribute float a_PointSize;\n"

                    "varying vec4 v_Color;\n"

                    "void main() {\n"
                    "    v_Color = a_Color;\n"
                    "    gl_Position = u_MVPMatrix * vec4(a_Position, 1.0);\n"
                    "    vec4 csPos = u_MVMatrix * vec4(a_Position, 1.0);\n"
                    "    gl_PointSize = a_PointSize / -csPos.z;\n"
                    //"    gl_PointSize = 128.0 / -csPos.z;\n"
                    "}\n";

    static const char constexpr mFragShaderStr[] =
            "#version 100\n"
                    "precision mediump float;\n"

                    "uniform sampler2D u_TextureUnit;\n"

                    "varying vec4 v_Color;\n"

                    "void main() {\n"
                    "    gl_FragColor = v_Color * texture2D(u_TextureUnit, gl_PointCoord);\n"
                    "}\n";

    unsigned int mAttrIndices[ATTR_MAX] = {0};
    unsigned int mUniformIndices[UNIFORM_MAX] = {0};

public:
    ParticleShaderProgram();

    unsigned int getAttrIndex(eShaderAttr attr) const override;
    unsigned int getUniformIndex(eShaderUniform uniform) const override;

    void
    setUniforms(Matrix4 &mvMatrix, Matrix4 &mvpMatrix, unsigned int textureId);

};


#endif //DGL_PARTICLESHADERPROGRAM_H
