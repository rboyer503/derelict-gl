//
// Created by Rob on 7/2/2018.
//

#ifndef DGL_OPENGLGRAPHICS_H
#define DGL_OPENGLGRAPHICS_H

#include "IGraphics.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


#define GraphicsIntf OpenGLGraphics::GetGraphicsIntf()


class OpenGLGraphics : public IGraphics
{
    static IGraphics *instance;

public:
    static IGraphics *GetGraphicsIntf();

    // IGraphics interface:
    void SetClearColor(DGLColor color) override;
    void SetDepthTest(bool enable) override;
    void SetBlend(eDGLBlendMode blendMode) override;
    void ClearScreen() override;
    //void ApplyAlpha(float alpha) override;
    void SetViewport(int width, int height) override;
    unsigned int GenBuffer() override;
    void
    LoadVertexBufferData(unsigned int bufferId, const float *data, unsigned int count) override;
    void UpdateVertexBufferData(unsigned int bufferId, signed long int offset, const float *data,
                                unsigned int count) override;
    void LoadIndexBufferData(unsigned int bufferId, const unsigned short *data,
                             unsigned int count) override;
    void DrawElementsIndexed(unsigned int indexBufferId, unsigned int count) override;
    void DrawArrays(unsigned int mode, unsigned int count) override;
    unsigned int CompileShader(unsigned int shaderType, const char *shaderSource) override;
    unsigned int LinkProgram(unsigned int vertShaderId, unsigned int fragShaderId) override;
    bool ValidateProgram(unsigned int programId) override;
    void UseProgram(unsigned int programId) override;
    void SetVertexAttrPtr(unsigned int bufferId, unsigned int attrIndex, int compPerVert,
                          unsigned int dataType, int stride, const void *offset) override;
    unsigned int GetAttrLoc(unsigned int programId, const char *attrName) override;
    unsigned int GetUniformLoc(unsigned int programId, const char *uniformName) override;
    void SetUniform1f(unsigned int uniformIndex, float f) override;
    void SetUniform4f(unsigned int uniformIndex, float v0, float v1, float v2, float v3) override;
    void SetUniformMatrix4fv(unsigned int uniformIndex, Matrix4 &matrix) override;
    void SetUniform3fv(unsigned int uniformIndex, std::vector<float> &data, int count) override;
    void SetUniform4fv(unsigned int uniformIndex, std::vector<float> &data, int count) override;
    unsigned int LoadTexture(const DGLRawBitmap &bitmap) override;
    void BindTexture(unsigned int uniformIndex, int activeTexture, unsigned int textureId) override;

private:
    bool mDepthTest = false;

};


#endif //DGL_OPENGLGRAPHICS_H
