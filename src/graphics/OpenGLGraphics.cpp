//
// Created by Rob on 7/2/2018.
//

#include "OpenGLGraphics.h"
#include "../os/Utilities.h"


IGraphics *OpenGLGraphics::instance = nullptr;


IGraphics *OpenGLGraphics::GetGraphicsIntf() {
    if (!instance)
        instance = new OpenGLGraphics();

    return instance;
}

void OpenGLGraphics::SetClearColor(DGLColor color) {
    glClearColor(color.red, color.green, color.blue, color.alpha);
}

void OpenGLGraphics::SetDepthTest(bool enable) {
    if (enable)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    mDepthTest = enable;
}

void OpenGLGraphics::SetBlend(eDGLBlendMode blendMode) {
    switch (blendMode)
    {
        case BLEND_MODE_ONE_ONE:
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
            break;

        case BLEND_MODE_ALPHA:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;

        default:
            glDisable(GL_BLEND);
            break;
    }
}

void OpenGLGraphics::ClearScreen() {
    GLbitfield bits = GL_COLOR_BUFFER_BIT;
    if (mDepthTest)
        bits |= GL_DEPTH_BUFFER_BIT;

    glClear(bits);
}

/*
void OpenGLGraphics::ApplyAlpha(float alpha)
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
    glColor4f(0.0f,0.0f,0.0f,alpha);
    glVertex3f(1.15f,1.15f,-2.0f);
    glVertex3f(-1.15f,1.15f,-2.0f);
    glVertex3f(-1.15f,-1.15f,-2.0f);
    glVertex3f(1.15f,-1.15f,-2.0f);
    glEnd();
    glFlush();

    SetDepthTest(mDepthTest);
}
*/

void OpenGLGraphics::SetViewport(int width, int height) {
    glViewport(0, 0, width, height);
}

unsigned int OpenGLGraphics::GenBuffer() {
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    return buffer;
}

void
OpenGLGraphics::LoadVertexBufferData(unsigned int bufferId, const float *data, unsigned int count) {
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void
OpenGLGraphics::UpdateVertexBufferData(unsigned int bufferId, signed long int offset,
                                       const float *data, unsigned int count) {
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferSubData(GL_ARRAY_BUFFER, offset, count * sizeof(float), data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLGraphics::LoadIndexBufferData(unsigned int bufferId, const unsigned short *data,
                                         unsigned int count) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(short), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLGraphics::DrawElementsIndexed(unsigned int indexBufferId, unsigned int count) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OpenGLGraphics::DrawArrays(unsigned int mode, unsigned int count) {
    glDrawArrays(mode, 0, count);
}

unsigned int OpenGLGraphics::CompileShader(unsigned int shaderType, const char *shaderSource) {
    unsigned int shaderId = glCreateShader(shaderType);
    if (!shaderId)
    {
        LOGE("Failed to create shader.");
        return 0;
    }

    glShaderSource(shaderId, 1, &shaderSource, nullptr);
    glCompileShader(shaderId);

    int compileStatus;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus)
    {
        glDeleteShader(shaderId);
        LOGE("Failed to compile shader.");
        // TODO: Add more debug logging.
        return 0;
    }

    return shaderId;
}

unsigned int OpenGLGraphics::LinkProgram(unsigned int vertShaderId, unsigned int fragShaderId) {
    unsigned int programId = glCreateProgram();
    if (!programId)
    {
        LOGE("Failed to create program.");
        return 0;
    }

    glAttachShader(programId, vertShaderId);
    glAttachShader(programId, fragShaderId);
    glLinkProgram(programId);

    int linkStatus;
    glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus)
    {
        glDeleteProgram(programId);
        LOGE("Failure to link program.");
        // TODO: Add more debug logging.
        return 0;
    }

    return programId;
}

bool OpenGLGraphics::ValidateProgram(unsigned int programId) {
    glValidateProgram(programId);

    int validateStatus;
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &validateStatus);
    if (!validateStatus)
    {
        glDeleteProgram(programId);
        LOGE("Failed to validate program.");
        // TODO: Add debug logging.
        return false;
    }

    return true;
}

void OpenGLGraphics::UseProgram(unsigned int programId) {
    glUseProgram(programId);
}

void
OpenGLGraphics::SetVertexAttrPtr(unsigned int bufferId, unsigned int attrIndex, int compPerVert,
                                 unsigned int dataType, int stride, const void *offset) {
    if (bufferId)
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);

    glVertexAttribPointer(attrIndex, compPerVert, dataType, 0, stride, offset);
    glEnableVertexAttribArray(attrIndex);

    if (bufferId)
        glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int OpenGLGraphics::GetAttrLoc(unsigned int programId, const char *attrName) {
    return static_cast<unsigned int>(glGetAttribLocation(programId, attrName));
}

unsigned int OpenGLGraphics::GetUniformLoc(unsigned int programId, const char *uniformName) {
    return static_cast<unsigned int>(glGetUniformLocation(programId, uniformName));
}

void OpenGLGraphics::SetUniform1f(unsigned int uniformIndex, float f) {
    glUniform1f(uniformIndex, f);
}
void
OpenGLGraphics::SetUniform4f(unsigned int uniformIndex, float v0, float v1, float v2, float v3) {
    glUniform4f(uniformIndex, v0, v1, v2, v3);
}

void OpenGLGraphics::SetUniformMatrix4fv(unsigned int uniformIndex, Matrix4 &matrix) {
    glUniformMatrix4fv(uniformIndex, 1, GL_FALSE, matrix.get());
}

void OpenGLGraphics::SetUniform3fv(unsigned int uniformIndex, std::vector<float> &data, int count) {
    glUniform3fv(uniformIndex, count, data.data());
}

void OpenGLGraphics::SetUniform4fv(unsigned int uniformIndex, std::vector<float> &data, int count) {
    glUniform4fv(uniformIndex, count, data.data());
}

unsigned int OpenGLGraphics::LoadTexture(const DGLRawBitmap &bitmap) {
    unsigned int textureId = 0;
    GLenum format;

    switch (bitmap.format)
    {
        case BITMAP_FORMAT_RGBA_8888:
            format = GL_RGBA;
            break;

        case BITMAP_FORMAT_A_8:
            format = GL_ALPHA;
            break;

        default:
            return 0;
    }

    glGenTextures(1, &textureId);
    if (textureId == 0)
        return 0;

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, bitmap.width, bitmap.height, 0, format, GL_UNSIGNED_BYTE,
                 bitmap.pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureId;
}

void
OpenGLGraphics::BindTexture(unsigned int uniformIndex, int activeTexture, unsigned int textureId) {
    glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + activeTexture));
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(uniformIndex, activeTexture);
}
