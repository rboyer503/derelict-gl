//
// Created by Rob on 8/8/2018.
//

#include "TextObject.h"


TextObject::TextObject(const SpriteFrameMapInfo *frameMapInfo, std::string text, uint32_t maxLength,
                       eTextJustifyMode justifyMode, Vector3 pos, Vector2 size, DGLColor color,
                       bool active)
        : mMaxLength(maxLength),
          mJustifyMode(justifyMode),
          mPos(pos),
          mSize(size),
          mActive(active) {
    Vector3 currPos = pos;
    for (uint32_t i = 0; i < maxLength; ++i)
    {
        mSpriteVec.push_back(std::make_shared<SpriteObject>(frameMapInfo, currPos, size, color));
        currPos.x += size.x * 0.75f; // TODO: Configurable spacing.
    }

    updateText(text);
}

void TextObject::updateText(std::string text) {
    if (!mActive || (mText == text))
        return;
    else if (text.length() > mMaxLength)
        throw std::runtime_error("TextObject::updateText: [Text exceeded max length]");

    mText = text;

    for (auto &sprite : mSpriteVec)
        sprite->setFrame(0);

    uint32_t currSprite = ((mJustifyMode == JUSTIFY_MODE_LEFT) ? 0 : (mMaxLength -
                                                                      static_cast<uint32_t>(text.length())));
    for (int i = 0; i < text.length(); ++i, ++currSprite)
    {
        if ((text[i] >= '0') && (text[i] <= '9'))
        {
            mSpriteVec[currSprite]->setFrame(static_cast<uint32_t>(text[i] - '0') + NUMBER_OFFSET);
        }
        else if ((text[i] >= 'A') && (text[i] <= 'Z'))
        {
            mSpriteVec[currSprite]->setFrame(static_cast<uint32_t>(text[i] - 'A') + LETTER_OFFSET);
        }
        else if (text[i] == '.')
        {
            mSpriteVec[currSprite]->setFrame(PERIOD_OFFSET);
        }
        else if (text[i] == ',')
        {
            mSpriteVec[currSprite]->setFrame(COMMA_OFFSET);
        }
        else if (text[i] == '!')
        {
            mSpriteVec[currSprite]->setFrame(EXCLAMATION_OFFSET);
        }
        else if (text[i] == '?')
        {
            mSpriteVec[currSprite]->setFrame(QUESTION_OFFSET);
        }
        else if (text[i] == ':')
        {
            mSpriteVec[currSprite]->setFrame(COLON_OFFSET);
        }
        else if (text[i] == '-')
        {
            mSpriteVec[currSprite]->setFrame(DASH_OFFSET);
        }
    }
}

void TextObject::updateColor(DGLColor color)
{
    for (auto &sprite : mSpriteVec)
        sprite->updateColor(color);
}
