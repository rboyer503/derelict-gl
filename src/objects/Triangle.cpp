//
// Created by Rob on 6/29/2018.
//

#include "Triangle.h"


TriangleObject::TriangleObject(float verts[18]) {
    mVertAttrs.assign(verts, verts + 18);
    mIndices = {0, 1, 2};
    mNumVerts = 3;
}
