//
// Created by Rob on 6/29/2018.
//

#ifndef DGL_SHADERPROGRAM_H
#define DGL_SHADERPROGRAM_H

enum eShaderAttr
{
    ATTR_POSITION,
    ATTR_COLOR,
    ATTR_NORMAL,
    ATTR_TEXTUREUV,
    ATTR_POINTSIZE,
    ATTR_MAX
};

enum eShaderUniform
{
    UNIFORM_COLOR,
    UNIFORM_PROJMATRIX,
    UNIFORM_MVMATRIX,
    UNIFORM_ITMVMATRIX,
    UNIFORM_MVPMATRIX,
    UNIFORM_POINTLIGHTPOS,
    UNIFORM_POINTLIGHTCOLOR,
    UNIFORM_TEXTUREUNIT,
    UNIFORM_MAX
};


class ShaderProgram
{
protected:
    static const char *mShaderAttrNames[];
    static const char *mShaderUniformNames[];
    static const int mShaderAttrComps[];
    unsigned int mProgramId = 0;

public:
    explicit ShaderProgram(const char *vertShaderStr, const char *fragShaderStr);
    virtual ~ShaderProgram() {}

    static int getShaderAttrComps(eShaderAttr attr) { return mShaderAttrComps[attr]; }

    void useProgram() const;

    virtual unsigned int getAttrIndex(eShaderAttr attr) const { return 0; }
    virtual unsigned int getUniformIndex(eShaderUniform uniform) const { return 0; }

private:
    unsigned int buildProgram(const char *vertShaderStr, const char *fragShaderStr);
};


#endif //DGL_SHADERPROGRAM_H
