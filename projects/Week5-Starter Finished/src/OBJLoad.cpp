#include "OBJLoad.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

// Borrowed from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
#pragma region String Trimming

// trim from start (in place)
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
        }));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

#pragma endregion 

VertexArrayObject::sptr OBJLoad::LoadFile(const std::string& filename)
{
    std::ifstream fileName;
    fileName.open(filename, std::ios::binary);

    //std::cout << "hgdfjfkyghk";

    // If our file fails to open, we will throw an error
    if (!fileName) {
        throw std::runtime_error("file not opening");
    }

    MeshBuilder<VertexPosNormTexCol>mesh;
    std::string fileLine;

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vert;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_norms;

    while (std::getline(fileName, fileLine))
    {
        //std::cout << "fafwf";

        trim(fileLine);
        //std::cout << fileLine;
        if (fileLine.substr(0, 1) == "#")
        {
            // Comment, do nothing
        }
        else if (fileLine.substr(0, 2) == "v ")
        {
            std::istringstream ss = std::istringstream(fileLine.substr(2));
            glm::vec3 ver;
            ss >> ver.x >> ver.y >> ver.z;
            temp_vert.push_back(ver);

           // std::cout << ver.x << ver.y << ver.z;
        }
        else if (fileLine.substr(0, 3) == "vt ")
        {
            std::istringstream ss = std::istringstream(fileLine.substr(3));   // Jose Change 2 to a 3
            glm::vec3 uv;
            ss >> uv.x >> uv.y;
            temp_uvs.push_back(uv);

           // std::cout << uv.x << uv.y;
        }
        else if (fileLine.substr(0, 3) == "vn ")
        {
            std::istringstream ss = std::istringstream(fileLine.substr(3));   // Jose Change 2 to a 3
            glm::vec3 norm;
            ss >> norm.x >> norm.y >> norm.z;
            temp_norms.push_back(norm);

            //std::cout << norm.x << norm.y << norm.z;
        }

        /*  else if (fileLine.substr(0, 2) == "f")
          {
              std::istringstream ss = std::istringstream(fileLine.substr(2));
              glm::vec3 ver;
              ss >> ver.x >> ver.y >> ver.z;
              unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
              temp_vert.push_back(ver);
          }*/

        else if (fileLine.substr(0, 2) == "f ")
        {
            std::string FileLineSub = fileLine.substr(2);
            std::string fileLineNoSlash = FileLineSub;

            for (int I = 0; I < fileLineNoSlash.length(); I++)
            {
                if (fileLineNoSlash[I] == '/')
                    fileLineNoSlash[I] = ' ';

                //std::cout << "feguw";
            }

            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            std::istringstream ss = std::istringstream(fileLineNoSlash);

            ss >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0] >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1] >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2];

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);

            //std::cout << vertexIndex[0] << uvIndex[0] << normalIndex[0] << vertexIndex[1] << uvIndex[1] << normalIndex[1] << vertexIndex[2] << uvIndex[2] << normalIndex[2] << "\n";
        }

        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vert = temp_vert[vertexIndex - 1];
            unsigned int uvIndex = uvIndices[i];
            glm::vec2 uv = temp_uvs[vertexIndex - 1];
            unsigned int normalIndex = normalIndices[i];
            glm::vec3 normal = temp_norms[vertexIndex - 1];

            mesh.AddVertex(vert, normal, uv, glm::vec4(1));
            mesh.AddIndex(i);
        }
    }

    return mesh.Bake();
}
