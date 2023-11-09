#ifndef LOAD_H__
#define LOAD_H__
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <map>

#include "utils.h"
using namespace std;
#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "object.h"
#include "scene.h"

object *read_obj_file(string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        throw std::ios_base::failure("Error opening file: " + filename);
    }
    vector<GLfloat> position;
    vector<GLfloat> normal;
    vector<GLfloat> uv;

    vector<GLushort> index_position;
    vector<GLushort> index_normal;
    vector<GLushort> index_uv;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            position.push_back(x);
            position.push_back(y);
            position.push_back(z);
            // cout << "v " << x << " " << y << " " << z << endl;
        } else if (token == "vn") {
            float nx, ny, nz;
            iss >> nx >> ny >> nz;
            normal.push_back(nx);
            normal.push_back(ny);
            normal.push_back(nz);
            // cout << "vn " << nx << " " << ny << " " << nz << endl;
        } else if (token == "vt") {
            float u, v;
            iss >> u >> v;
            uv.push_back(u);
            uv.push_back(v);
            // cout << "vt " << u << " " << v << endl;
        } else if (token == "f") {
            // cout << "f ";
            for (int i = 0; i < 3; ++i) {
                uint32_t index_v, index_n, index_u;
                iss >> index_v;
                // cout << index_v;
                index_position.push_back(index_v - 1);
                if (iss.peek() == '/') {
                    iss.ignore();
                    // cout << '/';
                    if (iss.peek() != '/') {
                        iss >> index_u;
                        // cout << index_u;
                        index_uv.push_back(index_u - 1);
                    }
                    if (iss.peek() == '/') {
                        // cout << '/';
                        iss.ignore();
                        iss >> index_n;
                        // cout << index_n;
                        index_normal.push_back(index_n - 1);
                    }
                }
                // cout << " ";
            }
            // cout << endl;
        }
    }
    file.close();

    object *my_obj;
    if(normal.empty()) {
        my_obj = new object(position.size()/3, index_position.size(), position.data(), index_position.data());
    } else {
        map<pair<int,int>, int> uniqueKeys;
        vector<GLfloat> vn;
        vector<GLushort> vnIndex;
        int nextId = 0;
        for(int i=0; i<index_position.size(); ++i) {
            pair<int,int> key = {index_position[i], index_normal[i]};
            if(!uniqueKeys.count(key)) {
                uniqueKeys[key] = nextId++;
                for(int j=0; j<3; ++j) vn.push_back(position[3*index_position[i] + j]);
                for(int j=0; j<3; ++j) vn.push_back(normal[3*index_normal[i] + j]);
            }
            vnIndex.push_back(uniqueKeys[key]);
        }
        my_obj = new object(vn.size()/6, vnIndex.size(), vn.data(), vnIndex.data());
    }

    return my_obj;
}

#endif