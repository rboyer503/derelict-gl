//
// Created by Rob on 7/2/2018.
//

#ifndef DGL_IGRAPHICS_H
#define DGL_IGRAPHICS_H

#include "../data/Matrices.h"

#include <vector>


enum eDGLBitmapFormat
{
    BITMAP_FORMAT_NONE,
    BITMAP_FORMAT_RGBA_8888,
    BITMAP_FORMAT_A_8,
    BITMAP_FORMAT_MAX
};

enum eDGLBlendMode
{
    BLEND_MODE_NONE,
    BLEND_MODE_ONE_ONE,
    BLEND_MODE_ALPHA,
    BLEND_MODE_MAX
};


struct DGLColor
{
    float red;
    float green;
    float blue;
    float alpha;
};

constexpr DGLColor RED{1.0f, 0.0f, 0.0f, 1.0f};
constexpr DGLColor GREEN{0.0f, 1.0f, 0.0f, 1.0f};
constexpr DGLColor BLUE{0.0f, 0.0f, 1.0f, 1.0f};
constexpr DGLColor WHITE{1.0f, 1.0f, 1.0f, 1.0f};
constexpr DGLColor GREY{0.5f, 0.5f, 0.5f, 1.0f};
constexpr DGLColor BLACK{0.0f, 0.0f, 0.0f, 1.0f};
constexpr DGLColor TRANSPARENT{0.0f, 0.0f, 0.0f, 0.0f};


struct DGLRawBitmap
{
    uint32_t width;
    uint32_t height;
    eDGLBitmapFormat format;
    void *pixels;
};


class IGraphics
{
public:
    virtual ~IGraphics() {}

    virtual void SetClearColor(DGLColor color) = 0;
    virtual void SetDepthTest(bool enable) = 0;
    virtual void SetBlend(eDGLBlendMode blendMode) = 0;
    virtual void ClearScreen() = 0;
    //virtual void ApplyAlpha(float alpha) = 0;
    virtual void SetViewport(int width, int height) = 0;
    virtual unsigned int GenBuffer() = 0;
    virtual void
    LoadVertexBufferData(unsigned int bufferId, const float *data, unsigned int count) = 0;
    virtual void
    UpdateVertexBufferData(unsigned int bufferId, signed long int offset, const float *data,
                           unsigned int count) = 0;
    virtual void
    LoadIndexBufferData(unsigned int bufferId, const unsigned short *data, unsigned int count) = 0;
    virtual void DrawElementsIndexed(unsigned int indexBufferId, unsigned int count) = 0;
    virtual void DrawArrays(unsigned int mode, unsigned int count) = 0;
    virtual unsigned int CompileShader(unsigned int shaderType, const char *shaderSource) = 0;
    virtual unsigned int LinkProgram(unsigned int vertShaderId, unsigned int fragShaderId) = 0;
    virtual bool ValidateProgram(unsigned int programId) = 0;
    virtual void UseProgram(unsigned int programId) = 0;
    virtual void SetVertexAttrPtr(unsigned int bufferId, unsigned int attrIndex, int compPerVert,
                                  unsigned int dataType, int stride, const void *offset) = 0;
    virtual unsigned int GetAttrLoc(unsigned int programId, const char *attrName) = 0;
    virtual unsigned int GetUniformLoc(unsigned int programId, const char *uniformName) = 0;
    virtual void SetUniform1f(unsigned int uniformIndex, float f) = 0;
    virtual void
    SetUniform4f(unsigned int uniformIndex, float v0, float v1, float v2, float v3) = 0;
    virtual void SetUniformMatrix4fv(unsigned int uniformIndex, Matrix4 &matrix) = 0;
    virtual void SetUniform3fv(unsigned int uniformIndex, std::vector<float> &data, int count) = 0;
    virtual void SetUniform4fv(unsigned int uniformIndex, std::vector<float> &data, int count) = 0;
    virtual unsigned int LoadTexture(const DGLRawBitmap &bitmap) = 0;
    virtual void
    BindTexture(unsigned int uniformIndex, int activeTexture, unsigned int textureId) = 0;

};


#endif //DGL_IGRAPHICS_H
