#ifndef RAWMODEL_H
#define RAWMODEL_H

#define GLEW_STATIC
#include <GL/glew.h>

class RawModel
{
private:
    const unsigned int vaoID = 0;
    const unsigned int vertexCount = 0;
    const unsigned int vboVertexPositionsID = 0;
    const unsigned int vboTextureCoordinatesID = 0;
    const unsigned int vboIndicesID = 0;
    const unsigned int vboVertexNormalsID = 0;

public:
    RawModel(int vaoID, int vertexCount, int vboVertexPositionsID,
             int vboTextureCoordinatesID, int vboIndicesID, int vboVertexNormalsID);

    RawModel(int vaoID, int vertexCount, int vboVertexPositionsID,
             int vboTextureCoordinatesID, int vboIndicesID);

    ~RawModel();

    int getVaoID();
    int getVertexCount();
};

#endif // RAWMODEL_H
