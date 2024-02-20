#ifndef Texture_H
#define Texture_H

#include <glad/glad.h>

#include <string>
#include <filesystem>
#include <iostream>

#include "stb_image.h"

class Texture
{
public:
    GLuint ID;
    int index;
    Texture(const char* filename,GLsizei index) {
        this->index = index;
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        std::string path = (std::filesystem::current_path() / filename).string();
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            std::string fileExtension;
            size_t dotPosition = path.find_last_of(".");
            if (dotPosition != std::string::npos) {
                fileExtension = path.substr(dotPosition + 1);
            }

            if (fileExtension == "png") {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            
        }
        else
        {
            std::cout << "Failed to load texture: " << stbi_failure_reason() << std::endl;
        }
        stbi_image_free(data);
    }

    void Use() {
        int textureLocation = GL_TEXTURE0 + index;

        glActiveTexture(textureLocation);
        glBindTexture(GL_TEXTURE_2D, ID);
    }
};
#endif