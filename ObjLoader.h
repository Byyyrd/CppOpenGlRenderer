
#ifndef ObjLoader_H
#define ObjLoader_H


#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <strstream>

#define _SILENCE_CXX17_STRSTREAM_DEPRECATION_WARNING

struct v2 {
    GLfloat x, y;
    v2(GLfloat x, GLfloat y) : x(x), y(y) {}
    void intoVector(std::vector<GLfloat> &vec) const {
        vec.push_back(x);
        vec.push_back(y);
    }
};

struct v3 {
    GLfloat x, y, z;
    v3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y),z(z) {}
    void intoVector(std::vector<GLfloat> &vec) const{
        vec.push_back(x);
        vec.push_back(y);
        vec.push_back(z);
    }
};

struct ObjData{
	std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    std::vector<GLfloat> tris;
};

static ObjData loadObj(const char* path) {

    ObjData data;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return data;
    }

    std::vector<GLfloat> tris;


    std::vector<v3> vertices;
    std::vector<v2> uvs;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type = iss.str().substr(0, 2);
        iss >> type;
        if (type[0] == 'v') {
            if (type[1] == 't') {
                GLfloat u,v;
                iss >> u >> v;
                uvs.push_back(v2{ u,v });
            }
            else {
                GLfloat x, y, z;
                iss >> x >> y >> z;

                vertices.push_back(v3{ x,y,z });
            }
           
        }
        else if (type[0] == 'f') {
            std::string x, y, z;
            iss >> x >> y >> z;

            for (std::string str : {x, y, z}) {
                size_t pos = str.find_first_of('/');
                if (pos != std::string::npos) {
                    std::string num1_str = str.substr(0, pos);
                    std::string num2_str = str.substr(pos + 1);
                    int num1 = std::stoi(num1_str);
                    int num2 = std::stoi(num2_str);
                    vertices[num1 - 1].intoVector(tris);
                    uvs[num2 - 1].intoVector(tris);
                }
            }
            
            
        }
    }
    data.tris = tris;
    return data;

}
#endif
