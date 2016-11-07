#include "RawModel.h"

// Mesh Constructor
RawModel::RawModel(int vaoID, int vertexCount, int vboVertexPositionsID,
                   int vboTextureCoordinatesID, int vboIndicesID, int vboVertexNormalsID)
:   vaoID(vaoID)
,   vertexCount(vertexCount)
,   vboVertexPositionsID(vboVertexPositionsID)
,   vboTextureCoordinatesID(vboTextureCoordinatesID)
,   vboIndicesID(vboIndicesID)
,   vboVertexNormalsID(vboVertexNormalsID)
{}

// RawModel w/o Normal Vectors
RawModel::RawModel(int vaoID, int vertexCount, int vboVertexPositionsID,
                   int vboTextureCoordinatesID, int vboIndicesID)
:   vaoID(vaoID)
,   vertexCount(vertexCount)
,   vboVertexPositionsID(vboVertexPositionsID)
,   vboTextureCoordinatesID(vboTextureCoordinatesID)
,   vboIndicesID(vboIndicesID)
{}

RawModel::~RawModel()
{
    // Delete VAO
    glDeleteVertexArrays(1, &vaoID);

    // Delete VBOs
    glDeleteBuffers(1, &vboVertexPositionsID);
    glDeleteBuffers(1, &vboTextureCoordinatesID);
    glDeleteBuffers(1, &vboIndicesID);
    if (vboVertexNormalsID != 0)
        glDeleteBuffers(1, &vboVertexNormalsID);
}

int RawModel::getVaoID()
{
    return vaoID;
}

int RawModel::getVertexCount()
{
    return vertexCount;
}
