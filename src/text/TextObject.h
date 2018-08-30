//
// Created by Rob on 8/8/2018.
//

#ifndef DGL_TEXTOBJECT_H
#define DGL_TEXTOBJECT_H

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "../data/Vectors.h"
#include "../objects/Sprite.h"


enum eTextJustifyMode
{
    JUSTIFY_MODE_LEFT,
    JUSTIFY_MODE_RIGHT,
    JUSTIFY_MODE_MAX
};


class TextObject
{
    static constexpr uint32_t NUMBER_OFFSET = 1;
    static constexpr uint32_t LETTER_OFFSET = 16;
    static constexpr uint32_t PERIOD_OFFSET = 42;
    static constexpr uint32_t COMMA_OFFSET = 43;
    static constexpr uint32_t EXCLAMATION_OFFSET = 44;
    static constexpr uint32_t QUESTION_OFFSET = 45;
    static constexpr uint32_t COLON_OFFSET = 46;
    static constexpr uint32_t DASH_OFFSET = 47;

    std::string mText;
    uint32_t mMaxLength;
    eTextJustifyMode mJustifyMode;
    Vector3 mPos;
    Vector2 mSize;
    bool mActive;

    sprite_vec mSpriteVec;

public:
    TextObject(const SpriteFrameMapInfo *frameMapInfo, std::string text, uint32_t maxLength,
               eTextJustifyMode justifyMode, Vector3 pos, Vector2 size, DGLColor color,
               bool active);

    const sprite_vec &getSpriteVec() const { return mSpriteVec; }

    void updateText(std::string text);
    void updateColor(DGLColor color);
};

typedef std::shared_ptr<TextObject> text_object_ptr;
typedef std::list<text_object_ptr> text_object_list;
typedef std::vector<text_object_ptr> text_object_vec;


#endif //DGL_TEXTOBJECT_H
