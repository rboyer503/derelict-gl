//
// Created by Rob on 7/1/2018.
//

#ifndef DGL_GAMEOBJECT_H
#define DGL_GAMEOBJECT_H

#include <list>
#include <memory>
#include <vector>


class GameObject
{
protected:
    std::vector<float> mVertAttrs;
    std::vector<unsigned short> mIndices;
    unsigned short mNumVerts;
    bool mIsDirty = true;

public:
    virtual ~GameObject() {}

    const std::vector<float> &getVertAttrs() const { return mVertAttrs; }
    const std::vector<unsigned short> &getIndices() const { return mIndices; }
    const unsigned short getNumVerts() const { return mNumVerts; }
    bool isDirty() const { return mIsDirty; }
    void setDirty(bool isDirty) { mIsDirty = isDirty; }
    virtual void handleDirty() {};
};

typedef std::shared_ptr<GameObject> game_object_ptr;
typedef std::list<game_object_ptr> game_object_list;


#endif //DGL_GAMEOBJECT_H
