#ifndef LK_TEXTURE_H
#define LK_TEXTURE_H

#include <string>

class Texture {
public:
    Texture() = default;

    explicit Texture(const std::string& file);

    bool Load(const std::string& file);

    bool Empty();

    ~Texture();


public:
    int width{};
    int height{};
    int nrChannels{};
    unsigned char *data{};
};


#endif //LK_TEXTURE_H
