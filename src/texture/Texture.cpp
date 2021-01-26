#include <stb_image.h>

#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

Texture::Texture(const std::string &file) {
    data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
}

Texture::~Texture() {
    stbi_image_free(data);
}

bool Texture::Load(const std::string &file) {
    if (data != nullptr) {
        stbi_image_free(data);
    }
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
    return data != nullptr;
}

bool Texture::Empty() {
    return data == nullptr;
}
