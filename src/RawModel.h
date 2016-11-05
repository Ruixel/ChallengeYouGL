#ifndef RAWMODEL_H
#define RAWMODEL_H


class RawModel
{
private:
    int vaoID;
    int vertexCount;

public:
    RawModel(int vaoID, int vertexCount);
    ~RawModel();

    int getVaoID();
    int getVertexCount();
};

#endif // RAWMODEL_H
