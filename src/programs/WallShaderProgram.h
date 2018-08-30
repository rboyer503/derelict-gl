//
// Created by Rob on 7/11/2018.
//

#ifndef DGL_WALLSHADERPROGRAM_H
#define DGL_WALLSHADERPROGRAM_H

#include "ShaderProgram.h"
#include "../data/Matrices.h"


class WallShaderProgram : public ShaderProgram
{
    static const char constexpr mVertShaderStr[] =
            "#version 100\n"
                    "uniform mat4 u_MVMatrix;\n"
                    "uniform mat4 u_IT_MVMatrix;\n"
                    "uniform mat4 u_MVPMatrix;\n"
                    "uniform vec4 u_PointLightPositions[3];\n"
                    "uniform vec3 u_PointLightColors[3];\n"

                    "attribute vec4 a_Position;\n"
                    "attribute vec3 a_Normal;\n"
                    "attribute vec2 a_TextureUV;\n"

                    "varying vec3 v_Color;\n"
                    "varying vec2 v_TextureUV;\n"
                    "varying float v_FogFactor;\n"

                    "vec4 eyeSpacePosition;\n"
                    "vec3 eyeSpaceNormal;\n"

                    "vec3 getAmbientLighting();\n"
                    "vec3 getPointLighting();\n"
                    "float getFogFactor();\n"

                    "void main() {\n"
                    "    eyeSpacePosition = u_MVMatrix * a_Position;\n"
                    "    eyeSpaceNormal = normalize(vec3(u_IT_MVMatrix * vec4(a_Normal, 0.0)));\n"
                    "    v_Color = getAmbientLighting();\n"
                    "    v_Color += getPointLighting();\n"
                    "    v_FogFactor = getFogFactor();\n"
                    "    v_TextureUV = a_TextureUV;\n"
                    "    gl_Position = u_MVPMatrix * a_Position;\n"
                    "}\n"

                    "float getFogFactor() {\n"
                    "    float fogFactor = (20.0 - length(eyeSpacePosition)) / 20.0;\n"
                    "    return clamp(fogFactor, 0.0, 1.0);\n"
                    "}\n"

                    "vec3 getAmbientLighting() {\n"
                    "    return vec3(0.1, 0.1, 0.1);\n"
                    "}\n"

                    "vec3 getPointLighting() {\n"
                    "    vec3 lightingSum = vec3(0.0);\n"
                    "    for (int i = 0; i < 3; i++) {\n"
                    "        vec3 toPointLight = vec3(u_PointLightPositions[i]) - vec3(eyeSpacePosition);\n"
                    "        float distance = length(toPointLight);\n"
                    "        toPointLight = normalize(toPointLight);\n"
                    "        float cosine = max(dot(eyeSpaceNormal, toPointLight), 0.0);\n"
                    "        lightingSum += (u_PointLightColors[i] * 8.0 * cosine) / (distance * distance);\n"
                    "    }\n"
                    "    return lightingSum;\n"
                    "}\n";

    static const char constexpr mFragShaderStr[] =
            "#version 100\n"
                    "precision mediump float;\n"

                    "uniform sampler2D u_TextureUnit;\n"

                    "varying vec3 v_Color;\n"
                    "varying vec2 v_TextureUV;\n"
                    "varying float v_FogFactor;\n"

                    "void main() {\n"
                    "    gl_FragColor = texture2D(u_TextureUnit, v_TextureUV) * vec4(v_Color, 1.0);\n"
                    "    gl_FragColor = mix(vec4(0.4, 0.5, 0.6, 1.0), gl_FragColor, v_FogFactor);\n"
                    "}\n";

    unsigned int mAttrIndices[ATTR_MAX] = {0};
    unsigned int mUniformIndices[UNIFORM_MAX] = {0};

public:
    WallShaderProgram();

    unsigned int getAttrIndex(eShaderAttr attr) const override;
    unsigned int getUniformIndex(eShaderUniform uniform) const override;

    void setUniforms(Matrix4 &mvMatrix, Matrix4 &it_mvMatrix, Matrix4 &mvpMatrix,
                     std::vector<float> &pointLightPos, std::vector<float> &pointLightColor,
                     int numPointLights, unsigned int textureId);

};


#endif //DGL_WALLSHADERPROGRAM_H
