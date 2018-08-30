//
// Created by Rob on 7/26/2018.
//

#ifndef DGL_SOUNDMETADATA_H
#define DGL_SOUNDMETADATA_H

#include <cstdint>
#include <vector>


enum eSoundClass
{
    SOUND_CLASS_ANY,
    SOUND_CLASS_NORMAL,
    SOUND_CLASS_BACKTRACK_LONG,
    SOUND_CLASS_BACKTRACK_SHORT,
    SOUND_CLASS_USERDEF_0,
    SOUND_CLASS_USERDEF_1,
    SOUND_CLASS_USERDEF_2,
    SOUND_CLASS_USERDEF_3,
    SOUND_CLASS_USERDEF_4,
    SOUND_CLASS_USERDEF_5,
    SOUND_CLASS_USERDEF_6,
    SOUND_CLASS_USERDEF_7,
    SOUND_CLASS_USERDEF_8,
    SOUND_CLASS_USERDEF_9,
    SOUND_CLASS_MAX
};


struct SoundClassStats
{
    uint32_t mCount;
    uint32_t mOffset;
};


struct SoundMetadata
{
    const char *mAssetName;
    eSoundClass mSoundClass;
    uint32_t mTicksToStart;
    float mVolume;
};

typedef std::vector<SoundMetadata> sound_metadata_vec;


#endif //DGL_SOUNDMETADATA_H
