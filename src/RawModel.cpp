#include "RawModel.h"

RawModel::RawModel(int vaoID, int vertexCount)
:   vaoID(vaoID)
,   vertexCount(vertexCount)
{
    //ctor
}

RawModel::~RawModel()
{
    //dtor
}

int RawModel::getVaoID()
{
    return vaoID;
}

int RawModel::getVertexCount()
{
    return vertexCount;
}
