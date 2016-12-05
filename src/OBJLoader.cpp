#include "OBJLoader.h"

using namespace std;

std::unique_ptr<RawModel> Loader::loadObjModel(const GLchar* fileName)
{
    // OBJ File Vectors
    std::vector<vector3f> vertices, normals;
    std::vector<vector2f> textureCoordinates;
    std::vector<std::string> faces;

    // VBO Arrays
    std::vector<GLfloat> a_vertices, a_texCoords, a_normals;
    std::vector<GLuint>  a_indices;

    // File Buffer Objects
    ifstream objFile;
    stringstream obj;
    objFile.exceptions( ifstream::badbit );

    // Attempt to read file, if error occurs it returns a nullptr
    try{
        objFile.open(fileName);
        obj << objFile.rdbuf();
        objFile.close();

    } catch (std::ios_base::failure e) {
        cout << "Error loading " << fileName << endl;
        return nullptr;
    }

    // Read the buffer and place into separate vectors to process later
    string line;
    while (std::getline(obj, line))
    {
        istringstream ss(line);

        if (ss.peek() == 'v')
        {
            ss.seekg(1);

            // Vertex
            if (ss.peek() == ' ')
                insertIntoFloatVector(&vertices, &ss, 3);
            else if (ss.peek() == 't')
                insertIntoFloatVector(&textureCoordinates, &ss, 2);
            else if (ss.peek() == 'n')
                insertIntoFloatVector(&normals, &ss, 3);
        }

        if (ss.peek() == 'f')
            insertIntoStringVector(&faces, &ss);
    }

    // From vector<array>s into single <arrays>
    faceArray a;
    GLfloat glf[3];
    int pointAt, indexCount = 0;
    string str;
    for (auto& i : faces)
    {
        std::istringstream ss(i);

        pointAt = 0;
        while (getline(ss, str, '/')) {
                //std::cout << "String: '" << str << "'" << std::endl;

                if (str == "")
                    glf[pointAt] = 1;
                else
                    glf[pointAt] = stoi(str);

                pointAt++;
        }

        //cout << vertices.at(glf[pointAt]-1).at(0) << endl;
        //cout << textureCoordinates.at(glf[1]-1).at(v) << endl;

        // VBO
        for (int v = 0; v < 3; v++)
            a_vertices.push_back(vertices.at(glf[0]-1).at(v));

        for (int v = 0; v < 2; v++){
            //std::cout << "Yeah: " << glf[1]-1 << std::endl;
            //if (glf[1]-1 != 0)
                a_texCoords.push_back(textureCoordinates.at(glf[1]-1).at(v));
        }

        for (int v = 0; v < 3; v++)
            a_normals.push_back(normals.at(glf[2]-1).at(v));

        for (int v = 0; v < 3; v++) {
            a_indices.push_back(indexCount);
            indexCount++;
        }

    }

    return Loader::loadToVAO(a_vertices, a_indices, a_texCoords, a_normals);
}

template<typename T>
void Loader::insertIntoFloatVector(std::vector<T>* vec, std::istringstream* ss,
                                      size_t arraySize)
 {
    std::array<string, 3> x;
    ss->seekg(2);

    if (arraySize == 2)
        *ss >> x[0] >> x[1];
    else
        *ss >> x[0] >> x[1] >> x[2];

    T tArray;
    for(unsigned i = 0; i<arraySize; i++)
        tArray[i] = stof(x[i]);
    vec->push_back(tArray);


    //vec->push_back(T{stof(x), stof(y), stof(z)});
    //cout << "Vector: " << tArray[0] << ", " << tArray[1] << ", " << tArray[2] << endl;
}

void Loader::insertIntoStringVector(std::vector<string>* vec, std::istringstream* ss)
{
    std::array<string, 3> x;
    ss->seekg(2);

    *ss >> x[0] >> x[1] >> x[2];

    for(int i = 0; i<3; i++)
        vec->push_back(x[i]);

    //vec->push_back(T{stof(x), stof(y), stof(z)});
    //cout << "Vector: " << x[0] << ", " << x[1] << ", " << x[2] << endl;
}


/*void OBJLoader::insertIntoVector3f(std::vector<vector3f>* vec, std::istringstream* ss)
{
    string x, y, z;

    ss->seekg(2);
    *ss >> x >> y >> z;
    vec->push_back(vector3f{stof(x), stof(y), stof(z)});

    cout << "Vector3f: " << x << ", " << y << ", " << z << endl;
}

void OBJLoader::insertIntoVector2f(std::vector<vector2f>* vec, std::istringstream* ss)
{
    string x, y;

    ss->seekg(2);
    *ss >> x >> y;
    vec->push_back(vector2f{stof(x), stof(y)});

    cout << "Vector2f: " << x << ", " << y << endl;
}
*/
